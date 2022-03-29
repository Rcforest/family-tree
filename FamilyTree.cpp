//
// Created by Rcforest on 2022/3/16.
//

#include "FamilyTree.h"

void FamilyTree::displayWithConcaveShape(FamilyMemberNode* root_, int level)
{
    FamilyMemberNode* p;
    if (root_ != nullptr)
    {
        cout << endl;
        string name = root_->person.name;
        for (int i = 0; i < level - 1; ++i)
        {
            cout << "   ";
        }
        cout << name;
        for (p = root_->firstChild; p != nullptr; p = p->nextSibling)
        {
            displayWithConcaveShape(p, level + 1);
        }
    }
}

void FamilyTree::Destroy(FamilyMemberNode*& r)
{
    FamilyMemberNode* p;
    if (r != NULL)
    {
        for (p = FirstChild(r); p != NULL; p = NextSibling(p))
            Destroy(p);
        delete r;
        r = NULL;
    }
}

FamilyMemberNode* FamilyTree::Parent(FamilyMemberNode* r, const FamilyMemberNode* cur) const
{
    if (r == NULL) return NULL;

    FamilyMemberNode* p;        // 孩子
    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
        if (p == cur) return r;                // cur是r的孩子

    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
    {
        FamilyMemberNode* q;
        q = Parent(p, cur);                    // 在子树上求cur的双亲
        if (q != NULL) return q;            // 双亲在子树上
    }
    return NULL;                            // 未找到双亲
}

FamilyMemberNode* FamilyTree::CopyTree(FamilyMemberNode* r)
{
    if (r == NULL)
        return NULL;
    FamilyMemberNode* t = new FamilyMemberNode(r->person);
    FamilyMemberNode* subTreeRoot, * cur = NULL, * p;
    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
    {
        subTreeRoot = CopyTree(p);
        if (t->firstChild == NULL)
        {
            t->firstChild = subTreeRoot;
            cur = subTreeRoot;
        }
        else
        {
            cur->nextSibling = subTreeRoot;
            cur = subTreeRoot;
        }
    }
    return t;
}

FamilyMemberNode* FamilyTree::Find(FamilyMemberNode* r, const string& Name) const
{
    if (r == NULL) return NULL;
    if (r->person.name == Name) return r;
    FamilyMemberNode* p;
    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
        if (p->person.name == Name) return p;
    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
    {
        FamilyMemberNode* q;
        q = Find(p, Name);
        if (q != NULL) return q;
    }
}

FamilyMemberNode* FamilyTree::createTree(Person (& persons)[100],
    vector<int> personsList,
    vector<int> parents,
    int root_)
{
    FamilyMemberNode* r;
    for (const Person& person : persons)
    {
        if (root_ == person.id - 1)
        {
            r = new FamilyMemberNode(person);
            break;
        }
    }
    FamilyMemberNode* subTreeRoot, * cur;
    for (int i = 0; i < memberCount; ++i)
    {
        if (parents[i] == root_)
        {
            if (persons[personsList[i]].birth <= persons[root_].birth)
            {
                cout << "存在孩子的年龄大于父亲, 家谱不合法!" << endl;
                return nullptr;
            }
            subTreeRoot = createTree(persons, personsList, parents, personsList[i]);
            if (!subTreeRoot) return nullptr;
            if (r->firstChild == nullptr)
            {
                r->firstChild = subTreeRoot;
                cur = subTreeRoot;
            }
            else
            {
                cur->nextSibling = subTreeRoot;
                cur = subTreeRoot;
            }
        }
    }
    return r;
}

void FamilyTree::getPersonsFromFile(const string& filename, Person (& persons)[MAX])
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        return;
    }
    string line;
    string delimiter;
    int count;
    infile >> count;
    memberCount = count;
    std::getline(infile, line);
    for (int i = 0; i < count; ++i)
    {
        std::getline(infile, line);
        vector<string> list = split(line, ", ");
        persons[i].id = stoi(list[0]);
        persons[i].name = list[1];
        persons[i].birth = Date(stoi(list[2]), stoi(list[3]), stoi(list[4]));
        persons[i].marriage = stoi(list[5]);
        persons[i].address = list[6];
        persons[i].alive = stoi(list[7]);
        if (!persons[i].alive)
        {
            persons[i].death = Date(stoi(list[8]), stoi(list[9]), stoi(list[10]));
        }
    }
}

void FamilyTree::getTreeFromFile(const string& filename, Person (& persons)[MAX])
{

    ifstream infile(filename);
    if (!infile.is_open())
    {
        return;
    }
    vector<int> parents;
    vector<int> repeatedIndex;
    string line;
    std::getline(infile, line);
    vector<string> personList = split(line, ", ");
    int n = memberCount;
    for (int i = 0; i < n; ++i)
    {
        if (persons[stoi(personList[i])].recorded)
        {
            memberCount--;
            repeatedIndex.push_back(i);
            continue;
        }
        persons[stoi(personList[i])].recorded = true;
    }
    std::getline(infile, line);
    vector<string> parentList = split(line, ", ");
    vector<int> personsIndex;
    int root_index = 0;
    int count = memberCount + size(repeatedIndex);
    for (int i = 0; i < count; ++i)
    {
        if (std::find(repeatedIndex.begin(), repeatedIndex.end(), i) != repeatedIndex.end())
        {
            continue;
        }
        if (stoi(parentList[i]) == -1)
        {
            root_index = stoi(personList[i]);
        }
        personsIndex.push_back(stoi(personList[i]));
        parents.push_back(stoi(parentList[i]));
    }
    root = createTree(persons, personsIndex, parents, root_index);
    if (root == nullptr) exit(1);
}

void FamilyTree::exportToPersonFile(const string& filename)
{
    ofstream personsOut;
    personsOut.open(filename);
    if (!personsOut)
    {
        cout << "personOut file open error";
        return;
    }
    personsOut << memberCount << "\n";
    outputPersonInfo(root, personsOut);
    personsOut.close();
}

void FamilyTree::exportToCaseFile(const string& filename)
{
    ofstream caseOut;
    caseOut.open(filename);
    if (!caseOut)
    {
        return;
    }
    exportPersonIndex(caseOut);
    exportParentIndex(caseOut);
    caseOut.close();
}

void FamilyTree::exportPersonIndex(ofstream& file)
{
    int count = 0;
    outputPersonIndex(root, file, count);
}

void FamilyTree::exportParentIndex(ofstream& file)
{
    int count = 0;
    outputParentIndex(root, file, count);
}

void FamilyTree::GetNumOfGeneration(FamilyMemberNode* r, const FamilyMemberNode* p, int level, int& result) const
{
    if (r != NULL)
    {
        level++;
        if (r == p)
        {
            result = level;
            return;
        }
    }
    if (FirstChild(r) != NULL)
        GetNumOfGeneration(FirstChild(r), p, level, result);
    if (NextSibling(r) != NULL)
        GetNumOfGeneration(NextSibling(r), p, level - 1, result);
}

FamilyTree::FamilyTree()
{
    root = NULL;
    memberCount = 0;
}

FamilyTree::FamilyTree(const FamilyTree& copy)
{
    root = CopyTree(copy.root);
    memberCount = copy.memberCount;
}

void FamilyTree::display()
{
    displayWithConcaveShape(root, 1);
    cout << endl;
}

void FamilyTree::relationship(const string& name1, const string& name2) const
{
    FamilyMemberNode* p1 = Find(name1);
    FamilyMemberNode* p2 = Find(name2);
    if (p1 && p2)
    {
        int NG1 = GetNumOfGeneration(p1);
        int NG2 = GetNumOfGeneration(p2);
        if (NG1 == NG2)
            if (Parent(p1) == Parent(p2))
                cout << name1 << "是" << name2 << "的亲兄弟" << endl;
            else
                cout << name1 << "是" << name2 << "的堂兄弟" << endl;
        else if (NG2 > NG1)
            if (NG2 - NG1 == 1)
            {
                if (p1 == Parent(p2))
                    cout << name1 << "是" << name2 << "的爸爸" << endl;
                else
                    cout << name1 << "是" << name2 << "的叔叔" << endl;
            }
            else
                cout << name1 << "是" << name2 << "的爷爷" << endl;
        else if (NG2 < NG1)
            if (NG1 - NG2 == 1)
                if (p2 == Parent(p1))
                    cout << name2 << "是" << name1 << "的爸爸" << endl;
                else
                    cout << name2 << "是" << name1 << "的叔叔" << endl;
            else
                cout << name2 << "是" << name1 << "的爷爷" << endl;
    }
    else if (!p1)
        cout << name1 << " 不在家族信息中！！" << endl;
    if (!p2)
        cout << name2 << " 不在家族信息中！！" << endl;
}
void FamilyTree::addChild(const string& name)
{
    FamilyMemberNode* p = Find(name);
    if (!p)
    {
        cout << name << "不在家族信息中！！" << endl;
        return;
    }
    int num = 0, i = 0;
    cout << "添加孩子个数：";
    cin >> num;
    Person children[10];
    int flag = 1;

    while (num--)
    {
        int id = memberCount++;
        children[i].id = id;
        cout << "请输入姓名：" << endl;
        cin >> children[i].name;
        while (flag)
        {
            cout << "出生日期：(eg:0000 00 00)" << endl;
            int y, m, d;
            cin >> y >> m >> d;
            if (!isValidBirth(Date(y, m, d), p->person.birth))
            {
                cout << "年龄大于父亲, 请重新输入!" << endl;
                continue;
            }
            children[i].birth = Date(y, m, d);
            flag = 0;
        }
        cout << "是否婚姻：0/1" << endl;
        cin >> children[i].marriage;
        cout << "住址：" << endl;
        cin >> children[i].address;
        cout << "是否在世：0/1" << endl;
        cin >> children[i].alive;
        if (!children[i].alive)
        {
            flag = 1;
            while (flag)
            {
                int y, m, d;
                cout << "去世日期：(eg:0000 00 00)" << endl;
                cin >> y >> m >> d;
                if (!isValidDeath(children[i].birth, Date(y, m, d)))
                {
                    cout << "去世日期小于出生日期, 请重新输入!" << endl;
                    continue;
                }
                children[i].death = Date(y, m, d);
                flag = 0;
            }
        }
        flag = 1;
        if (flag)
        {
            if (!p->firstChild)
            {
                p->firstChild = new FamilyMemberNode(children[i]);
                p = p->firstChild;
                flag = 0;
            }
            else
            {
                p = p->firstChild;
                while (p->nextSibling)
                    p = p->nextSibling;
                p->nextSibling = new FamilyMemberNode(children[i]);
                p = p->nextSibling;
                flag = 0;
            }
        }
        else
        {
            p->nextSibling = new FamilyMemberNode(children[i]);
            p = p->nextSibling;
        }
        i++;
    }
}
void FamilyTree::remove(const string& name)
{
    FamilyMemberNode* person = Find(root, name);
    if (person == NULL)
    {
        cout << "输入信息有误!" << endl;
        return;
    }
    if (Parent(person) != NULL)
    {
        FamilyMemberNode* p = Parent(person);
        if (p->firstChild == person)
        {
            p->firstChild = person->nextSibling;
            memberCount -= nodeCount(person);
            delete person;
            person = NULL;
        }
        else
        {
            FamilyMemberNode* p1 = p->firstChild;
            while (p1->nextSibling != person)
            {
                p1 = p1->nextSibling;
            }
            p1->nextSibling = person->nextSibling;
            memberCount -= nodeCount(person);
            delete person;
            person = NULL;
        }
    }
    else
    {
        cout << "第一代人无法删除!" << endl;
    }
}
void FamilyTree::update(string name)
{
    FamilyMemberNode* personNode = Find(name);
    Person presentPerson = personNode->person;
    if (personNode == NULL)
    {
        cout << "输入信息有误!" << endl;
        return;
    }
    cout << "请按下列指引修改信息！" << endl;
    cout << "请输入姓名:" << endl;
    cin >> presentPerson.name;
    cin.ignore();
    int flag = 1;
    while (flag)
    {
        cout << "请输入生日(年 月 日):" << endl;
        int y, m, d;
        cin >> y >> m >> d;
        Date birthday = Date(y, m, d);
        Date parentBirth = Parent(personNode)->person.birth;
        if (!isValidBirth(birthday, parentBirth))
        {
            cout << "年龄大于其父亲, 请重新输入!" << endl;
            continue;
        }
        personNode->person.birth = birthday;
        flag = 0;
    }
    cout << "请输入地址" << endl;
    cin >> presentPerson.address;
    int IsMarried;
    cout << "请输入婚姻状况,已婚输1，未婚输0" << endl;
    cin >> presentPerson.marriage;
    cin.ignore();
    cout << "该人是否在世，在世输1，已去世输0" << endl;
    cin >> presentPerson.alive;
    cin.ignore();
    if (!presentPerson.alive)
    {
        flag = 1;
        while (flag)
        {
            int y, m, d;
            cout << "输入去世日期(年 月 日)" << endl;
            cin >> y >> m >> d;
            Date deathDay = Date(y, m, d);
            if (deathDay < presentPerson.birth)
            {
                cout << "去世日期小于出生日期, 请重新输入!" << endl;
                continue;
            }
            flag = 0;
        }
    }
}

void FamilyTree::importFromFile(const string& personFile, const string& caseFile)
{
    Person persons[MAX];
    getPersonsFromFile(personFile, persons);
    getTreeFromFile(caseFile, persons);
}

void FamilyTree::exportToFile(const string& personFile, const string& caseFile)
{
    exportToPersonFile(personFile);
    exportToCaseFile(caseFile);
}

FamilyTree::~FamilyTree()
{
    Destroy(root);
}

FamilyMemberNode* FamilyTree::FirstChild(const FamilyMemberNode* r) const
{
    if (r == NULL)
        return NULL;
    return r->firstChild;
}
FamilyMemberNode* FamilyTree::NextSibling(const FamilyMemberNode* r) const
{
    if (r == NULL)
        return NULL;
    return r->nextSibling;
}

FamilyMemberNode* FamilyTree::Parent(const FamilyMemberNode* p) const
{
    return Parent(root, p);
}

FamilyMemberNode* FamilyTree::Find(const string& Name) const
{
    if (Name.empty())
        cerr << "Invalid input of Name." << endl;
    return Find(root, Name);
}

void FamilyTree::ShowInfoOf(const string& Name) const
{
    FamilyMemberNode* p = Find(Name);
    if (p == NULL)
    {
        cout << "查无此人" << endl;
        return;
    }
    cout << "被查询者信息：" << endl;
    cout << p->person << endl;
    cout << "是家中第" << GetNumOfGeneration(p) << "代成员" << endl;
    cout << "其父亲信息：" << endl;
    FamilyMemberNode* q = Parent(p);
    if (q != NULL)
        cout << q->person << endl;
    else
        cout << "None" << endl;
    cout << "其孩子信息：" << endl;
    int i = 1;
    for (FamilyMemberNode* t = FirstChild(p); t != NULL; t = NextSibling(t))
    {
        cout << "--第" << i << "个孩子：--" << endl;
        cout << t->person << endl;
        i++;
    }
}

void FamilyTree::ShowInfoOfGenNum(const int& n)
{
    if (root == NULL)
    {
        cout << "家谱树为空" << endl;
        return;
    }
    queue<FamilyMemberNode*> NodesQue;
    int height = 1;
    NodesQue.push(root);
    while (!NodesQue.empty())
    {
        if (n == height)
            break;
        int len = NodesQue.size();
        for (int i = 0; i < len; i++)
        {
            FamilyMemberNode* p = NodesQue.front();
            NodesQue.pop();
            if (FirstChild(p) != NULL)
                for (FamilyMemberNode* q = FirstChild(p); q != NULL; q = NextSibling(q))
                    NodesQue.push(q);
        }
        height++;
    }
    if (n != height)
        cout << "不存在第" << n << "代人" << endl;
    else
    {
        cout << "第" << n << "代共有" << NodesQue.size() << "人" << endl;
        while (!NodesQue.empty())
        {
            FamilyMemberNode* p = NodesQue.front();
            NodesQue.pop();
            cout << p->person.name << '\t';
        }
        cout << endl;
    }
}

int FamilyTree::GetNumOfGeneration(FamilyMemberNode* p) const
{
    int NumGeneration = 0;
    GetNumOfGeneration(root, p, NumGeneration, NumGeneration);
    if (NumGeneration > 0)
        return NumGeneration;
    cerr << "未找到该节点" << endl;
}

FamilyTree& FamilyTree::operator=(const FamilyTree& copy)
{
    if (&copy != this)
    {
        Destroy(root);
        root = CopyTree(copy.root);
    }
    return (*this);
}

void FamilyTree::outputPersonInfo(FamilyMemberNode* root_, ofstream& personsOut)
{
    FamilyMemberNode* p;
    if (root_ == nullptr)
    {
        return;
    }
    Person presentPerson = root_->person;
    personsOut << presentPerson.id << ", ";
    personsOut << presentPerson.name << ", ";
    personsOut << presentPerson.birth.year << ", ";
    personsOut << presentPerson.birth.month << ", ";
    personsOut << presentPerson.birth.day << ", ";
    personsOut << presentPerson.marriage << ", ";
    personsOut << presentPerson.address << ", ";
    personsOut << presentPerson.alive;
    if (!presentPerson.alive)
    {
        personsOut << ", ";
        personsOut << presentPerson.death.year << ", ";
        personsOut << presentPerson.death.month << ", ";
        personsOut << presentPerson.death.day;
    }
    personsOut << "\n";
    for (p = FirstChild(root_); p != nullptr; p = NextSibling(p))
        outputPersonInfo(p, personsOut);
}

void FamilyTree::outputPersonIndex(FamilyMemberNode* root_, ofstream& file, int& count)
{
    if (root_ == nullptr)
    {
        return;
    }
    file << root_->person.id - 1;
    count++;
    if (count == memberCount)
    {
        file << endl;
    }
    else
    {
        file << ", ";
    }
    FamilyMemberNode* p;
    for (p = FirstChild(root_); p != nullptr; p = NextSibling(p))
        outputPersonIndex(p, file, count);
}

void FamilyTree::outputParentIndex(FamilyMemberNode* root_, ofstream& file, int& count)
{
    if (root_ == nullptr)
    {
        return;
    }
    int parent_index;
    if (root_ == root)
    {
        parent_index = -1;
    }
    else
    {
        parent_index = Parent(root_)->person.id - 1;
    }
    file << parent_index;
    count++;
    if (count == memberCount)
    {
        file << endl;
    }
    else
    {
        file << ", ";
    }
    FamilyMemberNode* p;
    for (p = FirstChild(root_); p != nullptr; p = p->nextSibling)
    {
        outputParentIndex(p, file, count);
    }
}

int FamilyTree::nodeCount(FamilyMemberNode* r)
{
    FamilyMemberNode* p;
    if (r == nullptr)
    {
        return 0;
    }
    int subTreeNodeCountSum = 0;
    for (p = FirstChild(r); p != nullptr; p = NextSibling(p))
        subTreeNodeCountSum += nodeCount(p);
    return 1 + subTreeNodeCountSum;

}
bool FamilyTree::isValidBirth(const Date& presentBirth, const Date& parentBirth)
{
    return presentBirth > parentBirth;
}
bool FamilyTree::isValidDeath(const Date& presentBirth, const Date& presentDeath)
{
    return presentDeath >= presentBirth;
}

vector<string> split(string phrase, const string& delimiter)
{
    vector<string> list;
    size_t pos = 0;
    string token;
    while ((pos = phrase.find(delimiter)) != string::npos)
    {
        token = phrase.substr(0, pos);
        list.push_back(token);
        phrase.erase(0, pos + delimiter.length());
    }
    list.push_back(phrase);
    return list;
}

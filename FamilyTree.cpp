//
// Created by Rcforest on 2022/3/16.
//

#include "FamilyTree.h"


string FamilyTree::getName(FamilyMemberNode* r)
{
    for (const Person& i : persons) {
        if (i.id == r->id())
            return i.name;
    }
    return "\0";
}

void FamilyTree::displayWithConcaveShape(FamilyMemberNode* root_, int level)
{
    FamilyMemberNode* p;
    if (root_ != nullptr) {
        cout << endl;
        string name = root_->person.name;
        for (int i = 0; i < level - 1; ++i) {
            cout << "   ";
        }
        cout << name;
        for (p = root_->firstChild; p != nullptr; p = p->nextSibling) {
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
        delete r; r = NULL;
    }
}

FamilyMemberNode* FamilyTree::Parent(FamilyMemberNode* r, const FamilyMemberNode* cur) const
{
    if (r == NULL) return NULL;				// 绌轰簩鍙夋爲

    FamilyMemberNode *p;        // 孩子
    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
        if (p == cur) return r;                // cur是r的孩子

    for (p = FirstChild(r); p != NULL; p = NextSibling(p)) {
        FamilyMemberNode *q;
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
        q = Find(p,Name);
        if(q!=NULL) return q;
    }
}

FamilyMemberNode* FamilyTree::createTree(vector<int> parents, int root_)
{
    int index = persons_id[root_];
    FamilyMemberNode* r = new FamilyMemberNode(persons[index]);
    FamilyMemberNode* subTreeRoot, * cur=NULL;
    for (int i = 0; i < memberCount; ++i) {
        if (parents[i] == root_) {
            subTreeRoot = createTree(parents, i);
            if (r->firstChild == nullptr) {
                r->firstChild = subTreeRoot;
                cur = subTreeRoot;
            }
            else {
                cur->nextSibling = subTreeRoot;
                cur = subTreeRoot;
            }
        }
    }

    return r;
}

FamilyMemberNode* FamilyTree::parent(FamilyMemberNode* root_, const FamilyMemberNode* child) const
{
    if (root_ == nullptr) return nullptr;
    FamilyMemberNode* p;
    for (p = root_->firstChild; p != nullptr; p = p->nextSibling) {
        if (p == child) return root_;
    }
    for (p = root_->firstChild; p != nullptr; p = p->nextSibling) {
        FamilyMemberNode* q = parent(p, child);
        if (q) return q;
    }
    return nullptr;
}

FamilyMemberNode* FamilyTree::node(int id, FamilyMemberNode* root_)
{
    FamilyMemberNode* p;
    if (root_ == nullptr || root_->id() == id) {
        return root_;
    }
    for (p = root_->firstChild; p != nullptr; p = p->nextSibling) {
        FamilyMemberNode* presentNode = node(id, p);
        if (presentNode) return presentNode;
    }
    return nullptr;
}

int FamilyTree::parentIndex(const FamilyMemberNode* child) const
{
    if (child == root) {
        return -1;
    }
    int id = parent(root, child)->id();
    for (int i = 0; i < memberCount; ++i) {
        if (persons_id[i] == id) return i;
    }
    return -1;
}

void FamilyTree::getPersonsFromFile(const string& filename)
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

void FamilyTree::getTreeFromFile(const string& filename)
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
    vector<string> list = split(line, ", ");
    int n = memberCount, count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (persons[stoi(list[i])].recorded)
        {
            memberCount--;
            repeatedIndex.push_back(i);
            continue;
        }
        persons_id[count] = stoi(list[i]);
        persons[stoi(list[i])].recorded = true;
        count++;
    }
    std::getline(infile, line);
    list = split(line, ", ");
    for (int i = 0; i < memberCount; ++i)
    {
        if (std::find(repeatedIndex.begin(), repeatedIndex.end(), i) != repeatedIndex.end())
        {
            cout << i << endl;
            continue;
        }
        parents.push_back(stoi(list[i]));
    }
    root = createTree(parents, 0);
}

void FamilyTree::exportToPersonFile(const string& filename)
{
    ofstream personsOut;
    personsOut.open(filename);
    if (!personsOut)
    {
        return;
    }
    personsOut << memberCount << "\n";
    for (int i = 0; i < memberCount; ++i)
    {
        personsOut << persons[i].id << ", ";
        personsOut << persons[i].name << ", ";
        personsOut << persons[i].birth.year << ", ";
        personsOut << persons[i].birth.month << ", ";
        personsOut << persons[i].birth.day << ", ";
        personsOut << persons[i].marriage << ", ";
        personsOut << persons[i].address << ", ";
        personsOut << persons[i].alive;
        if (!persons[i].alive)
        {
            personsOut << ", ";
            personsOut << persons[i].death.year << ", ";
            personsOut << persons[i].death.month << ", ";
            personsOut << persons[i].death.day;
        }
        personsOut << "\n";
    }
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
    for (int i = 0; i < memberCount; ++i)
    {
        file << persons_id[i];
        if (i == memberCount - 1)
            file << endl;
        else
            file << ", ";
    }
}

void FamilyTree::exportParentIndex(ofstream& file)
{
    for (int i = 0; i < memberCount; ++i)
    {
        FamilyMemberNode* presentNode = node(persons_id[i], root);
        int parent_index = parentIndex(presentNode);
        file << parent_index;
        if (i == memberCount - 1)
            file << endl;
        else
            file << ", ";
    }
}

void FamilyTree::GetNumOfGeneration(FamilyMemberNode *r, const FamilyMemberNode *p,int level, int &result) const 
{
    if(r!=NULL)
    {
        level++;
        if(r==p){ result = level; return ;}
    }
    if(FirstChild(r)!=NULL)
        GetNumOfGeneration(FirstChild(r), p, level, result);
	if(NextSibling(r)!=NULL)
		GetNumOfGeneration(NextSibling(r), p, level-1, result);
}

FamilyTree::FamilyTree() {
  root = NULL;
  memberCount = 0;
}

FamilyTree::FamilyTree(const FamilyTree &copy) {
  root = CopyTree(copy.root);
}

void FamilyTree::display() {
  displayWithConcaveShape(root, 1);
  cout << endl;
}

void FamilyTree::describeGeneration(int n) {
}

void FamilyTree::query(string name) {
}
void FamilyTree::relationship(string name1, string name2) {
}
void FamilyTree::addChild(string name) {
}
void FamilyTree::remove(string name) {
  FamilyMemberNode *person = Find(root, name);
  if (person == NULL) {
    cout << "输入信息有误!" << endl;
    return;
  }
  if (parent(root, person) != NULL) {
    FamilyMemberNode *p = parent(root, person);
    if (p->firstChild == person) {
      p->firstChild = person->nextSibling;
      delete person;
      person = NULL;
    } else {
      FamilyMemberNode *p1 = p->firstChild;
      while (p1->nextSibling != p) {
        p1 = p1->nextSibling;
      }
      p1->nextSibling = person->nextSibling;
      delete person;
      person = NULL;
    }
  } else {
    cout << "第一代人无法删除!" << endl;
  }
}
void FamilyTree::update(string name) {
  FamilyMemberNode *person = NULL;
  person = Find(root, name);
  if (person == NULL) {
    cout << "输入信息有误!" << endl;
    return;
  }
  cout << "请按下列指引修改信息！" << endl;
  cout << "请输入姓名:" << endl;
  cin >> person->person.name;
  cin.ignore();
  cout << "请输入生日(年,月,日):" << endl;
  cin >> person->person.birth.year;
  cin.ignore();
  cin >> person->person.birth.month;
  cin.ignore();
  cin >> person->person.birth.day;
  cin.ignore();
  cout << "请输入地址" << endl;
  cin >> person->person.address;
  int IsMarried;
  cout << "请输入婚姻状况,已婚输1，未婚输0" << endl;
  cin >> IsMarried;
  cin.ignore();
  int word = 1;
  while (word) {
    if (IsMarried == 1) {
      person->person.marriage = 1;
      word = 0;
    } else if (IsMarried == 0) {
      person->person.marriage = 0;
      word = 0;
    } else {
      cout << "输入数据非法,请重新输入" << endl;
      cin >> IsMarried;
    }
  }
  word = 1;
  cout << "该人是否在世，在世输1，已去世输0" << endl;
  int alive;
  cin >> alive;
  cin.ignore();
}

void FamilyTree::importFromFile(string personFile, string caseFile) {
  getPersonsFromFile(personFile);
  getTreeFromFile(caseFile);
}

void FamilyTree::exportToFile(const string &personFile, const string &caseFile) {
  exportToPersonFile(personFile);
  exportToCaseFile(caseFile);
}

FamilyTree::~FamilyTree() {
  Destroy(root);
}

FamilyMemberNode *FamilyTree::FirstChild(const FamilyMemberNode *r) const {
  if (r == NULL)
    return NULL;
  return r->firstChild;
}
FamilyMemberNode *FamilyTree::NextSibling(const FamilyMemberNode *r) const {
  if (r == NULL)
    return NULL;
  return r->nextSibling;
}

FamilyMemberNode *FamilyTree::Parent(const FamilyMemberNode *p) const {
  return Parent(root, p);
}

FamilyMemberNode *FamilyTree::Find(string Name) const {
  if (Name.empty())
    cerr << "Invalid input of Name." << endl;
  return Find(root, Name);
}

void FamilyTree::ShowInfoOf(string Name) const {
    FamilyMemberNode *p = Find(Name);
    if (p == NULL) {
      cout << "查无此人" << endl;
      return;
    }
    cout << "被查询者信息：" << endl;
    cout << p->person << endl;
    cout << "是家中第" << GetNumOfGeneration(p) << "代成员" << endl;
    cout << "其父亲信息：" << endl;
    FamilyMemberNode *q = Parent(p);
    if (q != NULL)
        cout << q->person << endl;
    else
        cout << "None" << endl;
    cout << "其孩子信息：" << endl;
    int i = 1;
    for (FamilyMemberNode *t = FirstChild(p); t != NULL; t = NextSibling(t)) {
      cout << "--第" << i << "个孩子：--" << endl;
      cout << t->person << endl;
      i++;
    }
}

void FamilyTree::ShowInfoOfGenNum(const int& n)
{
    if (n <= 0)
        cerr << "Invalid input of the num of generation." << endl;
    else if (root == NULL)
        return;
    else
    {
        int genNum = 0;
        queue<FamilyMemberNode*> q;
        FamilyMemberNode* cur, * p;
        q.push(root);
        while (!q.empty())
        {
            cur = q.front();
            q.pop();
            if (GetNumOfGeneration(cur) == n)
            {
                cout << cur->person.name << '\t';
                genNum++;
            }
            for (p = FirstChild(cur); p != NULL; p = NextSibling(p))
                q.push(p);
        }
        cout << endl;
        cout << "绗?" << n << "浠ｅ叡鏈?" << genNum << "浜?" << endl;
    }
}

int FamilyTree::GetNumOfGeneration(FamilyMemberNode *p) const {
    int NumGeneration = 0;
    GetNumOfGeneration(root, p, NumGeneration,NumGeneration);
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

vector<string> split(string phrase, string delimiter)
{
    vector<string> list;
    string s = string(std::move(phrase));
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos)
    {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}

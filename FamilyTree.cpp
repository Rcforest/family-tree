//
// Created by Rcforest on 2022/3/16.
//

#include "FamilyTree.h"



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

FamilyMemberNode *FamilyTree::createTree(Person (&persons)[100],
                                         vector<int> personsList,
                                         vector<int> parents,
                                         int root_) {
  FamilyMemberNode *r;
  for (Person person:persons) {
    if (root_ == person.id - 1) {
      r = new FamilyMemberNode(person);
      break;
    }
  }
  FamilyMemberNode *subTreeRoot, *cur;
  for (int i = 0; i < memberCount; ++i) {
    if (parents[i] == root_) {
      subTreeRoot = createTree(persons, personsList, parents, personsList[i]);
      if (r->firstChild == nullptr) {
        r->firstChild = subTreeRoot;
        cur = subTreeRoot;
      } else {
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

void FamilyTree::getPersonsFromFile(const string &filename, Person (&persons)[MAX]) {
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

void FamilyTree::getTreeFromFile(const string &filename, Person (&persons)[MAX]) {

  ifstream infile(filename);
  if (!infile.is_open()) {
    return;
  }
  vector<int> parents;
  vector<int> repeatedIndex;
  string line;
  std::getline(infile, line);
  vector<string> personList = split(line, ", ");
  int n = memberCount;
  for (int i = 0; i < n; ++i) {
    if (persons[stoi(personList[i])].recorded) {
      memberCount--;
      repeatedIndex.push_back(i);
      continue;
    }
    persons[stoi(personList[i])].recorded = true;
  }
  std::getline(infile, line);
  vector<string> parentList = split(line, ", ");
  vector<int> personsIndex;
  int root_index;
  int count = memberCount + size(repeatedIndex);
  for (int i = 0; i < count; ++i) {
    if (std::find(repeatedIndex.begin(), repeatedIndex.end(), i) != repeatedIndex.end()) {
      cout << i << endl;
      continue;
    }
    if (stoi(parentList[i]) == -1) {
      root_index = stoi(personList[i]);
    }
    personsIndex.push_back(stoi(personList[i]));
    parents.push_back(stoi(parentList[i]));
  }
  root = createTree(persons, personsIndex, parents, root_index);
}

void FamilyTree::exportToPersonFile(const string &filename)
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

void FamilyTree::exportToCaseFile(const string &filename)
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
  else
  if (!p1)
    cout << name1 << " 不在家族信息中！！" << endl;
  if(!p2)
    cout << name2 << " 不在家族信息中！！" << endl;
}
void FamilyTree::addChild(string name) {
  FamilyMemberNode *p = Find(name);
  if (!p) {
    cout << name << "不在家族信息中！！" << endl;
    return;
  }
  int num = 0, i = 0;
  cout << "添加孩子个数：";
  cin >> num;
  Person children[num];
  int flag = 1;

  while (num--) {
    int id = memberCount++;
    children[i].id = id;
    cout << "请输入姓名：" << endl;
    cin >> children[i].name;
    cout << "出生日期：(eg:0000 00 00)" << endl;
    int y, m, d;
    cin >> y >> m >> d;
    children[i].birth = Date(y, m, d);
    cout << "是否婚姻：0/1" << endl;
    cin >> children[i].marriage;
    cout << "住址：" << endl;
    cin >> children[i].address;
    cout << "是否在世：0/1" << endl;
    cin >> children[i].alive;
    if (!children[i].alive) {
      cout << "去世日期：(eg:0000 00 00)" << endl;
      cin >> y >> m >> d;
      children[i].death = Date(y, m, d);
    }
    if (flag) {
      if (!p->firstChild) {
        p->firstChild = new FamilyMemberNode(children[i]);
        p = p->firstChild;
        flag = 0;
      } else {
        p = p->firstChild;
        while (p->nextSibling)
          p = p->nextSibling;
        p->nextSibling = new FamilyMemberNode(children[i]);
        p = p->nextSibling;
        flag = 0;
      }
    } else {
      p->nextSibling = new FamilyMemberNode(children[i]);
      p = p->nextSibling;
    }
    i++;
  }
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
      memberCount -= nodeCount(person);
      delete person;
      person = NULL;
    } else {
      FamilyMemberNode *p1 = p->firstChild;
      while (p1->nextSibling != person) {
        p1 = p1->nextSibling;
      }
      p1->nextSibling = person->nextSibling;
      memberCount -= nodeCount(person);
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
  Person persons[MAX];
  getPersonsFromFile(personFile, persons);
  getTreeFromFile(caseFile, persons);
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
        cout << "第" << n << "代共有" << genNum << "人" << endl;
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

void FamilyTree::outputPersonInfo(FamilyMemberNode *root_, ofstream &personsOut) {
  FamilyMemberNode *p;
  if (root_ == nullptr) {
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
  if (!presentPerson.alive) {
    personsOut << ", ";
    personsOut << presentPerson.death.year << ", ";
    personsOut << presentPerson.death.month << ", ";
    personsOut << presentPerson.death.day;
  }
  personsOut << "\n";
  for (p = FirstChild(root_); p != nullptr; p = NextSibling(p))
    outputPersonInfo(p, personsOut);
}

void FamilyTree::outputPersonIndex(FamilyMemberNode *root_, ofstream &file, int &count) {
  if (root_ == nullptr) {
    return;
  }
  file << root_->id() - 1;
  count ++;
  if (count == memberCount) {
    file << endl;
  } else {
    file << ", ";
  }
  FamilyMemberNode *p;
  for (p = FirstChild(root_); p != nullptr; p = NextSibling(p))
    outputPersonIndex(p, file, count);
}

void FamilyTree::outputParentIndex(FamilyMemberNode *root_, ofstream &file, int &count) {
  if (root_ == nullptr) {
    return;
  }
  int parent_index;
  if (root_ == root) {
    parent_index = -1;
  } else {
    parent_index = Parent(root_)->id() - 1;
  }
  file << parent_index;
  count ++;
  if (count == memberCount) {
    file << endl;
  } else {
    file << ", ";
  }
  FamilyMemberNode *p;
  for (p = FirstChild(root_); p != nullptr ; p = p->nextSibling) {
    outputParentIndex(p, file, count);
  }
}

int FamilyTree::nodeCount(FamilyMemberNode *r) {
  FamilyMemberNode *p;
  if (r == nullptr) {
    return 0;
  }
  int subTreeNodeCountSum = 0;
  for (p = FirstChild(r); p != nullptr; p = NextSibling(p))
    subTreeNodeCountSum += nodeCount(p);
  return 1 + subTreeNodeCountSum;

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

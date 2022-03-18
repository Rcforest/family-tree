//
// Created by Rcforest on 2022/3/16.
//

#include "FamilyTree.h"

FamilyMemberNode *FamilyTree::memberNode(string name) {
  int id;
  for (int i = 0; i < memberCount; ++i) {
    if (persons[i].name == name) {
      id = i + 1;
      break;
    }
  }
  return node(id, root);
}
FamilyTree::FamilyTree() {
  root = nullptr;
}
vector<string> split(string &phrase, const string &delimiter) {
  vector<string> list;
  string s = string(std::move(phrase));
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    list.push_back(token);
    s.erase(0, pos + delimiter.length());
  }
  list.push_back(s);
  return list;
}
void FamilyTree::getPersonsFromFile(const string &filename) {
  ifstream infile(filename);
  if (!infile.is_open()) {
    return;
  }
  string line;
  string delimiter;
  int count;
  infile >> count;
  memberCount = count;
  std::getline(infile, line);
  for (int i = 0; i < count; ++i) {
    std::getline(infile, line);
    vector<string> list = split(line, ", ");
    persons[i].id = stoi(list[0]);
    persons[i].name = list[1];
    cout << persons[i].name << endl;
    persons[i].birth = Date(stoi(list[2]), stoi(list[3]), stoi(list[4]));
    persons[i].marriage = stoi(list[5]);
    persons[i].address = list[6];
    persons[i].alive = stoi(list[7]);
    if (!persons[i].alive) {
      persons[i].death = Date(stoi(list[8]), stoi(list[9]), stoi(list[10]));
    }
  }
}
void FamilyTree::getTreeFromFile(const string &filename) {
  ifstream infile(filename);
  if (!infile.is_open()) {
    return;
  }
  vector<int> person_index;
  vector<int> parents;
  string line;
  std::getline(infile, line);
  vector<string> list = split(line, ", ");
  person_index.reserve(list.size());
  for (const string &i: list) {
    person_index.push_back(stoi(i));
  }
  std::getline(infile, line);
  list = split(line, ", ");
  parents.reserve(list.size());
  for (const string &i: list) {
    parents.push_back(stoi(i));
  }
  root = createTree(person_index, parents, 0);
}
void FamilyTree::importFromFile(string personFile, string caseFile) {
  getPersonsFromFile(personFile);
  getTreeFromFile(caseFile);
}
FamilyMemberNode *FamilyTree::createTree(const vector<int> &persons_index, vector<int> parents, int root_) {
  int index = 0;
  for (int i = 0; i < memberCount; ++i) {
    if (persons_index[i] == root_) {
      index = i;
      break;
    }
  }
  FamilyMemberNode *r = new FamilyMemberNode(persons[index]);
  FamilyMemberNode *subTreeRoot, *cur;
  for (int i = 0; i < memberCount; ++i) {
    if (parents[i] == root_) {
      subTreeRoot = createTree(persons_index, parents, i);
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
FamilyMemberNode *FamilyTree::node(int id, FamilyMemberNode *root_) {
  FamilyMemberNode *p;
  if (root_ == nullptr || root_->id() == id) {
    return root_;
  }
  for (p = root_->firstChild; p != nullptr; p = p->nextSibling) {
    FamilyMemberNode *presentNode = node(id, p);
    if (presentNode) return presentNode;
  }
  return nullptr;
}
FamilyMemberNode *FamilyTree::parent(FamilyMemberNode *root_, const FamilyMemberNode *child) const {
  if (root_ == nullptr) return nullptr;
  FamilyMemberNode *p;
  for (p = root_->firstChild; p != nullptr; p = p->nextSibling) {
    if (p == child) return root_;
  }
  for (p = root_->firstChild; p != nullptr; p = p->nextSibling) {
    FamilyMemberNode *q = parent(p, child);
    if (q) return q;
  }
  return nullptr;
}
int FamilyTree::parentIndex(const FamilyMemberNode *child) const {
  if (child == root) {
    return -1;
  }
  return parent(root, child)->id() - 1;
}
string FamilyTree::getName(FamilyMemberNode *r) {
  for (const Person &i: persons) {
    if (i.id == r->id())
      return i.name;
  }
  return "\0";
}

void FamilyTree::displayWithConcaveShape(FamilyMemberNode *root_, int level) {
  FamilyMemberNode *p;
  if (root_ != nullptr) {
    cout << endl;
    string name = getName(root_);
    for (int i = 0; i < level - 1; ++i) {
      cout << "   ";
    }
    cout << name;
    for (p = root_->firstChild; p != nullptr; p = p->nextSibling) {
      displayWithConcaveShape(p, level + 1);
    }
  }
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

}
void FamilyTree::update(string name) {

}
void FamilyTree::exportToFile(const string &personFile, const string &caseFile) {
  exportToPersonFile(personFile);
  exportToCaseFile(caseFile);
}
void FamilyTree::exportToPersonFile(const string &filename) {
  ofstream personsOut;
  personsOut.open(filename);
  if (!personsOut) {
    return;
  }
  personsOut << memberCount << "\n";
  for (int i = 0; i < memberCount; ++i) {
    personsOut << persons[i].id << ", ";
    personsOut << persons[i].name << ", ";
    personsOut << persons[i].birth.year << ", ";
    personsOut << persons[i].birth.month << ", ";
    personsOut << persons[i].birth.day << ", ";
    personsOut << persons[i].marriage << ", ";
    personsOut << persons[i].address << ", ";
    personsOut << persons[i].alive;
    if (!persons[i].alive) {
      personsOut << ", ";
      personsOut << persons[i].death.year << ", ";
      personsOut << persons[i].death.month << ", ";
      personsOut << persons[i].death.day;
    }
    personsOut << "\n";
  }
  personsOut.close();
}
void FamilyTree::exportToCaseFile(const string &filename) {
  ofstream caseOut;
  caseOut.open(filename);
  if (!caseOut) {
    return;
  }
  exportPersonIndex(caseOut);
  exportParentIndex(caseOut);
  caseOut.close();
}
void FamilyTree::exportPersonIndex(ofstream &file) {
  queue<FamilyMemberNode *> q;
  int count = 0;
  if (root == nullptr) return;
  q.push(root);
  while (!q.empty()) {
    FamilyMemberNode *p = q.front();
    count++;
    if (count == memberCount) file << p->id() - 1 << endl;
    else file << p->id() - 1 << ", ";
    q.pop();
    for (p = p->firstChild; p != nullptr; p = p->nextSibling) {
      q.push(p);
    }
  }
}
void FamilyTree::exportParentIndex(ofstream &file) {
  for (int i = 0; i < memberCount - 1; ++i) {
    FamilyMemberNode *presentNode = node(i + 1, root);
    file << parentIndex(presentNode) << ", ";
  }
  file << parentIndex(node(memberCount, root)) << "\n";
}


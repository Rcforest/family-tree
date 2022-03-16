//
// Created by Rcforest on 2022/3/16.
//
#include "FamilyMemberNode.h"
#include <vector>
#include <fstream>
#ifndef FAMILY_TREE__FAMILYTREE_H_
#define FAMILY_TREE__FAMILYTREE_H_
#define MAX 30
class FamilyTree {
 protected:
  FamilyMemberNode *root;
  Person persons[MAX];
  int memberCount;
  FamilyMemberNode memberNode(string name); //根据名字确定节点
  FamilyMemberNode *createTree(const vector<int> &persons_index, vector<int> parents, int root_);
  void getPersonsFromFile(const string &filename);
  void getTreeFromFile(const string &filename);
 public:
  FamilyTree();
  void display();
  void describeGeneration(int n);
  void query(string name);
  void relationship(string name1, string name2);
  void addChild(string name);
  void remove(string name);
  void update(string name);
  void importFromFile(string personFile, string caseFile);
  void exportToFile();
};

vector<string> split(char *phrase, string delimiter);

#endif //FAMILY_TREE__FAMILYTREE_H_
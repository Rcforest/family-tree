//
// Created by Rcforest on 2022/3/16.
//
#include "FamilyMemberNode.h"
#ifndef FAMILY_TREE__FAMILYTREE_H_
#define FAMILY_TREE__FAMILYTREE_H_

class FamilyTree {
 protected:
  FamilyMemberNode *root;
  FamilyMemberNode memberNode(string name); //根据名字确定节点
 public:
  FamilyTree();
  void display();
  void describeGeneration(int n);
  void query(string name);
  void relationship(string name1, string name2);
  void addChild(string name);
  void remove(string name);
  void update(string name);
  void importFromFile();
  void exportToFile();
};

#endif //FAMILY_TREE__FAMILYTREE_H_

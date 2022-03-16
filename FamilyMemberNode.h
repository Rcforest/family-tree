//
// Created by Rcforest on 2022/3/16.
//
#include <string>
using namespace std;
#ifndef FAMILY_TREE__FAMILYMEMBERNODE_H_
#define FAMILY_TREE__FAMILYMEMBERNODE_H_

struct Date {
  int year;
  int month;
  int day;
  Date()=default;
  Date(int y, int m, int d);
};

struct Person {
  string name;
  Date birth;
  bool marriage;
  string address;
  bool alive;
  Date death;
  Person()=default;
  Person(string name, Date birth, bool marriage);
};

class FamilyMemberNode {
 protected:
  Person person;
  FamilyMemberNode *firstChild;
  FamilyMemberNode *nextSibling;
 public:
  explicit FamilyMemberNode();
  FamilyMemberNode(Person person, FamilyMemberNode *fChild, FamilyMemberNode *nSibling);
};

#endif //FAMILY_TREE__FAMILYMEMBERNODE_H_

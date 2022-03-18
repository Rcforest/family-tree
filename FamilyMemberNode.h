//
// Created by Rcforest on 2022/3/16.
//
#include <string>
#include <iostream>
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
  int id;
  string name;
  Date birth;
  bool marriage;
  string address;
  bool alive;
  Date death;
  bool recorded;
  Person();
  Person(int id, string name, Date birth, bool marriage, string address, bool alive=true, Date death=Date(-1, -1, -1));
};

class FamilyMemberNode {
 protected:
  Person person;
 public:
  explicit FamilyMemberNode();
  FamilyMemberNode(Person person, FamilyMemberNode *fChild, FamilyMemberNode *nSibling);
  FamilyMemberNode(Person person);
  FamilyMemberNode *firstChild;
  FamilyMemberNode *nextSibling;
  int id();
};

#endif //FAMILY_TREE__FAMILYMEMBERNODE_H_

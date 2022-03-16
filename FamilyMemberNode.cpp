//
// Created by Rcforest on 2022/3/16.
//

#include "FamilyMemberNode.h"
Person::Person(int id, string name, Date birth, bool marriage, string address, bool alive, Date death) {
  id = id;
  name = name;
  birth = birth;
  marriage = marriage;
  address = address;
  alive = alive;
  death = death;
}
Date::Date(int y, int m, int d) {
  year = y;
  month = m;
  day = d;
}

FamilyMemberNode::FamilyMemberNode() {
  firstChild = nullptr;
  nextSibling = nullptr;
}
FamilyMemberNode::FamilyMemberNode(Person person1, FamilyMemberNode *fChild, FamilyMemberNode *nSibling) {
  person = person1;
  firstChild = fChild;
  nextSibling = nSibling;
}
FamilyMemberNode::FamilyMemberNode(Person person1) {
  person = person1;
  firstChild = nullptr;
  nextSibling = nullptr;
}
int FamilyMemberNode::id() {
  return person.id;
}


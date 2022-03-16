//
// Created by Rcforest on 2022/3/16.
//

#include "FamilyMemberNode.h"
Date::Date(int y, int m, int d) {
  year = y;
  month = m;
  day = d;
}

Person::Person(string name, Date birth, bool marriage) {
  name = name;
  birth = birth;
  marriage = marriage;
  alive = true;
}
FamilyMemberNode::FamilyMemberNode() {
  firstChild = nullptr;
  nextSibling = nullptr;
}
FamilyMemberNode::FamilyMemberNode(Person person, FamilyMemberNode *fChild, FamilyMemberNode *nSibling) {
  person = person;
  firstChild = fChild;
  nextSibling = nSibling;
}


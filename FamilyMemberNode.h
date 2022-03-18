//
// Created by Rcforest on 2022/3/16.
//
#include <string>
#include<iostream>
using namespace std;
#ifndef FAMILY_TREE__FAMILYMEMBERNODE_H_
#define FAMILY_TREE__FAMILYMEMBERNODE_H_

struct Date {
	int year;
	int month;
	int day;
	Date();
	Date(int y, int m, int d);

	Date& operator=(const Date& t);
	ostream& operator<<(ostream& out);
};

struct Person {
	string name;
	Date birth;
	bool marriage;
	string address;
	bool alive;
	Date death;
	Person();
	Person(const Person& temp);
	Person(string Name, Date Birth, bool Marriage, string Address = "NoAddress", bool Alive = false, Date Death = Date());

	Person& operator=(const Person& temp);
	ostream& operator<<(ostream& out);
};

class FamilyMemberNode {
 protected:
	Person person;
	FamilyMemberNode *firstChild;
	FamilyMemberNode *nextSibling;
 public:
	FamilyMemberNode();
	FamilyMemberNode(Person person, FamilyMemberNode *fChild=NULL, FamilyMemberNode *nSibling=NULL);

	friend class FamilyTree;
};

#endif //FAMILY_TREE__FAMILYMEMBERNODE_H_

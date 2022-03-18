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
	ostream& OutputDate(ostream& out) const;

	friend class Person;
};

ostream& operator<<(ostream& out, const Date& date);

struct Person {
	int id;
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
	ostream& OutputPerson(ostream& out) const;
};

ostream& operator<<(ostream& out, const Person& p);

class FamilyMemberNode {
 protected:
	Person person;
	FamilyMemberNode *firstChild;
	FamilyMemberNode *nextSibling;
 public:
	FamilyMemberNode();
	FamilyMemberNode(Person person, FamilyMemberNode *fChild=NULL, FamilyMemberNode *nSibling=NULL);
	int id();
	friend class FamilyTree;
};

#endif //FAMILY_TREE__FAMILYMEMBERNODE_H_

//
// Created by Rcforest on 2022/3/16.
//

#include "FamilyMemberNode.h"
Date::Date()
{
	year = month = day = 0;
}
Date::Date(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

Date& Date::operator=(const Date& t)
{
	year = t.year;
	month = t.month;
	day = t.day;

	return (*this);
}

ostream& Date::operator<<(ostream& out)
{
	out << year << "\b\b\b\b\t年" << month << "\b\b\t月" << day << "\b\b\t日" << endl;
	return out;
}

Person::Person() :birth(), death()
{
	name = "NoName";
	marriage = false;
	address = "NoAddress";
	alive = false;
}

Person::Person(const Person& temp)
{
	name = temp.name;
	birth = temp.birth;
	marriage = temp.marriage;
	address = temp.address;
	alive = temp.alive;
	death = temp.death;
}

Person::Person(string Name, Date Birth, bool Marriage, string Address, bool Alive, Date Death) {
	name = name;
	birth = birth;
	marriage = marriage;
	address = address;
	alive = alive;
	death = death;
}
Person& Person::operator=(const Person& temp)
{
	name = temp.name;
	birth = temp.birth;
	marriage = temp.marriage;
	address = temp.address;
	alive = temp.alive;
	death = temp.death;
	return (*this);
}
ostream& Person::operator<<(ostream& out)
{
	// TODO: 在此处插入 return 语句
}
FamilyMemberNode::FamilyMemberNode() {
	firstChild = nullptr;
	nextSibling = nullptr;
}

FamilyMemberNode::FamilyMemberNode(Person p, FamilyMemberNode *fChild, FamilyMemberNode *nSibling) {
	person = p;
	firstChild = fChild;
	nextSibling = nSibling;
}
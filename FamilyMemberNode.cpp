//
// Created by Rcforest on 2022/3/16.
//

#include "FamilyMemberNode.h"
Date::Date()
{
	year = month = day = 0;
}

Date::Date(const Date& t)
{
	year = t.year;
	month = t.month;
	day = t.day;
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

ostream& Date::OutputDate(ostream& out) const
{
	out << year << "\b\b\b\b\t��" << month << "\b\b\t��" << day << "\b\b\t��\n";
	return out;
}

Person::Person() :birth(Date()), death(Date())
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
	id = temp.id;
	recorded = temp.recorded;
}

Person::Person(string Name, Date Birth, bool Marriage, string Address, bool Alive, Date Death, bool R,int ID) {
	name = name;
	birth = birth;
	marriage = marriage;
	address = address;
	alive = alive;
	death = death;
	recorded = R;
	id = ID;
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
ostream& Person::OutputPerson(ostream& out) const
{
	out << "������" << name << '\n';
	out << "�������ڣ�" << birth << '\n';
	out << "����״����" << (marriage ? "Yes" : "No") << '\n';
	out << "��ַ��" << address << '\n';
	out << "ȥ�����ڣ�";
	if (alive)
		out << "None";
	else
		out << death;
	out << '\n';
	return out;
}
FamilyMemberNode::FamilyMemberNode() {
	firstChild = NULL;
	nextSibling = NULL;
}

FamilyMemberNode::FamilyMemberNode(Person p, FamilyMemberNode* fChild, FamilyMemberNode* nSibling) {
	person = p;
	firstChild = fChild;
	nextSibling = nSibling;
}

int FamilyMemberNode::id()
{
	return person.id;
}

ostream& operator<<(ostream& out, const Date& date)
{
	date.OutputDate(out);
	return out;
}

ostream& operator<<(ostream& out, const Person& p)
{
	p.OutputPerson(out);
	return out;
}

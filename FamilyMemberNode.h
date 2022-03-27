#pragma once
//
// Created by Rcforest on 2022/3/16.
//
#pragma warning(disable: 4290)            // for VS2019
#pragma warning(disable: 4996)            // for VS2019
#include <string>
#include<iostream>
using namespace std;
#ifndef FAMILY_TREE__FAMILYMEMBERNODE_H_
#define FAMILY_TREE__FAMILYMEMBERNODE_H_

struct Date
{
    int year;
    int month;
    int day;
    Date();
    Date(const Date& t);
    Date(int y, int m, int d);
    Date& operator=(const Date& t);
    bool operator>=(const Date& t) const;
    bool operator<=(const Date& t) const;
    bool operator>(const Date& t) const;
    bool operator<(const Date& t) const;
    bool operator==(const Date& t) const;
    bool operator!=(const Date& t) const;

    ostream& OutputDate(ostream& out) const;

    friend class Person;
};

ostream& operator<<(ostream& out, const Date& date);

struct Person
{
    int id;
    string name;
    Date birth;
    bool marriage;
    string address;
    bool alive;
    Date death;
    bool recorded;
    Person();
    Person(const Person& temp);
    Person(string Name,
        const Date& Birth,
        bool Marriage,
        string Address = "NoAddress",
        bool Alive = false,
        const Date& Death = Date(),
        bool R = true,
        int ID = -1);

    Person& operator=(const Person& temp);
    ostream& OutputPerson(ostream& out) const;
};

ostream& operator<<(ostream& out, const Person& p);

class FamilyMemberNode
{
protected:
    Person person;
    FamilyMemberNode* firstChild;
    FamilyMemberNode* nextSibling;
public:
    FamilyMemberNode();
    explicit FamilyMemberNode(const Person& person, FamilyMemberNode* fChild = NULL, FamilyMemberNode* nSibling = NULL);
    friend class FamilyTree;
};

#endif //FAMILY_TREE__FAMILYMEMBERNODE_H_

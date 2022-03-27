#pragma once
//
// Created by Rcforest on 2022/3/16.
//
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include "FamilyMemberNode.h"
#ifndef FAMILY_TREE__FAMILYTREE_H_
#define FAMILY_TREE__FAMILYTREE_H_
#define MAX 100
using namespace std;

class FamilyTree
{
protected:

    FamilyMemberNode* root;
    int memberCount;
    //assitant func

    /* editor hhl*/
    FamilyMemberNode* createTree(Person (& persons)[100],
        vector<int> personsList,
        vector<int> parents,
        int root_);
    void getPersonsFromFile(const string& filename, Person (& persons)[MAX]);
    void getTreeFromFile(const string& filename, Person (& persons)[MAX]);
    void outputPersonInfo(FamilyMemberNode* root_, ofstream& personsOut);
    void outputPersonIndex(FamilyMemberNode* root_, ofstream& file, int& count);
    void outputParentIndex(FamilyMemberNode* root_, ofstream& file, int& count);
    void exportToPersonFile(const string& filename);
    void exportToCaseFile(const string& filename);
    void exportPersonIndex(ofstream& file);
    void exportParentIndex(ofstream& file);
    void displayWithConcaveShape(FamilyMemberNode* root_, int level);
    bool isValidBirth(const Date& presentBirth, const Date& parentBirth);
    bool isValidDeath(const Date& presentBirth, const Date& presentDeath);
    /* editor lhy */
    void Destroy(FamilyMemberNode*& r);
    FamilyMemberNode* Parent(FamilyMemberNode* r, const FamilyMemberNode* cur) const;
    FamilyMemberNode* CopyTree(FamilyMemberNode* r);
    FamilyMemberNode* Find(FamilyMemberNode* r, const string& Name) const;
    void GetNumOfGeneration(FamilyMemberNode* r, const FamilyMemberNode* p, int level, int& result) const;
    int nodeCount(FamilyMemberNode* r);
    /**************/
public:
    FamilyTree();
    FamilyTree(const FamilyTree&);

    /* editor hhl */
    void display();
    void relationship(const string& name1, const string& name2) const;
    void addChild(const string& name);
    void remove(const string& name);
    void update(string name);
    void importFromFile(const string& personFile, const string& caseFile);
    void exportToFile(const string& personFile, const string& caseFile);

    /* editor lhy */
    ~FamilyTree();
    FamilyMemberNode* FirstChild(const FamilyMemberNode* r) const;
    FamilyMemberNode* NextSibling(const FamilyMemberNode* r) const;
    FamilyMemberNode* Parent(const FamilyMemberNode* p) const;
    FamilyMemberNode* Find(const string& Name) const;    //根据名字确定节点
    void ShowInfoOf(const string& Name) const;            //按照姓名查询，输出成员信息
    void ShowInfoOfGenNum(const int& n);
    int GetNumOfGeneration(FamilyMemberNode* p) const;
    FamilyTree& operator=(const FamilyTree& copy);
    /**************/
};
vector<string> split(string phrase, const string& delimiter);

#endif //FAMILY_TREE__FAMILYTREE_H_

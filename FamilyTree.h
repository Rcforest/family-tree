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
enum Status
{
	SUCCESS, FAILED, ERROR
};

class FamilyTree {
protected:

	FamilyMemberNode* root;
	int memberCount;
	//assitant func

	/* editor hhl*/
    FamilyMemberNode *createTree(Person (&persons)[100],
                                 vector<int> personsList,
                                 vector<int> parents,
                                 int root_);
	FamilyMemberNode* parent(FamilyMemberNode* root_, const FamilyMemberNode* child) const;
	FamilyMemberNode* node(int id, FamilyMemberNode* root_);
	void getPersonsFromFile(const string& filename, Person (&persons)[MAX]);
	void getTreeFromFile(const string& filename, Person (&persons)[MAX]);
    void outputPersonInfo(FamilyMemberNode *root_, ofstream &personsOut);
    void outputPersonIndex(FamilyMemberNode *root_, ofstream &file, int &count);
    void outputParentIndex(FamilyMemberNode *root_, ofstream &file, int &count);
	void exportToPersonFile(const string &filename);
	void exportToCaseFile(const string &filename);
	void exportPersonIndex(ofstream& file);
	void exportParentIndex(ofstream& file);
	void displayWithConcaveShape(FamilyMemberNode* root_, int level);
    bool isValidBirth(Date presentBirth, Date parentBirth);
    bool isValidDeath(Date presentBirth, Date presentDeath);
	/* editor lhy */
	void Destroy(FamilyMemberNode*& r);
	FamilyMemberNode* Parent(FamilyMemberNode* r, const FamilyMemberNode* cur) const;
	FamilyMemberNode* CopyTree(FamilyMemberNode* r);
	FamilyMemberNode* Find(FamilyMemberNode* r, const string& Name) const;
	void GetNumOfGeneration(FamilyMemberNode* r, const FamilyMemberNode* p,int level, int& result) const;
    int nodeCount(FamilyMemberNode* r);
	/**************/
public:
	FamilyTree();
	FamilyTree(const FamilyTree&);

	/* editor hhl */
	void display();
	void describeGeneration(int n);
	void query(string name);
	void relationship(string name1, string name2);
	void addChild(string name);
	void remove(string name);
	void update(string name);
	void importFromFile(string personFile, string caseFile);
	void exportToFile(const string& personFile, const string& caseFile);

	/* editor lhy */
	~FamilyTree();
	FamilyMemberNode* FirstChild(const FamilyMemberNode* r) const;
	FamilyMemberNode* NextSibling(const FamilyMemberNode* r) const;
	FamilyMemberNode* Parent(const FamilyMemberNode* p) const;
	FamilyMemberNode* Find(string Name) const;	//根据名字确定节点
	void ShowInfoOf(string Name) const;			//按照姓名查询，输出成员信息
	void ShowInfoOfGenNum(const int& n);
	int GetNumOfGeneration(FamilyMemberNode* p) const;
	FamilyTree& operator=(const FamilyTree& copy);
	/**************/
};
vector<string> split(string phrase, string delimiter);

#endif //FAMILY_TREE__FAMILYTREE_H_

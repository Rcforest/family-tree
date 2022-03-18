//
// Created by Rcforest on 2022/3/16.
//
#include "FamilyMemberNode.h"
#ifndef FAMILY_TREE__FAMILYTREE_H_
#define FAMILY_TREE__FAMILYTREE_H_

enum Status
{
	SUCCESS, FAILED, ERROR
};

class FamilyTree {
 protected:

	FamilyMemberNode *root;
	//assitant func


	/* editor lhy */
	void Destroy(FamilyMemberNode*& r);
	FamilyMemberNode* Parent(FamilyMemberNode* r, const FamilyMemberNode* cur) const;
	FamilyMemberNode* CopyTree(FamilyMemberNode* r);
	FamilyMemberNode* Find(FamilyMemberNode* r, string Name) const;
	Status GetNumOfGeneration(FamilyMemberNode* r,const FamilyMemberNode* p, int& n) const;

	void ShowInfoOf(string name) const;
	/**************/
 public:
	FamilyTree();
	FamilyTree(const FamilyTree&);
	void display();
	void describeGeneration(int n);
	void query(string name);
	void relationship(string name1, string name2);
	void addChild(string name);
	void remove(string name);
	void update(string name);
	void importFromFile();
	void exportToFile();

	/* editor lhy */
	~FamilyTree();
	FamilyMemberNode* FirstChild(const FamilyMemberNode* r) const;
	FamilyMemberNode* NextSibling(const FamilyMemberNode* r) const;
	FamilyMemberNode* Parent(const FamilyMemberNode* p) const;
	FamilyMemberNode* Find(string Name) const; //根据名字确定节点

	int GetNumOfGeneration(FamilyMemberNode* p) const;
	FamilyTree& operator=(const FamilyTree& copy);
	/**************/
};

vector<string> split(char *phrase, string delimiter);

#endif //FAMILY_TREE__FAMILYTREE_H_

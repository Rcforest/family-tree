//
// Created by Rcforest on 2022/3/16.
//

#include "FamilyTree.h"

void FamilyTree::Destroy(FamilyMemberNode*& r)
{
    FamilyMemberNode* p;
    if (r != NULL)
    {
        for (p = FirstChild(r); p != NULL; p = NextSibling(p))
            Destroy(p);
        delete r; r = NULL;
    }
}

FamilyMemberNode* FamilyTree::Parent(FamilyMemberNode* r, const FamilyMemberNode* cur) const
{
    if (r == NULL) return NULL;				// 空二叉树

    FamilyMemberNode* p;		// 孩子 
    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
        if (p == cur) return r;				// cur是r的孩子

    for (p = FirstChild(r); p != NULL; p = NextSibling(p)) {
        FamilyMemberNode* q;
        q = Parent(p, cur);			        // 在子树上求cur的双亲	
        if (q != NULL) return q;			// 双亲在子树上
    }
    return NULL;							// 未找到双亲
}

FamilyMemberNode* FamilyTree::CopyTree(FamilyMemberNode* r)
{
    if (r == NULL)
        return NULL;
    FamilyMemberNode* t = new FamilyMemberNode(r->person);
    FamilyMemberNode* subTreeRoot, * cur = NULL, * p;
    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
    {
        subTreeRoot = CopyTree(p);
        if (t->firstChild == NULL)
        {
            t->firstChild = subTreeRoot;
            cur = subTreeRoot;
        }
        else
        {
            cur->nextSibling = subTreeRoot;
            cur = subTreeRoot;
        }
    }
    return t;
}

FamilyMemberNode* FamilyTree::Find(FamilyMemberNode* r, string Name) const
{
    if (r->person.name == Name)
        return r;
    FamilyMemberNode* p;
    for (p = FirstChild(r); p != NULL; p = NextSibling(p))
        if (p->person.name == Name) return p;
}

Status FamilyTree::GetNumOfGeneration(FamilyMemberNode* r, const FamilyMemberNode* p, int& n) const
{
    if (p == NULL)
        return ERROR;
    if (r == p)
        return SUCCESS;
    n++;
    for (FamilyMemberNode* t = FirstChild(r); t != NULL; t = NextSibling(t))
    {
        return GetNumOfGeneration(t, p, n);
    }
}

void FamilyTree::ShowInfoOf(string Name) const
{
    FamilyMemberNode* p = Find(Name);
    if (p == NULL)
    {
        cout << "查无此人" << endl;
        return;
    }
    

}

FamilyTree::FamilyTree()
{
    root = NULL;
}

FamilyTree::FamilyTree(const FamilyTree& copy)
{
    root = CopyTree(copy.root);
}

void FamilyTree::describeGeneration(int n)
{
}

FamilyTree::~FamilyTree()
{
    Destroy(root);
}

FamilyMemberNode* FamilyTree::FirstChild(const FamilyMemberNode* r) const
{
    if (r == NULL)
        return NULL;
    return r->firstChild;
}
FamilyMemberNode* FamilyTree::NextSibling(const FamilyMemberNode* r) const
{
    if (r == NULL)
        return NULL;
    return r->nextSibling;
}

FamilyMemberNode* FamilyTree::Parent(const FamilyMemberNode* p) const
{
    return Parent(root, p);
}

FamilyMemberNode* FamilyTree::Find(string Name) const
{
    if (Name.empty())
        cerr << "Invalid input of Name." << endl;
    return Find(root,Name);
}

int FamilyTree::GetNumOfGeneration(FamilyMemberNode* p) const
{
    int NumGeneration = 1;
    if (GetNumOfGeneration(root, p, NumGeneration) == SUCCESS)
        return NumGeneration;
    cerr << "未找到该节点" << endl;
}

FamilyTree& FamilyTree::operator=(const FamilyTree& copy)
{
    if (&copy != this)
    {
        Destroy(root);
        root = CopyTree(copy.root);
    }
    return (*this);
}

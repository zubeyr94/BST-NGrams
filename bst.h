
//
// Zübeyr Furkan Eryilmaz
// 21202676
// CS 202 - 01
//

// bst.h

#include <iostream>

#ifndef BST_H
#define BST_H

using namespace std;

typedef string TreeItemType;

//TreeNode
//Node implementation to create a tree
class TreeNode
{
private:
    TreeNode();
    TreeItemType item;
    TreeNode *leftChildPtr, *rightChildPtr;
    int count;

    friend class NgramTree;
};

//NgramTree  class
class NgramTree
{
public:
    NgramTree();
    ~NgramTree();

    void addNgram(string ngram);
    int getTotalNgramCount();
    void printNgramFrequencies();
    int getHeight( TreeNode* subTreePtr);
    bool isComplete();
    bool isFull();
    void generateTree(string fileName, int n);

protected:
    //Helper functions to use recursion
    void getTotalNgramCount( TreeNode* subTreePtr, int &counter);
    void printNgramFrequencies( TreeNode* subTreePtr);
    bool isComplete( TreeNode* subTreePtr);
    bool isFull( TreeNode* subTreePtr);
    //Destroy function to call in destructor
    void destroyTree( TreeNode* &subTreePtr);

private:
    TreeNode* root;
};


#endif // BST_H

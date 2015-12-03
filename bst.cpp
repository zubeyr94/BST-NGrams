
//
// Zübeyr Furkan Eryilmaz
// 21202676
// CS 202 - 01
//

#include "bst.h"
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

NgramTree::NgramTree()
{
    root = NULL;
}

NgramTree::~NgramTree()
{
    //Destructs
    destroyTree(root);
}

void NgramTree::addNgram(string ngram)
{
    /*
        If tree is empty directly create new node and add
        If is not empty find the place then if it is not repeated, add node
                                            if it is repeated, increment the count of ngram
    */
    TreeNode* curr = root;
    TreeNode** parent = NULL;
    bool isRepeated = false;

    if ( curr == NULL)
    {
        root = new TreeNode();
        root -> item = ngram;
        root -> count = 1;
    }
    else
    {
        while ( curr != NULL)
        {
            if (ngram.compare(curr -> item) > 0)
            {
                parent = &(curr -> rightChildPtr);
                curr = curr -> rightChildPtr;
            }

            else if ( ngram.compare(curr -> item) < 0)
            {
                parent = &(curr -> leftChildPtr);
                curr = curr -> leftChildPtr;
            }

            else
            {
                (curr -> count)++;
                isRepeated = true;
                break;
            }
        }

        if (!isRepeated)
        {
            *parent = new TreeNode();
            (*parent) -> item = ngram;
            (*parent) -> count = 1;
        }
     }

}

int NgramTree::getTotalNgramCount()
{
    int counter = 0;

    //Call helper to use recursion
    getTotalNgramCount( root, counter);

    return counter;
}

void NgramTree::getTotalNgramCount( TreeNode* subTreePtr, int &counter)
{
    //By doing preorder traversal counts the number of nodes
    if ( subTreePtr != NULL)
    {
        counter ++;
        getTotalNgramCount( subTreePtr -> leftChildPtr, counter);
        getTotalNgramCount( subTreePtr -> rightChildPtr, counter);
    }
}

void NgramTree::printNgramFrequencies()
{
    //Call helper to use recursion
    printNgramFrequencies( root);
    cout << endl;
}

void NgramTree::printNgramFrequencies( TreeNode* subTreePtr)
{
    //By doing inorder traversal print outs the tree items and counts
    if ( subTreePtr != NULL)
    {
        printNgramFrequencies( subTreePtr -> leftChildPtr);

        cout << "\"" << subTreePtr -> item << "\" " << "appears " << subTreePtr -> count << " time(s)" << endl;

        printNgramFrequencies( subTreePtr -> rightChildPtr);
    }
}

int NgramTree::getHeight( TreeNode* subTreePtr)
{
    // Implemented using rule of that height of a tree is equals to maximum height of its subtrees + 1
    int height = 0;

    if ( subTreePtr != NULL)
    {
        height = 1 + max( getHeight(subTreePtr -> leftChildPtr), getHeight(subTreePtr -> rightChildPtr));
    }

    return height;
}

bool NgramTree::isComplete()
{
    //Call helper to use recursion
    return isComplete(root);
}

bool NgramTree::isComplete(TreeNode* subTreePtr)
{
    // A tree is not complete if it contains a node that's right subtree's height not equal to or 1 less than
    //left subtree's height
    //A tree is complete:
    //      if left subtree's height of a node is equal to right subtree's height and if its left subtree is full tree
    //          it is complete if right subtree is complete
    //      else which means left subtree's height of a node is equal to right subtree's height+1 and if its right subtree
    //      is full tree
    //          it is complete if left subtree is complete
    if ( subTreePtr != NULL)
    {
        int leftHeight = getHeight( subTreePtr -> leftChildPtr);
        int rightHeight = getHeight( subTreePtr -> rightChildPtr);

        if ( leftHeight != rightHeight && leftHeight != rightHeight + 1)
            return false;

        if ( leftHeight == rightHeight)
        {
            if( isFull(subTreePtr -> leftChildPtr))
            {
                return isComplete( subTreePtr -> rightChildPtr);
            }

            return false;
        }

        else
        {
            if ( isFull(subTreePtr -> rightChildPtr))
            {
                return isComplete( subTreePtr -> leftChildPtr);
            }

            return false;
        }
    }

    return true;
}

bool NgramTree::isFull()
{
    return isFull( root);
}

bool NgramTree::isFull( TreeNode* subTreePtr)
{
    //If the tree is full number elements in the tree should be equal to
    //2 to the height - 1
    if ( root != NULL)
    {
        int counter = 0;
        getTotalNgramCount( subTreePtr, counter);

        return (counter == (pow( 2, getHeight(subTreePtr)) - 1));
    }

    return true;
}

void NgramTree::generateTree(string fileName, int n)
{
    //Read from file and add to tree one by one
    ifstream file;
    file.open(fileName.c_str());

    string word;

    while (file >> word)
    {
        if (word.length() >= n)
        {
            for (int i = 0; i <= word.length() - n; i++)
            {
                addNgram(word.substr(i,n));
            }
        }
    }
}

void NgramTree::destroyTree( TreeNode* &subTreePtr)
{
    //By doing postorder traversal deletes all the tree
    if ( subTreePtr != NULL)
    {
        destroyTree(subTreePtr -> leftChildPtr);
        destroyTree(subTreePtr -> rightChildPtr);

        delete subTreePtr;
        subTreePtr = NULL;
    }
}

TreeNode::TreeNode()
{
    item = "";
    leftChildPtr = NULL;
    rightChildPtr = NULL;
    count = 0;
}


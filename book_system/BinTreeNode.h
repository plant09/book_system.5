#ifndef BINTREENODE_H
#define BINTREENODE_H
#include"assistance.h"

struct BinTreeNode
{
	book_data data;
	BinTreeNode* leftChild;
	BinTreeNode* rightChild;
	BinTreeNode(const book_data& d, BinTreeNode* lChild = NULL, BinTreeNode* rChild = NULL)
	{
		data = d;
		leftChild = lChild;
		rightChild = rChild;
	}
};

#endif


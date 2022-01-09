#ifndef BINSORTTREE_H
#define BINSORTTREE_H

#include"BinTreeNode.h"
#include"assistance.h"

class BinSortTree
{
protected:
	BinTreeNode* root;
public:
	//构造函数
	BinSortTree();

	//通过id查找结点
	BinTreeNode* find(const int& key, BinTreeNode*& f)const;

	//插入结点
	status insert(const book_data& e);

	//删除结点
	void delete_node(BinTreeNode*& p);

	//显示所有结点信息
	void show_all_data(BinTreeNode* p);

	//获取根结点
	BinTreeNode* get_root();
};

#endif


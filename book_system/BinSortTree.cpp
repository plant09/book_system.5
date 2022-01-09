#include "BinSortTree.h"

BinSortTree::BinSortTree()
{
	root = nullptr;
}

BinTreeNode* BinSortTree::find(const int& key, BinTreeNode*& f)const
{
	BinTreeNode* p = root;
	f = nullptr;
	while (p != nullptr && p->data.book_id != key)
	{
		if (key < p->data.book_id)
		{
			f = p;
			p = p->leftChild;
		}
		else
		{
			f = p;
			p = p->rightChild;
		}
	}
	return p;
}

status BinSortTree::insert(const book_data& e)
{
	BinTreeNode* f;
	if (find(e.book_id, f) == nullptr)
	{
		BinTreeNode* p;
		p = new BinTreeNode(e);
		if (root == nullptr)
			root = p;
		else if (e.book_id < f->data.book_id)
			f->leftChild = p;
		else
			f->rightChild = p;
		return SUCCESS;
	}
	else
		return FAIL;
}

void BinSortTree::delete_node(BinTreeNode*& p)
{
	BinTreeNode* tmpPtr, * tmpF;
	if (p->leftChild == nullptr && p->rightChild == nullptr)
	{
		delete p;
		p = NULL;
	}
	else if (p->leftChild == NULL)
	{
		tmpPtr = p;
		p = p->rightChild;
		delete tmpPtr;
	}
	else if (p->rightChild == NULL)
	{
		tmpPtr = p;
		p = p->leftChild;
		delete tmpPtr;
	}
	else
	{
		tmpF = p;
		tmpPtr = p->leftChild;
		while (tmpPtr->rightChild != NULL)
			//
		{
			tmpF = tmpPtr;
			tmpPtr = tmpPtr->rightChild;
		}
		p->data = tmpPtr->data;
		//
		if (tmpF->rightChild == tmpPtr)     //
			delete_node(tmpF->rightChild);
		else
			delete_node(tmpF->leftChild);
	}
}

void BinSortTree::show_all_data(BinTreeNode* p)
{
	if (p != nullptr)
	{
		show_all_data(p->leftChild);
		cout << "图书号：" << p->data.book_id;
		cout << "  书名：" << p->data.book_name;
		cout << "  作者：" << p->data.author_name;
		cout << "  出版社：" << p->data.publisher_name;
		cout << "  出版日期：" << p->data.publish_date.year << "." << p->data.publish_date.month << "." << p->data.publish_date.day;
		cout << "  定价:" << p->data.price / 100 << "." << p->data.price % 100 << "元";
		cout << "  购买数量:" << p->data.purchase_amount;
		cout << "  加入购物车日期：" << p->data.add_to_cart_date.year << "."
			<< p->data.add_to_cart_date.month << "." << p->data.add_to_cart_date.day << endl;
		show_all_data(p->rightChild);
	}
}

BinTreeNode* BinSortTree::get_root()
{
	return root;
}
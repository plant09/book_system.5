#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "assistance.h"
#include "LinkList.h"

class hash_table
{
public:
	hash_table();
	~hash_table();

	bool insert(book_data &book);	//插入书籍
	bool insert_old_book(book_data &book);	//不建立索引结点
	bool delete_books_by_ID(const int ID, book_data &book);	//删除书籍
	int delete_books_by_date(date &date);
	bool get_books_by_ID(const int ID, book_data &book);	//获得书籍
	int get_books_by_date(date &d, book_data books[]);
	int get_books_by_author(char *author_name, book_data books[]);

	void traverse(void (*visit)(const book_data &)) const;
	void in_storage();
private:
	int hash_fun(date &d)	//哈希函数
	{
		return (d.month - 1) * 31 + d.day - 1;
	}
	int ID_fun(int ID)	//用于ID索引表
	{
		return ID % 10;
	}

	LinkList<int> ID_index_table[10];	//索引表
	LinkList<book_data>* date_hash_table[372]; 	//哈希表
};


#endif

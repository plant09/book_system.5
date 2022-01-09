#include "hash_table.h"
#include "LinkList.h"


hash_table::hash_table()
{
	for (int i = 0; i <= 371; i++)
	{
		date_hash_table[i] = NULL;
	}
}

hash_table::~hash_table()
{
	for (int i = 0; i <= 371; i++)
	{
		if (date_hash_table[i] != NULL)
			delete date_hash_table[i];
	}
}

bool hash_table::insert(book_data &book)
{
	const int id = book.book_id;	//防止相同ID重复添加
	if (get_books_by_ID(id, book))
		return false;

	int val = hash_fun(book.storage_date);
	if (date_hash_table[val] == NULL)	//无则加之
		date_hash_table[val] = new LinkList<book_data>(book);
	else
		date_hash_table[val]->InsertElem(book);
	ID_index_table[ID_fun(book.book_id)].InsertElem(val);	//建立该结点的索引表
	return true;
}

bool hash_table::insert_old_book(book_data &book)	//不建立索引结点
{
	const int id = book.book_id;	//防止相同ID重复添加
	if (get_books_by_ID(id, book))
		return false;

	int val = hash_fun(book.storage_date);
	if (date_hash_table[val] == NULL)	//无则加之
		date_hash_table[val] = new LinkList<book_data>(book);
	else
		date_hash_table[val]->InsertElem(book);
	return true;
}

bool hash_table::delete_books_by_ID(const int ID, book_data &book)
{
	int val = 0;

	Node<int> *p = ID_index_table[ID_fun(ID)].first->next;	//有头结点
	while (p != NULL)	
	{
		val = p->data;	//根据索引表值去找
		Node<book_data> *q = date_hash_table[val]->first;
		while (q->next != NULL)	//遍历该链表
		{
			if (q->next->data.book_id == ID)	//找到则删除
			{
				Node<book_data> *t = q->next;
				q->next = t->next;
				t->next = NULL;
				book = t->data;
				delete t;
				return true;
			}
			q = q->next;
		}
		p = p->next;
	}
	return false;
}

int hash_table::delete_books_by_date(date &date)
{
	int count = 0;
	int val = hash_fun(date);
	if (date_hash_table[val] == NULL)	//该日期没有任何书
		return 0;
	Node<book_data> *q = date_hash_table[val]->first;
	Node<book_data> *t;

	while (q->next != NULL)
	{
		if (q->next->data.storage_date.year == date.year)	//通过哈希分类后只有year可能不一样
		{
			count++;
			t = q->next;
			q->next = t->next;
			t->next = NULL;
			delete t;
		}
		else
			q = q->next;
	}
	return count;
}

bool hash_table::get_books_by_ID(const int ID, book_data &book)
{
	int val = 0;

	Node<int> *p = ID_index_table[ID_fun(ID)].first->next;	//有头结点
	while (p != NULL)	
	{
		val = p->data;	//根据索引表值去找
		Node<book_data> *q = date_hash_table[val]->first;
		while (q->next != NULL)	//找到具体链表后遍历观察有无ID相同的书
		{
			if (q->next->data.book_id == ID)
			{
				book = q->next->data;
				return true;
			}
			q = q->next;
		}
		p = p->next;
	}
	return false;
}

int hash_table::get_books_by_date(date &d, book_data books[])
{
	int val = hash_fun(d);
	int count = 0;
	if (date_hash_table[val] == NULL)	//该日期没有任何书
		return 0;
	Node<book_data> *q = date_hash_table[val]->first;
	Node<book_data> *t;

	while (q->next != NULL)
	{
		if (q->next->data.storage_date.year == d.year)
		{
			t = q->next;	//给到数组
			books[count] = t->data;
			count++;
		}
		q = q->next;
	}
	return count;
}

int hash_table::get_books_by_author(char *author_name, book_data books[])
{
	int count = 0;

	for (int i = 0; i <= 371; i++)
	{
		if (date_hash_table[i]!= NULL)
		{
			Node<book_data> *q = date_hash_table[i]->first->next;
			while (q != NULL)
			{
				char *ch = q->data.author_name;
				if (strcmp(ch, author_name) == 0)
				{
					books[count++] = q->data;
				}
			//	while (*ch == *author_name)
			//	{
			//		if (ch == '\0' && author_name == '\0')	//名字相同
			//		{
			//			books[count++] = q->data;
			//			break;
			//		}
			//		ch++;
			//		author_name++;
			//	}
				q = q->next;
			}
		}
	}
	return count;
}

void hash_table::traverse(void (*visit)(const book_data &)) const
{
	for (int i = 0; i <= 371; i++)
	{
		if (date_hash_table[i]!= NULL)
		{
			Node<book_data> *q = date_hash_table[i]->first->next;
			while (q != NULL)
			{
				(*visit)(q->data);
				q = q->next;
			}
		}
	}
}

void hash_table::in_storage()
{
	ofstream outf("library.dat", ios::out | ios::binary);
	for (int i = 0; i <= 371; i++)
	{
		if (date_hash_table[i]!= NULL)
		{
			Node<book_data> *q = date_hash_table[i]->first->next;
			while (q != NULL)
			{
				outf.write(reinterpret_cast<char*>(&q->data), sizeof(book_data));
				q = q->next;
			}
		}
	}
}

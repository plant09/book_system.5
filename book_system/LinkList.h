#ifndef LINKLIST_H
#define LINKLIST_H

#include <assert.h>
#include "Node.h"

template <class ElemType>
class LinkList
{
public:
	LinkList();
	LinkList(ElemType &data);
	~LinkList();
	void InsertElem(ElemType &data);
	void Clear();
	Node<ElemType> *LocateAddress(int data);
private:
	Node<ElemType> *first;

	friend class hash_table;
};

template <class ElemType>
LinkList<ElemType>::LinkList()
{
	first = new Node<ElemType>();
	assert(first);
	first->next = NULL;
}

template <class ElemType>
LinkList<ElemType>::LinkList(ElemType &data)
{
	first = new Node<ElemType>();
	assert(first);
	first->next = new Node<ElemType>(data);
}

template <class ElemType>
LinkList<ElemType>::~LinkList()
{
	Clear();
	delete first;
	first = NULL;
}

template <class ElemType>
void LinkList<ElemType>::InsertElem(ElemType &data)
{
	Node<ElemType> *p = first;
	Node<ElemType> *q = new Node<ElemType>();
	assert(q);

	q->data = data;

	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = q;
	return;
}

template <class ElemType>
void LinkList<ElemType>::Clear()
{
	Node<ElemType> *p = first->next, *temp;
	while (p != NULL)
	{
		temp = p->next;
		delete p;
		p = temp;
	}
	first->next = NULL;
	return;
}

template <class ElemType>
Node<ElemType> *LinkList<ElemType>::LocateAddress(int data)
{
	Node<ElemType> *p = first;
	for (int i = 1; i <= data && p != NULL; i++)
	{
		p = p->next;
	}
	return p;
}

template <class ElemType>
int Frequency(LinkList<ElemType> &list, ElemType data)
{
	Node<ElemType> *p = list.first;
	int count = 0;
	p = p->next;
	while (p != NULL)
	{
		if (p->data == data)
			count++;
		p = p->next;
	}
	return count;

}
#endif

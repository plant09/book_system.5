#ifndef NODE_H
#define NODE_H

#include <assert.h>

template <class ElemType>
class Node
{
public:
	Node();
	Node(ElemType &data);
	Node<ElemType> *next;
	ElemType data;
};

template <class ElemType>
Node<ElemType>::Node()
{
	next = NULL;
}

template <class ElemType>
Node<ElemType>::Node(ElemType &data)
{
	this->data = data;
	next = NULL;
}
#endif

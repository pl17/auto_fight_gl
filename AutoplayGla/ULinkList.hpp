#pragma once

#include "ULinkNode.hpp"

template <class T>
class  ULinkList
{
public:
	ULinkList();
	~ULinkList();

	enum INSERT_TYPE
	{
		INSERT_BEFORE,
		INSERT_AFTER,
	};

	void Append(T object);
	void Insert(ULinkNode<T> *src, ULinkNode<T> *des, INSERT_TYPE type);
	void Delete(T object);
	ULinkNode<T>* FindNode(T object);
	ULinkNode<T>* Last();
	ULinkNode<T>* First();
private:
	ULinkNode<T> m_first;
	ULinkNode<T> m_last;
};

template <class T>
ULinkNode<T>* ULinkList<T>::FindNode( T object )
{
	ULinkNode *now;

	now=this->m_first.Next();
	while (now)
	{
		if (object==now->GetData())
			return now;
		now=now->Next();
	}
	return NULL;
}

template <class T>
void ULinkList<T>::Delete( T object )
{
	ULinkNode<T> *node;

	node=this->FindNode(object);
	if (node)
		delete node;
}

template <class T>
void ULinkList<T>::Append( T object )
{
	ULinkNode<T> *node;

	node=new ULinkNode<T>(object);

	ULinkList::Insert(&this->m_last, node, INSERT_BEFORE);
}

template <class T>
ULinkList<T>::~ULinkList()
{
	ULinkNode<T> *next, *now;

	now=this->m_first.Next();
	while (now!=&this->m_last)
	{
		next=now->Next();
		delete now;
		now=next;
	}
}

template <class T>
ULinkList<T>::ULinkList()
{
	this->m_first.SetNext(&this->m_last);
	this->m_last.SetBack(&this->m_first);
}

template <class T>
ULinkNode<T>* ULinkList<T>::Last()
{
	return &this->m_last;
}

template <class T>
ULinkNode<T>* ULinkList<T>::First()
{
	return &this->m_first;
}

template <class T>
void ULinkList<T>::Insert( ULinkNode<T> *src, ULinkNode<T> *des, INSERT_TYPE type )
{
	ULinkNode<T> *t1, *t2;

	if (src && des)
	{
		t1=0;
		t2=0;

		if (type==INSERT_AFTER && src!=&this->m_last)
		{
			t1=src;
			t2=src->Next();
		}
		else if (type==INSERT_BEFORE && src!=&this->m_first)
		{
			t1=src->Back();
			t2=src;
		}

		if (t1 && t2)
		{
			t1->SetNext(des);
			t2->SetBack(des);
			des->SetNext(t2);
			des->SetBack(t1);
		}
	}
}

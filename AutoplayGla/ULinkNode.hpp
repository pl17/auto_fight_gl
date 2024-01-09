#pragma once

template <class T>
class ULinkNode
{
public:
	ULinkNode();
	ULinkNode(T data);
	~ULinkNode();

	void SetData(T data);
	T GetData();

	ULinkNode<T>* Next();
	ULinkNode<T>* Back();

	void SetNext(ULinkNode<T> *node);
	void SetBack(ULinkNode<T> *node);
private:
	ULinkNode<T> *m_next;
	ULinkNode<T> *m_back;
	T m_data;

	void _Init(T data);
};

template <class T>
ULinkNode<T>* ULinkNode<T>::Next()
{
	return this->m_next;
}

template <class T>
T ULinkNode<T>::GetData()
{
	return this->m_data;
}

template <class T>
void ULinkNode<T>::SetData( T data )
{
	this->m_data=data;
}

template <class T>
ULinkNode<T>::~ULinkNode()
{
	if (this->m_back)
	{
		this->m_back->m_next=this->m_next;
	}
	if (this->m_next)
	{
		this->m_next->m_back=this->m_back;
	}
}

template <class T>
ULinkNode<T>::ULinkNode()
{
	this->_Init(0);
}

template <class T>
ULinkNode<T>::ULinkNode(T data)
{
	this->_Init(data);
}

template <class T>
void ULinkNode<T>::SetBack( ULinkNode<T> *node )
{
	this->m_back=node;
}

template <class T>
void ULinkNode<T>::SetNext( ULinkNode<T> *node )
{
	this->m_next=node;
}

template <class T>
ULinkNode<T>* ULinkNode<T>::Back()
{
	return this->m_back;
}

template <class T>
void ULinkNode<T>::_Init(T data)
{
	this->m_back=0;
	this->m_next=0;
	this->m_data=data;
}

#pragma once

#include <Windows.h>

template <class T>
class UArrayList
{
public:
	UArrayList();
	~UArrayList();

	int GetSize();
	BOOL Add(T object);
	T Get(int index);
	BOOL Remove(int index);
	T& operator[](int nIndex);
protected:
	T* m_lpvValue;
	int m_nSize;
	int m_nMaxSize;
	HANDLE m_hMemory;

	BOOL _IncreaseBlockMemory(int nCount);
	BOOL _IncreaseBlockMemory();

	static const int _BUFFERSIZE=10;
};

template <class T>
UArrayList<T>::UArrayList()
{
	this->m_nSize=0;
	this->m_nMaxSize=UArrayList::_BUFFERSIZE;
	this->m_hMemory=LocalAlloc(LMEM_MOVEABLE, this->m_nMaxSize*sizeof(T));
	this->m_lpvValue=(T*)LocalLock(this->m_hMemory);
}

template <class T>
UArrayList<T>::~UArrayList()
{
	LocalUnlock(this->m_hMemory);
	LocalFree(this->m_hMemory);
}

template <class T>
int UArrayList<T>::GetSize()
{
	return this->m_nSize;
}

template <class T>
BOOL UArrayList<T>::Add( T object )
{
	BOOL brs;

	brs=TRUE;

	if (this->m_nSize>=this->m_nMaxSize)
		brs=this->_IncreaseBlockMemory();

	this->m_lpvValue[this->m_nSize]=object;
	this->m_nSize++;

	return brs;
}

template <class T>
T UArrayList<T>::Get( int index )
{
	if (index<0 || index>=this->m_nSize)
		return NULL;

	return this->m_lpvValue[index];
}

template <class T>
BOOL UArrayList<T>::Remove( int index )
{
	BOOL brs;
	if (index<0 || index>this->m_nSize)
	{
		brs=FALSE;
	}
	else
	{
		brs=TRUE;
		this->m_lpvValue[index]=this->m_lpvValue[this->m_nSize-1];
		this->m_nSize--;
	}

	return brs;
}

template <class T>
BOOL UArrayList<T>::_IncreaseBlockMemory( int nCount )
{
	BOOL brs;

	brs=LocalUnlock(this->m_hMemory);
	//err=GetLastError();
	//if (brs)
	{
		this->m_hMemory=LocalReAlloc(this->m_hMemory, sizeof(T)*(this->m_nMaxSize+nCount), LMEM_MOVEABLE);
		this->m_nMaxSize+=nCount;

		this->m_lpvValue=(T*)LocalLock(this->m_hMemory);
	}

	return brs;
}


template <class T>
BOOL UArrayList<T>::_IncreaseBlockMemory()
{
	return this->_IncreaseBlockMemory(UArrayList::_BUFFERSIZE);
}

template <class T>
T& UArrayList<T>::operator[]( int nIndex )
{
	//if (nIndex<0 || nIndex>=this->m_nSize)
	//return (void*&)(void*)NULL;
	return this->m_lpvValue[nIndex];
}

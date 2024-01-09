#pragma once

#include <Windows.h>

template <class T>
class ULinkList
{
public:
	ULinkList_Base(int nUnitSize);
	~ULinkList_Base();

	BOOL Add(T* object);
	BOOL Remove(T* object);
	BOOL IsExist(T* object);
private:
	T m_list;
};
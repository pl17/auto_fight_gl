#pragma once

#include "UArrayList.hpp"

class UHashTable
{
public:
	UHashTable();
	~UHashTable();

	typedef struct _UDICTIONARY
	{
		TCHAR *szKey;
		int nKey;
		TCHAR *szValue;
		int nValue;
	} UDICTIONARY;

	BOOL Append(TCHAR *szKey, TCHAR *szValue);
	int GetSize();
	TCHAR* GetValue(const TCHAR *szKey);
	BOOL IsExist(const TCHAR *szKey);
	BOOL IsEqual(const TCHAR *szKey, const TCHAR *szValue);
	int FindIndex(const TCHAR *szKey);
	void RemoveKey(const TCHAR *szKey);
	void RemoveKey(int index);
	BOOL EditKey(const TCHAR *szKey, TCHAR *szValue);
	BOOL EditKey(int index, TCHAR *szValue);
protected:
	UArrayList<UDICTIONARY*> m_hashtable;
};
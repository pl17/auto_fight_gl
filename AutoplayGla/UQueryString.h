#pragma once

#include "UHashTable.h"

class UQueryString :
	public UHashTable
{
public:
	UQueryString(const TCHAR* szUrl);
	~UQueryString();

	TCHAR* BuildQueryString();
	void Append(TCHAR *szKey, TCHAR *szValue);
	void RemoveKey(const TCHAR *szKey);

	static BOOL IsEqualQuery(UQueryString *src, UQueryString *des);
private:
	void _ParseQueryString(const TCHAR *szQueryString);
	void _ParseUrl(const TCHAR *szUrl);
	void _Free(int index);

	TCHAR *m_szHost;
	int m_nHost;
};
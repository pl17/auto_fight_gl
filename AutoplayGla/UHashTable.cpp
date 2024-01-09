#include "UHashTable.h"

UHashTable::UHashTable()
{

}

UHashTable::~UHashTable()
{
	int size;

	size=this->m_hashtable.GetSize();
	for (int i=0; i<size; i++)
	{
		LocalFree(this->m_hashtable.Get(i));
	}
}

BOOL UHashTable::Append( TCHAR *szKey, TCHAR *szValue )
{
	int index;
	UDICTIONARY* node;
	BOOL brs;

	index=this->FindIndex(szKey);

	if (index>=0)
	{
		brs=FALSE;
	}
	else
	{
		node=(UDICTIONARY*)LocalAlloc(LMEM_FIXED, sizeof(UDICTIONARY));
		node->szKey=szKey;
		node->szValue=szValue;
		node->nKey=wcslen(szKey);
		node->nValue=wcslen(szValue);

		this->m_hashtable.Add(node);
		brs=TRUE;
	}

	return brs;
}

TCHAR* UHashTable::GetValue( const TCHAR *szKey )
{
	int index;
	TCHAR *rs;
	
	index=this->FindIndex(szKey);
	rs=NULL;
	if (index>=0)
	{
		rs=this->m_hashtable.Get(index)->szValue;
	}
	return rs;
}

int UHashTable::GetSize()
{
	return this->m_hashtable.GetSize();
}

BOOL UHashTable::IsExist( const TCHAR *szKey )
{
	return this->FindIndex(szKey)>=0?TRUE:FALSE;
}

int UHashTable::FindIndex( const TCHAR *szKey )
{
	int size;
	int index;

	size=this->m_hashtable.GetSize();
	index=-1;
	for (int i=0; i<size; i++)
	{
		if (wcsicmp(szKey, this->m_hashtable.Get(i)->szKey)==0)
		{
			index=i;
			break;
		}
	}

	return index;
}

void UHashTable::RemoveKey( const TCHAR *szKey )
{
	this->RemoveKey(this->FindIndex(szKey));
}

void UHashTable::RemoveKey( int index )
{
	if (index>=0 && index<this->GetSize())
		this->m_hashtable.Remove(index);
}

BOOL UHashTable::EditKey( const TCHAR *szKey, TCHAR *szValue )
{
	int index;

	index=this->FindIndex(szKey);
	
	return this->EditKey(index, szValue);
}

BOOL UHashTable::EditKey( int index, TCHAR *szValue )
{
	BOOL brs;

	brs=FALSE;
	if (index>=0 && index<this->GetSize())
	{
		brs=TRUE;
		this->m_hashtable.Get(index)->szValue=szValue;
	}

	return brs;
}

BOOL UHashTable::IsEqual( const TCHAR *szKey, const TCHAR *szValue )
{
	int index;
	BOOL brs;

	index=this->FindIndex(szKey);
	brs=FALSE;
	if (index>=0)
	{
		if (wcsicmp(this->m_hashtable.Get(index)->szValue, szValue)==0)
			brs=TRUE;
	}

	return brs;
}

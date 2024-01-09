#include "UQueryString.h"


UQueryString::UQueryString( const TCHAR* szUrl )
:UHashTable()
{
	this->m_szHost=NULL;
	this->_ParseUrl(szUrl);
}

UQueryString::~UQueryString()
{
	int size, i;

	size=this->GetSize();
	for (i=0; i<size; i++)
	{
		LocalFree(this->m_hashtable.Get(i)->szKey);
		LocalFree(this->m_hashtable.Get(i)->szValue);
	}
	LocalFree(this->m_szHost);
}

TCHAR* UQueryString::BuildQueryString()
{
	int len, size, i;
	TCHAR *szQuery, *szTmp;

	size=this->m_hashtable.GetSize();
	len=this->m_nHost;
	for (i=0; i<size; i++)
	{
		len+=this->m_hashtable.Get(i)->nKey+this->m_hashtable.Get(i)->nValue;
	}
	//len+=size+size-1;
	if (size!=0) len+=2*size;
	
	szQuery=(TCHAR*)LocalAlloc(LMEM_FIXED, sizeof(TCHAR)*(len+1));
	//Build host
	CopyMemory(szQuery, this->m_szHost, this->m_nHost*sizeof(TCHAR));
	szQuery[this->m_nHost]=L'?';

	szTmp=szQuery+this->m_nHost+1;
	for (i=0; i<size; i++)
	{
		CopyMemory(szTmp, this->m_hashtable.Get(i)->szKey, this->m_hashtable.Get(i)->nKey*sizeof(TCHAR));
		szTmp+=this->m_hashtable.Get(i)->nKey;

		*szTmp=L'=';
		szTmp++;

		CopyMemory(szTmp, this->m_hashtable.Get(i)->szValue, this->m_hashtable.Get(i)->nValue*sizeof(TCHAR));
		szTmp+=this->m_hashtable.Get(i)->nValue;

		*szTmp=L'&';
		szTmp++;
	}
	szQuery[len]=NULL;

	return szQuery;
}

void UQueryString::_ParseQueryString( const TCHAR *szQueryString )
{
	const TCHAR *cStart, *cEnd;
	TCHAR *szKey, *szValue;
	const TCHAR *szTmp;
	int len;

	cStart=szQueryString;
	cEnd=cStart;
	do
	{
		szQueryString++;
		cEnd++;

		if (*szQueryString==L'=')
		{
			len=(int)(cEnd-cStart);
			szKey=(TCHAR*)LocalAlloc(LMEM_FIXED, (len+1)*sizeof(TCHAR));
			CopyMemory(szKey, cStart, len*sizeof(TCHAR));
			szKey[len]=NULL;
			cStart=cEnd+1;
		}
		else if (*szQueryString==L'&' || *szQueryString==NULL)
		{
			len=(int)(cEnd-cStart);
			szValue=(TCHAR*)LocalAlloc(LMEM_FIXED, (len+1)*sizeof(TCHAR));
			CopyMemory(szValue, cStart, len*sizeof(TCHAR));
			szValue[len]=NULL;
			cStart=cEnd+1;

			this->Append(szKey, szValue);
		}
	}
	while (*szQueryString);
}

void UQueryString::_ParseUrl( const TCHAR *szUrl )
{
	const TCHAR *szStartQuery;


	this->m_szHost=NULL;
	this->m_nHost=0;
	if (szUrl)
	{
		szStartQuery=wcschr(szUrl, L'?');
		if (szStartQuery)
		{
			this->m_nHost=(int)(szStartQuery-szUrl);

			this->_ParseQueryString(szStartQuery+1);
		}
		else
		{
			this->m_nHost=wcslen(szUrl);
		}

		this->m_szHost=(TCHAR*)LocalAlloc(LMEM_FIXED, (this->m_nHost+1)*sizeof(TCHAR));
		CopyMemory(this->m_szHost, szUrl, this->m_nHost*sizeof(TCHAR));
		this->m_szHost[this->m_nHost]=NULL;
	}
}

void UQueryString::Append( TCHAR *szKey, TCHAR *szValue )
{
	int index;

	index=this->FindIndex(szKey);
	if (index<0)
	{
		this->UHashTable::Append(szKey, szValue);
	}
	else
	{
		LocalFree(this->m_hashtable.Get(index)->szValue);
		this->EditKey(index, szValue);
	}
}

void UQueryString::RemoveKey( const TCHAR *szKey )
{
	int index;

	index=this->FindIndex(szKey);
	if (index>=0)
	{
		this->_Free(index);
		this->UHashTable::RemoveKey(index);
	}
}

BOOL UQueryString::IsEqualQuery( UQueryString *src, UQueryString *des )
{
	BOOL brs;
	

	brs=TRUE;
	if (src && des)
	{
		if (src->GetSize()!=des->GetSize())
		{
			brs=FALSE;
		}
		else
		{
			for (int i=0, size=src->GetSize(); i<size; i++)
			{
				if (!des->IsEqual(src->m_hashtable.Get(i)->szKey, src->m_hashtable.Get(i)->szValue))
				{
					brs=FALSE;
					break;
				}
			}
		}
	}

	return brs;
}

void UQueryString::_Free( int index )
{
	if (index>=0 && index<=this->GetSize())
	{
		LocalFree(this->m_hashtable.Get(index)->szKey);
		this->m_hashtable.Get(index)->szKey=NULL;

		LocalFree(this->m_hashtable.Get(index)->szValue);
		this->m_hashtable.Get(index)->szValue=NULL;
	}
}

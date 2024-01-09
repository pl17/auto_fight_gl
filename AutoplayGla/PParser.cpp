#include <Windows.h>
#include "PParser.h"

int ppIsEqualIgnoreCase(const TCHAR *src, const TCHAR *des, int nsize)
{
	if (src==NULL && des!=NULL) return 0;
	
	int lsrc;

	lsrc=wcslen(src);
	if (nsize==-1)
	{
		nsize=wcslen(des);
	}
	if (lsrc<nsize)
		return 0;

	for (int i=0; i<nsize; i++)
	{
		if ((src[i]|0x20) != (des[i]|0x20)) return 0;
	}

	return 1;
}

int ppIsBoundary(TCHAR c, const TCHAR *lpszListBoundary)
{
	if (lpszListBoundary==NULL)
		return 0;

	while (*lpszListBoundary!=NULL)
	{
		if (*lpszListBoundary==c) return 1;
		lpszListBoundary++;
	}

	return 0;
}

const TCHAR* ppGetNextBoundary(const TCHAR *pszStart, const TCHAR *szListBoundary)
{
	if (pszStart)
	{
		while (*pszStart!=NULL)
		{
			if (ppIsBoundary(*pszStart, szListBoundary))
				break;
			pszStart++;
		}
	}

	return pszStart;
}

int ppIsInIgnoreCharList(const TCHAR c, const TCHAR *pszIgnoreList)
{
	if (pszIgnoreList)
	{
		while (*pszIgnoreList!=NULL)
		{
			if (c==*pszIgnoreList) return 1;
			pszIgnoreList++;
		}
	}

	return 0;
}

int ppParseToNumber(TCHAR *str, const TCHAR *szListBoundary, const TCHAR *szListIgnore, int nListValue, int *pListValue, ...)
{
	return ppvParseToNumber(str, szListBoundary, szListIgnore, nListValue, &pListValue);
}

int ppParseToNumber( const TCHAR *str, int base, int *output )
{
	const TCHAR *last;
	int len;
	int c;
	char *pout;

	*output=0;
	if (str)
	{
		len=wcslen(str);
		for (int i=0; i<len; i++)
		{
			if (str[i]>='a' && str[i]<='f')
				c=str[i]-'a'+10;
			else if (str[i]>='A' && str[i]<='F')
				c=str[i]-'A'+10;
			else if (str[i]>='0' && str[i]<='9')
				c=str[i]-'0';
			else return 0;

			*output=(*output<<4)|c;
		}
	}

	return 1;
}

int ppvParseToNumber(TCHAR *str, const TCHAR *szListBoundary, const TCHAR *szListIgnore, int nListValue, int **pList)
{
	int n, i, sign;
	const TCHAR *pszStart, *pszEnd;

	pszStart=str;
	pszEnd=pszStart;
	i=0;

	do 
	{
		pszEnd=ppGetNextBoundary(pszStart, szListBoundary);
		n=0;
		sign=1;
		while (pszStart!=pszEnd)
		{
			if (*pszStart>='0' && *pszStart<='9')
			{
				n=n*10+(*pszStart-'0');
			}
			else if (n==0 && *pszStart=='-')
			{
				sign*=-1;
			}
			else if (*pszStart==' ' || ppIsInIgnoreCharList(*pszStart, szListIgnore))
			{
				pszStart++;
				continue;
			}
			else
			{
				n=0;
				pszStart=pszEnd;
				break;
			}
			pszStart++;
		}
		pszStart=pszEnd+1;
		if (i<nListValue)
		{
			*(pList[i])=sign*n;
			i++;
		}
	} while (*pszEnd!=NULL);

	return i;
}

int ppParseToNumberIgnoreText(TCHAR *str, const TCHAR *szListBoundary, TCHAR *szListIgnore,int nListValue, int *pListValue, ...)
{
	return ppvParseToNumberIgnoreText(str, szListBoundary, szListIgnore, nListValue, &pListValue);
}

int ppvParseToNumberIgnoreText(TCHAR *str, const TCHAR *szListBoundary, TCHAR *szListIgnore, int nListValue, int **pList)
{
	int n, i, sign;
	const TCHAR *pszStart, *pszEnd;

	if (str==NULL)
		return 0;

	pszStart=str;
	pszEnd=pszStart;
	i=0;

	do 
	{
		pszEnd=ppGetNextBoundary(pszStart, szListBoundary);
		n=0;
		sign=1;
		while (pszStart!=pszEnd)
		{
			if (*pszStart>='0' && *pszStart<='9')
			{
				n=n*10+(*pszStart-'0');
			}
			else if (n==0 && *pszStart=='-')
			{
				sign*=-1;
			}
			else //if (*pszStart<'0' || *pszStart>'9')
			{
				if (n!=0 && !ppIsInIgnoreCharList(*pszStart, szListIgnore))
				{
					break;
				}
			}
// 			else
// 			{
// 				n=0;
// 				pszStart=pszEnd;
// 				break;
// 			}
			pszStart++;
		}
		pszStart=pszEnd+1;
		if (i<nListValue)
		{
			*(pList[i])=sign*n;
			i++;
		}
	} while (*pszEnd!=NULL);

	return i;
}

int ppIsContainIgnoreCase( const TCHAR *src, const TCHAR *des, int nsize )
{
	int len;

	if (src==NULL && des!=NULL) return 0;
	if (src==NULL && des==NULL) return 1;

	len=wcslen(src);
	if (nsize==-1) nsize=wcslen(des);

	for (int i=0; i<=len-nsize; i++)
	{
		if (ppIsEqualIgnoreCase(src+i, des, nsize))
			return 1;
	}

	return 0;
}

void ppParseFunctionArg( TCHAR *lpszScriptFunction, int nIndex, TCHAR **lpszOutput )
{
	TCHAR *cStart, *cEnd;

	*lpszOutput=NULL;

	if (lpszScriptFunction)
	{
		cStart=wcschr(lpszScriptFunction, '{');
		if (cStart) cStart=wcschr(cStart, '(');

		while (nIndex>0 && cStart)
		{
			nIndex--;
			cStart++;
			cStart=wcschr(cStart, ',');
		}

		if (cStart)
		{
			cStart++;
			cEnd=wcschr(cStart, ',');
			if (cEnd==NULL) cEnd=wcschr(cStart, ')');
			if (cEnd)
			{
				*lpszOutput=(TCHAR*)LocalAlloc(LMEM_FIXED, (cEnd-cStart+1)*sizeof(TCHAR));
				CopyMemory(*lpszOutput, cStart, (cEnd-cStart)*sizeof(TCHAR));
				(*lpszOutput)[cEnd-cStart]=NULL;
			}
		}
	}
}

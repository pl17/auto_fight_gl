#ifndef _PARSE_H
#define _PARSE_H
#include <tchar.h>

int ppIsEqualIgnoreCase(const TCHAR *src, const TCHAR *des, int nsize);
int ppIsContainIgnoreCase(const TCHAR *src, const TCHAR *des, int nsize);
int ppIsBoundary(TCHAR c, TCHAR *lpszListBoundary);
TCHAR* ppGetNextBoundary(TCHAR *pszStart, TCHAR *szListBoundary);
int ppvParseToNumber(TCHAR *str, const TCHAR *szListBoundary, const TCHAR *szListIgnore, int nListValue, int **pList);
int ppParseToNumber(TCHAR *str, const TCHAR *szListBoundary, const TCHAR *szListIgnore, int nListValue, int *pListValue, ...);
int ppParseToNumber(const TCHAR *str, int base, int *output);

int ppParseToNumberIgnoreText(TCHAR *str, const TCHAR *szListBoundary, TCHAR *szListIgnore, int nListValue, int *pListValue, ...);
int ppvParseToNumberIgnoreText(TCHAR *str, const TCHAR *szListBoundary, TCHAR *szListIgnore, int nListValue, int **pList);

void ppParseFunctionArg(TCHAR *lpszScriptFunction, int nIndex, TCHAR **lpszOutput);
#endif
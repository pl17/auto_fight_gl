#ifdef _PDBG

#include <stdio.h>
#include "MOutputDebug_View.h"

MOutputDebug_View::MOutputDebug_View()
{
	this->Init();
}

MOutputDebug_View::~MOutputDebug_View()
{
	this->Clear();
}

BOOL MOutputDebug_View::Init()
{
	return TRUE;
}

void MOutputDebug_View::Clear()
{
}

BOOL MOutputDebug_View::Reset()
{
	return TRUE;
}

BOOL MOutputDebug_View::WriteStreamA( char *szMsg, DWORD dwSize, DWORD* lpdwWritten )
{
	OutputDebugStringA(szMsg);
	return TRUE;
}

BOOL MOutputDebug_View::WriteStreamW( WCHAR *szMsg, DWORD dwSize, DWORD* lpdwWritten )
{
	OutputDebugStringW(szMsg);
	return TRUE;
}

#endif
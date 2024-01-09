#ifdef _PDBG

#include <stdio.h>
#include "MOutputDebug_Base.h"

#pragma warning(disable: 4267)


MOutputDebug_Base::MOutputDebug_Base()
{
	this->m_bShowTime=TRUE;
}

MOutputDebug_Base::~MOutputDebug_Base()
{
}

BOOL MOutputDebug_Base::vWriteA( char *szFormatMsg, void* ArgList,  BOOL bNewLine )
{
	char *szMsgA;
	DWORD dwWritten;
	int len;
	BOOL rs;

	rs=FALSE;
	if (this->m_hStream!=NULL && this->m_hStream!=INVALID_HANDLE_VALUE)
	{
		szMsgA=(char*)LocalAlloc(LMEM_FIXED, 1024*sizeof(char));
		if (szMsgA!=NULL)
		{
			len=0;
			if (this->m_bShowTime)
			{
				SYSTEMTIME st;
				GetLocalTime(&st);
				len=wsprintfA(szMsgA, "[%04d-%02d-%02d %02d:%02d:%02d]\t"
					, st.wYear
					, st.wMonth
					, st.wDay
					, st.wHour
					, st.wMinute
					, st.wSecond);
			}
			len+=vsprintf_s(szMsgA+len, 1024-len, szFormatMsg, (va_list)ArgList);
			if (bNewLine)
				len+=wsprintfA(szMsgA+len, "\r\n");
			rs=this->WriteStreamA(szMsgA, len, &dwWritten);
			LocalFree(szMsgA);
		}
		else
		{
			//Error cannot alloc szMsgW
		}
	}
	else
	{
		//Error invalid handle
	}

	return rs;
}

BOOL MOutputDebug_Base::WriteA( char *szFormatMsg, ... )
{
	return this->vWriteA(szFormatMsg, (va_list)_ADDRESSOF(szFormatMsg) + _INTSIZEOF(szFormatMsg));
}

BOOL MOutputDebug_Base::vWriteLineA( char *szFormatMsg, void* ArgList )
{
	BOOL rs;

	rs=this->vWriteA(szFormatMsg, ArgList, TRUE);

	return rs;
}

BOOL MOutputDebug_Base::WriteLineA( char *szFormatMsg, ... )
{
	return this->vWriteLineA(szFormatMsg, (va_list)_ADDRESSOF(szFormatMsg) + _INTSIZEOF(szFormatMsg));
}

void MOutputDebug_Base::SetStream( HANDLE hStream )
{
	this->m_hStream=hStream;
}

HANDLE MOutputDebug_Base::GetStream()
{
	return this->m_hStream;
}

BOOL MOutputDebug_Base::vWriteW( WCHAR *szFormatMsg, void* ArgList,  BOOL bNewLine )
{
	WCHAR *szMsgW;
	DWORD dwWritten;
	int len;
	BOOL rs;

	rs=FALSE;
	if (this->m_hStream!=NULL && this->m_hStream!=INVALID_HANDLE_VALUE)
	{
		szMsgW=(WCHAR*)LocalAlloc(LMEM_FIXED, 1024*sizeof(WCHAR));
		if (szMsgW!=NULL)
		{
			len=0;
			if (this->m_bShowTime)
			{
				SYSTEMTIME st;
				GetLocalTime(&st);
				len=wsprintfW(szMsgW, L"[%04d-%02d-%02d %02d:%02d:%02d]\t"
					, st.wYear
					, st.wMonth
					, st.wDay
					, st.wHour
					, st.wMinute
					, st.wSecond);
			}

			len+=wvsprintfW(szMsgW+len, szFormatMsg, (va_list)ArgList);
			if (bNewLine)
				len+=wsprintfW(szMsgW+len, L"\r\n");
			rs=this->WriteStreamW(szMsgW, len, &dwWritten);
			LocalFree(szMsgW);
		}
		else
		{
			//Error cannot alloc szMsgW
		}
	}
	else
	{
		//Error invalid handle
	}

	return rs;
}

BOOL MOutputDebug_Base::WriteW( WCHAR *szFormatMsg, ... )
{
	return this->vWriteW(szFormatMsg, (va_list)_ADDRESSOF(szFormatMsg) + _INTSIZEOF(szFormatMsg));
}

BOOL MOutputDebug_Base::vWriteLineW( WCHAR *szFormagMsg, void* ArgList )
{
	BOOL rs;

	rs=this->vWriteW(szFormagMsg, ArgList, TRUE);

	return rs;
}

BOOL MOutputDebug_Base::WriteLineW( WCHAR *szFormatMsg, ... )
{
	return this->vWriteLineW(szFormatMsg, (va_list)_ADDRESSOF(szFormatMsg) + _INTSIZEOF(szFormatMsg));
}

BOOL MOutputDebug_Base::WriteStreamA(char *szMsg, DWORD dwSize, DWORD* lpdwWritten)
{
	WaitForSingleObject(this->m_hStream, INFINITE);
	return WriteFile(this->m_hStream, szMsg, dwSize, lpdwWritten, NULL);
}

BOOL MOutputDebug_Base::WriteStreamW(WCHAR *szMsg, DWORD dwSize, DWORD* lpdwWritten)
{
	BOOL rs;
	WaitForSingleObject(this->m_hStream, INFINITE);
	rs=WriteFile(this->m_hStream, szMsg, dwSize*sizeof(WCHAR), lpdwWritten, NULL);
	if (lpdwWritten)
		*lpdwWritten/=sizeof(WCHAR);

	return rs;
}

void MOutputDebug_Base::ShowTime( BOOL bVisible )
{
	this->m_bShowTime=bVisible;
}

#endif

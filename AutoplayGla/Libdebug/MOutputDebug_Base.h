#ifndef _MOUTPUTBASE_H
#define _MOUTPUTBASE_H

#ifdef _PDBG

#include "IOutputDebug.h"

class MOutputDebug_Base: public IOutputDebug
{
public:
	MOutputDebug_Base();
	virtual ~MOutputDebug_Base();

	BOOL vWriteA( char *szFormatMsg, void* ArgList,  BOOL bNewLine=FALSE );
	BOOL vWriteW( WCHAR *szFormatMsg, void* ArgList,  BOOL bNewLine=FALSE );

	BOOL WriteA( char *szFormatMsg, ... );
	BOOL WriteW( WCHAR *szFormatMsg, ... );

	BOOL vWriteLineA( char *szFormagMsg, void* ArgList );
	BOOL vWriteLineW( WCHAR *szFormagMsg, void* ArgList );

	BOOL WriteLineA( char *szFormagMsg, ... );
	BOOL WriteLineW( WCHAR *szFormagMsg, ... );

	void ShowTime(BOOL bVisible);

protected:
	void SetStream(HANDLE hStream);
	HANDLE GetStream();

	virtual BOOL WriteStreamA(char *szMsg, DWORD dwSize, DWORD* lpdwWritten);
	virtual BOOL WriteStreamW(WCHAR *szMsg, DWORD dwSize, DWORD* lpdwWritten);

private:
	HANDLE m_hStream;
	BOOL m_bShowTime;
};

#endif//End PDBG
#endif//End file
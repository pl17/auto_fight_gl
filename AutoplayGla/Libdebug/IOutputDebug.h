#ifndef _IOUTPUTDEBUG_H
#define _IOUTPUTDEBUG_H

#ifdef _PDBG

#include <Windows.h>

class IOutputDebug
{
public:
	virtual ~IOutputDebug();


	virtual BOOL vWriteA(char *szFormatMsg, void* ArgList, BOOL bNewLine=FALSE)=0;
	virtual BOOL vWriteW(WCHAR *szFormatMsg, void* ArgList,  BOOL bNewLine=FALSE)=0;

	virtual BOOL WriteA(char *szFormatMsg, ...)=0;
	virtual BOOL WriteW(WCHAR *szFormatMsg, ...)=0;

	virtual BOOL vWriteLineA(char *szFormatMsg, void* ArgList)=0;
	virtual BOOL vWriteLineW(WCHAR *szFormatMsg, void* ArgList)=0;

	virtual BOOL WriteLineA(char *szFormatMsg, ...)=0;
	virtual BOOL WriteLineW(WCHAR *szFormatMsg, ...)=0;

	//
	virtual BOOL Reset()=0;
	virtual void ShowTime(BOOL bVisible)=0;

protected:
  	virtual BOOL Init()=0;
  	virtual void Clear()=0;

};

#endif//End PDBG
#endif//End file
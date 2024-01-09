#ifndef _LOGS_H_
#define _LOGS_H_

#ifdef _PDBG//Use debug

#include "IOutputDebug.h"
#include "MOutputDebug_Base.h"
#include "MOutputDebug_File.h"
#include "MOutputDebug_Console.h"
#include "MOutputDebug_View.h"

//Define function
#define LogClose(pIDebug)	(delete pIDebug)

#define LogCreateFile(pIDebug, filename)	(pIDebug= new MOutputDebug_File(filename))
#define LogCreateConsole(pIDebug)	(pIDebug=new MOutputDebug_Console())
#define LogCreateView(pIDebug)	(pIDebug=new MOutputDebug_View())

#define LogWriteLineW(pIDebug, szFormatText, ...) (pIDebug->WriteLineW(szFormatText, __VA_ARGS__ ))
#define LogWriteLineA(pIDebug, szFormatText, ...) (pIDebug->WriteLineA(szFormatText, __VA_ARGS__ ))
#define LogWriteW(pIDebug, szFormatText, ...) (pIDebug->WriteW(szFormatText, __VA_ARGS__ ))
#define LogWriteA(pIDebug, szFormatText, ...) (pIDebug->WriteA(szFormatText, __VA_ARGS__ ))
#define LogReset(pIDebug) (pIDebug->Reset())
#define LogShowTime(pIDebug, bVisible)	(pIDebug->ShowTime(bVisible))

//process unicode/ascii
#ifdef UNICODE
#define LogWriteLine	LogWriteLineW
#define LogWrite		LogWriteW
#else
#define LogWriteLine	LogWriteLineA
#define LogWrite		LogWriteA
#endif

#else//Not use debug

#define LogClose(pIDebug)

#define LogCreateFile(pIDebug, filename)
#define LogCreateConsole(pIDebug)
#define LogCreateView(pIDebug)

#define IOutputDebug void
#define MOutputDebug_Base void
#define MOutputDebug_Console void
#define MOutputDebug_File void
#define MOutputDebug_View void

#define LogWriteLineW(pIDebug, szFormatText, ...)
#define LogWriteLineA(pIDebug, szFormatText, ...)
#define LogWriteW(pIDebug, szFormatText, ...)
#define LogWriteA(pIDebug, szFormatText, ...)

#define LogWriteLine
#define LogWrite

#define LogReset(pIDebug)
#define LogShowTime(pIDebug, bVisible)
#endif

#endif
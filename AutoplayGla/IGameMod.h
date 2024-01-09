#pragma once

#include <ExDisp.h>

class IGameMod
{
public:
	virtual BOOL Go(IWebBrowser2 *wb2)=0;
	virtual void SetMod(const TCHAR* szQueryString)=0;
	virtual BOOL IsTruth(IWebBrowser2 *wb2)=0;
};
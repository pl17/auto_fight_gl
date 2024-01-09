#pragma once

#include <ExDisp.h>

class IGameReport
{
public:
	virtual void OnReport(IWebBrowser2 *wb2);
};
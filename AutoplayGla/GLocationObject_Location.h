#pragma  once

#include "GLocationObject_Base.h"
#include <MsHTML.h>

class GLocationObject_Location :
	public GLocationObject_Base
{
public:
	GLocationObject_Location();
	BOOL AttackMonster(IWebBrowser2 *wb2, int nIndex);
	BSTR GetMonsterName(IHTMLDocument3 *doc3, int nIndex);

private:

};
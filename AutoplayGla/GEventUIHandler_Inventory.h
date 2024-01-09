#pragma once

#include <MsHTML.h>
#include <ExDisp.h>
#include "GEventUIHandler_Base.h"

class GEventUIHandler_Inventory :
	public GEventUIHandler_Base
{
public:
	GEventUIHandler_Inventory();
	void Synchronized( IWebBrowser2 *wb2 );

private:
	IHTMLDOMNode* _GetRootMenu(IHTMLDocument3 *doc3);
	BOOL _CheckMenuTag(IHTMLDOMNode *node);
	BSTR _GetHref(IHTMLDOMNode *node);
	void _SynchronizedInvId(IWebBrowser2 *wb2);

	int m_nLastInvId;
};

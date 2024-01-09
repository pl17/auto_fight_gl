#pragma once

#include <ExDisp.h>
#include "IGameObject.h"
#include "UHashTable.h"

class GExpeditionObject_Info
{
public:
	GExpeditionObject_Info();
	void Synchronized(IWebBrowser2 *wb2);
private:
	UHashTable m_htInfo;
	BOOL m_bValid;

	void _ParseInfo(IWebBrowser2 *wb2);
	BOOL _IsExpeditionInfo(struct IHTMLDOMNode *node);
};
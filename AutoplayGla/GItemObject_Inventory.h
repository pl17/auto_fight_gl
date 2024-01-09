#pragma once

#include "ItemInvObject.h"
#include <ExDisp.h>

#define INV_WIDTH		8
#define INV_HEIGHT		4

class GItemObject_Inventory
{
public:
	GItemObject_Inventory();
	void Synchronized(IWebBrowser2 *wb2);

	IHTMLDOMNode* GetSlotNode(IWebBrowser2 *wb2, int nRow, int nColumn);
	IHTMLDOMNode* GetSlotItem(IWebBrowser2 *wb2, int nRow, int nColumn);
	BOOL IsExistItemDirect(IWebBrowser2 *wb2, int nRow, int nColumn);
	BOOL IsValid();
//private:
	ItemInvObject m_items[INV_HEIGHT][INV_WIDTH];

private:
	BOOL m_bIsValid;
};
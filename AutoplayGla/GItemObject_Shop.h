#pragma once

#include "ItemInvObject.h"
#include <ExDisp.h>
#include <Windows.h>

#define SHOP_WIDTH	6
#define SHOP_HEIGHT	8

class GItemObject_Shop
{
public:
	GItemObject_Shop();
	
	void Synchronized(IWebBrowser2 *wb2);
	IHTMLDOMNode* GetSlotNode(IWebBrowser2 *wb2, int nRow, int nColumn);
	BOOL IsExistItemDirect(IWebBrowser2 *wb2, int nRow, int nColumn);
private:
	ItemInvObject m_items[SHOP_HEIGHT][SHOP_WIDTH];
};
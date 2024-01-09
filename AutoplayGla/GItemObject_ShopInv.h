#pragma once

#include "GItemObject_Inventory.h"
#include "GItemObject_Shop.h"
#include "GPlayerObject_Player.h"
#include <ExDisp.h>

class GItemObject_ShopInv
{
public:
	GItemObject_ShopInv(GItemObject_Shop *itemShop, GItemObject_Inventory *itemInv, GPlayerObject_Player *player);

	BOOL CanAction();
	BOOL TryAction();
	BOOL SellItem(IWebBrowser2 *wb2, int nInvRow, int nInvColumn, int nShopRow, int nShopColumn);
	BOOL BuyItem(IWebBrowser2 *wb2, int nInvRow, int nInvColumn, int nShopRow, int nShopColumn);

	void Synchronized(IWebBrowser2 *wb2);
private:
	GItemObject_Shop *m_itemShop;
	GItemObject_Inventory *m_itemInv;
	GPlayerObject_Player *m_player;
};
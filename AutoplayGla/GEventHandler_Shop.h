#pragma once

#include "GEventHandler_Base.h"
#include "GItemObject_Inventory.h"
#include "GItemObject_Shop.h"
#include "GPlayerObject_Player.h"


class GEventHandler_Shop :
	public GEventHandler_Base
{
public:
	GEventHandler_Shop(GItemObject_Shop *itemShop, GItemObject_Inventory *itemInv, GPlayerObject_Player *player);

	void Synchronized( IWebBrowser2 *wb2 );
private:
	//void AfterSynchronized( IWebBrowser2 *wb2 );
	BOOL _CanHandler();
	BOOL _OnHandler();
	BOOL _OnProcessingHandler();
	BOOL _OnFinishedHandler();

	GItemObject_Shop *m_itemShop;
	GItemObject_Inventory *m_itemInv;
	GPlayerObject_Player *m_player;
};
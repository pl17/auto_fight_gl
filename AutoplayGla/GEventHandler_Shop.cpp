#include "GEventHandler_Shop.h"
#include "ActionSimulator.h"


GEventHandler_Shop::GEventHandler_Shop( GItemObject_Shop *itemShop, GItemObject_Inventory *itemInv, GPlayerObject_Player *player )
:GEventHandler_Base(NULL, NULL, NULL)
{
	this->m_player=player;
	this->m_itemInv=itemInv;
	this->m_itemShop=itemShop;
}

void GEventHandler_Shop::Synchronized( IWebBrowser2 *wb2 )
{
}

BOOL GEventHandler_Shop::_CanHandler()
{
	BOOL brs;

	brs=FALSE;

	if (this->m_player && this->m_player->GetGold()>10)
		brs=TRUE;

	return brs;
}

BOOL GEventHandler_Shop::_OnHandler()
{
	BOOL brs;

	return brs;
}

BOOL GEventHandler_Shop::_OnProcessingHandler()
{
	return TRUE;
}

BOOL GEventHandler_Shop::_OnFinishedHandler()
{
	return TRUE;
}


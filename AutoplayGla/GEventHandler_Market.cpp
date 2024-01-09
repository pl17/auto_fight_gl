#include "GEventHandler_Market.h"

GEventHandler_Market::GEventHandler_Market( IWebBrowser2 *wb2, IGameMod *gmod, GItemObject_Market *market, GPlayerObject_Player *player )
:GEventHandler_Base(wb2, gmod, market)
{
	this->m_market=market;
	this->m_player=player;
}

BOOL GEventHandler_Market::_CanHandler()
{
	BOOL brs;

	brs=FALSE;

	if (this->GetAutoHandler())
	{
		if (this->m_player)
		{
			if ((this->m_player->GetGold()>=this->m_market->GetMaxGold() && this->m_market->GetMaxGold()>0)
				|| this->m_player->GetGold()>=30000)
				brs=TRUE;
		}
	}

	return brs;
}

BOOL GEventHandler_Market::_OnHandler()
{
	this->m_market->BidItem(this->m_wb2);

	return TRUE;
}

BOOL GEventHandler_Market::_OnProcessingHandler()
{
	return TRUE;
}

BOOL GEventHandler_Market::_OnFinishedHandler()
{
	return FALSE;
}

void GEventHandler_Market::AfterSynchronized( IWebBrowser2 *wb2 )
{
	if (this->m_player)
	{
		this->m_player->Synchronized(wb2);
	}
}

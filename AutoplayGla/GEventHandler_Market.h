#pragma once

#include "GEventHandler_Base.h"
#include "GItemObject_Market.h"
#include "GPlayerObject_Player.h"

class GEventHandler_Market :
	public GEventHandler_Base
{
public:
	GEventHandler_Market(IWebBrowser2 *wb2, IGameMod *gmod, GItemObject_Market *market, GPlayerObject_Player *player);

	BOOL _CanHandler();
	BOOL _OnHandler();
	BOOL _OnProcessingHandler();
	BOOL _OnFinishedHandler();

	void AfterSynchronized( IWebBrowser2 *wb2 );

private:
	GItemObject_Market *m_market;
	GPlayerObject_Player *m_player;
};
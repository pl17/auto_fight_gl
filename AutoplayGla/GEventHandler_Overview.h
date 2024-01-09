#pragma once

#include "GItemObject_Inventory.h"
#include "GPlayerObject_Player.h"
#include "GEventHandler_Base.h"
#include "GameManager.h"

class GEventHandler_Overview :
	public GEventHandler_Base
{
public:
	GEventHandler_Overview(IWebBrowser2 *wb2, IGameMod *gmod, GPlayerObject_Player *player, GItemObject_Inventory *inventory);

private:
	BOOL _CanHandler();
	BOOL _OnHandler();
	BOOL _OnProcessingHandler();
	BOOL _OnFinishedHandler();
	void _OnSynchronized( IWebBrowser2 *wb2 );

	BOOL _FindFood(int *nRow, int *nColumn);

	GItemObject_Inventory *m_inventory;
	GPlayerObject_Player *m_player;
};
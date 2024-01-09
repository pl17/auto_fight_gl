#pragma once

#include <ExDisp.h>
#include "GEventHandler_Base.h"
#include "IGameObject.h"
#include "GLocationObject_Dungeon.h"
#include "GPlayerObject_Player.h"

class GEventHandler_Dungeon :
	public GEventHandler_Base
{
public:
	GEventHandler_Dungeon(IWebBrowser2 *wb2, IGameMod *gmod, GLocationObject_Dungeon *dungeonobj, GPlayerObject_Player *playerobj);

private:
	BOOL _CanHandler();

	BOOL _OnHandler();
	BOOL _OnProcessingHandler();
	BOOL _OnFinishedHandler();

private:
	GPlayerObject_Player *m_playerobj;
	GLocationObject_Dungeon *m_dungeonobj;
};
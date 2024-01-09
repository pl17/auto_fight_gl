#pragma once

#include <ExDisp.h>
#include "GEventHandler_Base.h"
#include "GLocationObject_Location.h"
#include "GPlayerObject_Player.h"

class GEventHandler_Location : 
	public GEventHandler_Base
{
public:
	GEventHandler_Location(IWebBrowser2 *wb2, IGameMod *gmod, GLocationObject_Location *objLoc, GPlayerObject_Player *objPlayer);

private:
	BOOL _CanHandler();

	BOOL _OnHandler();
	BOOL _OnProcessingHandler();
	BOOL _OnFinishedHandler();

private:
	GPlayerObject_Player *m_objPlayer;
	GLocationObject_Location *m_objLoc;
};
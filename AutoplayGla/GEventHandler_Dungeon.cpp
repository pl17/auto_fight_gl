#include "GEventHandler_Dungeon.h"
#include "GameLink.h"

GEventHandler_Dungeon::GEventHandler_Dungeon( IWebBrowser2 *wb2, IGameMod *gmod, GLocationObject_Dungeon *dungeonobj, GPlayerObject_Player *playerobj )
:GEventHandler_Base(wb2, gmod, dungeonobj)
{
	this->m_dungeonobj=dungeonobj;
	this->m_playerobj=playerobj;
}

BOOL GEventHandler_Dungeon::_CanHandler()
{
	BOOL brs;

	brs=FALSE;

	if (this->m_playerobj)
	{
		if (this->m_playerobj->GetLevel()>=10)
			brs=TRUE;
	}

	return brs;
}

BOOL GEventHandler_Dungeon::_OnHandler()
{
	return TRUE;
}

BOOL GEventHandler_Dungeon::_OnProcessingHandler()
{
	return TRUE;
}

BOOL GEventHandler_Dungeon::_OnFinishedHandler()
{
	return TRUE;
}

#include "GEventHandler_Location.h"
#include "GameLink.h"
#include "IGameObject.h"

GEventHandler_Location::GEventHandler_Location( IWebBrowser2 *wb2, IGameMod *gmod,  GLocationObject_Location *objLoc, GPlayerObject_Player *objPlayer)
:GEventHandler_Base(wb2, gmod, objLoc)
{
	this->m_objPlayer=objPlayer;
	this->m_objLoc=objLoc;
}

BOOL GEventHandler_Location::_CanHandler()
{
	BOOL brs;

	brs=FALSE;

	if (this->GetAutoHandler())
	{
		if (this->m_objPlayer && this->m_objLoc)
		{
			if (this->m_objLoc->GetCooldown()<=0 
				&& this->m_objLoc->GetCurrentPoint()>0
				&& this->m_objPlayer->GetHpCurrent()>50)
			{
				brs=TRUE;
			}
		}
	}


	return brs;
}

BOOL GEventHandler_Location::_OnHandler()
{
	BOOL brs;

	brs=this->m_objLoc->AttackMonster(this->m_wb2, 2);

	return brs;
}

BOOL GEventHandler_Location::_OnProcessingHandler()
{
	return TRUE;
}

BOOL GEventHandler_Location::_OnFinishedHandler()
{
	return TRUE;
}

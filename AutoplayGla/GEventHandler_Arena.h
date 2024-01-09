#pragma once
#include <ExDisp.h>
#include "GEventHandler_Base.h"
#include "GEventHandler_Quest.h"
#include "IGameObject.h"
#include "GPlayerObject_Player.h"

class GEventHandler_Arena : 
	public GEventHandler_Base
{
public:
	GEventHandler_Arena(IWebBrowser2 *wb2, IGameMod *gmod, IGameObject *objArena, GEventHandler_Quest *evQuest, GPlayerObject_Player *objPlayer);

	void SetHpLow(BOOL bEnable, int nHp);
private:
	BOOL _CanHandler();
	BOOL _OnHandler();

	BOOL _OnProcessingHandler();
	BOOL _OnFinishedHandler();

	int m_nFirstIndex;
	int m_nHpLow;
	int m_bHpLow;

	GEventHandler_Quest *m_evQuest;
	GPlayerObject_Player *m_objPlayer;
};
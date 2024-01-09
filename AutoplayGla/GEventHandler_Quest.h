#pragma once

#include "GEventHandler_Base.h"
//#include "GameQuest.h"
#include "GQuestObject_Quest.h"
#include "IGameObject.h"

class GEventHandler_Quest :
	public GEventHandler_Base
{
public:
	//GEventHandler_Quest(IWebBrowser2 *wb2, GameManager *gm, GameQuest *quest);
	GEventHandler_Quest(IWebBrowser2 *wb2, IGameMod *gmod, GQuestObject_Quest *quest);
	void OnFightArena(BOOL bWin);
	void OnFightTurma(BOOL bWin);

protected:
	BOOL _CanHandler();
	BOOL _OnHandler();
	BOOL _OnProcessingHandler();
	BOOL _OnFinishedHandler();
	void _OnSynchronized( IWebBrowser2 *wb2 );


	GQuestObject_Quest *m_quest;
};
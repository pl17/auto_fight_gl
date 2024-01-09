#pragma once
#include <ExDisp.h>
#include "GEventHandler_Base.h"
#include "GEventHandler_Quest.h"
#include "IGameObject.h"
#include "GPlayerObject_Player.h"

class GEventHandler_Turma : 
	public GEventHandler_Base
{
public:
	GEventHandler_Turma(IWebBrowser2 *wb2, IGameMod *gmod, IGameObject *objTurma, GEventHandler_Quest *evQuest, GPlayerObject_Player *objPlayer);
private:
	
	BOOL _CanHandler();
	BOOL _OnHandler();

	BOOL _OnProcessingHandler();
	BOOL _OnFinishedHandler();

	int m_nFirstIndex;
	GEventHandler_Quest *m_evQuest;
	GPlayerObject_Player *m_objPlayer;
};
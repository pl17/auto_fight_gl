#include "GEventHandler_Arena.h"
#include "GameArenaServer.h"
#include "PXPath.h"
#include "Logs.h"

#pragma warning (disable: 4996)

extern IOutputDebug *gv_dbgConsole;

GEventHandler_Arena::GEventHandler_Arena( IWebBrowser2 *wb2, IGameMod *gmod, IGameObject *objArena, GEventHandler_Quest *evQuest, GPlayerObject_Player *objPlayer )
:GEventHandler_Base(wb2, gmod, objArena)
{
	this->m_nFirstIndex=-1;
	this->m_evQuest=evQuest;
	this->m_objPlayer=objPlayer;

	this->m_bHpLow=FALSE;
	this->m_nHpLow=0;
}

BOOL GEventHandler_Arena::_CanHandler()
{
	BOOL brs;

	brs=FALSE;

	if (this->GetAutoHandler())
	{
		if (this->GetCooldown()<=0)
		{
			if (this->m_objPlayer)
			{
				if (this->m_bHpLow)
				{
					if (this->m_nHpLow<this->m_objPlayer->GetHpCurrent())
						brs=TRUE;
				}
				else
					brs=TRUE;
			}
		}
	}

	return brs;
}

BOOL GEventHandler_Arena::_OnHandler()
{
	GameArenaServer *arena;
	ARENA_PLAYER *listPlayer;
	BOOL brs;

	brs=FALSE;
	arena=new GameArenaServer(this->m_wb2);
	if (arena->AttackPlayerMinLevel(this->m_nFirstIndex))
	{
		brs=TRUE;
		listPlayer=arena->GetListArenaPlayer();
		int index;
		index=arena->GetIndexPlayerMinLevel(this->m_nFirstIndex);

		LogWriteLine(gv_dbgConsole, 
			TEXT("AttackArena: %20s%5d%5d")
			, listPlayer[index].szPlayerName
			, listPlayer[index].nLevel
			, listPlayer[index].nServer);
	}
	
	delete arena;

	return brs;
}


BOOL GEventHandler_Arena::_OnProcessingHandler()
{
	BOOL brs;

	brs=TRUE;
	if (GameArenaServer::CheckBash(this->m_wb2))
	{
		this->m_nFirstIndex++;
		brs=FALSE;
		LogWriteLine(gv_dbgConsole, TEXT("AttackArena: BlackList %d"), this->m_nFirstIndex);
	}

	return brs;
}

BOOL GEventHandler_Arena::_OnFinishedHandler()
{
	BOOL brs;
	BOOL bWin;

	brs=GameArenaServer::CheckFightReport(this->m_wb2, &bWin);
	if (brs)
	{
		this->m_nFirstIndex=-1;
		if (this->m_evQuest)
			this->m_evQuest->OnFightArena(bWin);
		if (bWin)
		{
			int nGoldTotal, nGoldBase, nExp, nHornor;
			GameArenaServer::GetFightWinInfo(this->m_wb2, 0, &nGoldTotal, &nGoldBase, &nExp, &nHornor);
			GameArenaServer::nFightWin++;
			GameArenaServer::nGoldBase+=nGoldBase;
			GameArenaServer::nGoldTotal+=nGoldTotal;
			GameArenaServer::nExp+=nExp;
			GameArenaServer::nHornor+=nHornor;
			LogWriteLine(gv_dbgConsole, TEXT("AttackArena: Win Gold %d(%d) - Exp %d - Hornor: %d"), nGoldTotal, nGoldBase, nExp, nHornor);
		}
		else
		{
			GameArenaServer::nFightLose++;
			LogWriteLine(gv_dbgConsole, TEXT("AttackArena: Lose"));
		}
		LogWriteLine(gv_dbgConsole, TEXT("AttackArena: Finished"));
	}
	return brs;
}

void GEventHandler_Arena::SetHpLow( BOOL bEnable, int nHp )
{
	this->m_bHpLow=bEnable;
	this->m_nHpLow=nHp;

	if (this->GetAutoHandler())
	{
		this->FireEvent();
	}
}

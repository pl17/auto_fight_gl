#include "GEventHandler_Turma.h"
#include "GameArenaServer.h"

#include "Logs.h"

extern IOutputDebug *gv_dbgConsole;

GEventHandler_Turma::GEventHandler_Turma( IWebBrowser2 *wb2, IGameMod *gmod, IGameObject *objTurma, GEventHandler_Quest *evQuest, GPlayerObject_Player *objPlayer )
:GEventHandler_Base(wb2, gmod, objTurma)
{
	this->m_nFirstIndex=-1;
	this->m_evQuest=evQuest;
	this->m_objPlayer=objPlayer;
}

BOOL GEventHandler_Turma::_OnHandler()
{
	GameArenaServer *turma;
	ARENA_PLAYER *listPlayer;
	BOOL brs;
	int index;

	brs=FALSE;
	turma=new GameArenaServer(this->m_wb2);
	if (turma->AttackPlayerMinLevel(this->m_nFirstIndex))
	{
		brs=TRUE;
		listPlayer=turma->GetListArenaPlayer();
		index=turma->GetIndexPlayerMinLevel(this->m_nFirstIndex);
		LogWriteLine(gv_dbgConsole, 
			TEXT("AttackTurma: %20s%5d%5d")
			, listPlayer[index].szPlayerName
			, listPlayer[index].nLevel
			, listPlayer[index].nServer);
	}

	delete turma;
	return brs;
}

BOOL GEventHandler_Turma::_CanHandler()
{
	BOOL brs;

	brs=FALSE;

	if (this->GetAutoHandler())
	{
		if (this->GetCooldown()<=0)
		{
			if (this->m_objPlayer)
			{
				if (this->m_objPlayer->GetLevel()>=10)
					brs=TRUE;
			}
		}
	}

	return brs;
}

BOOL GEventHandler_Turma::_OnProcessingHandler()
{
	BOOL brs;

	brs=TRUE;
	if (GameArenaServer::CheckBash(this->m_wb2))
	{
		this->m_nFirstIndex++;
		LogWriteLine(gv_dbgConsole, TEXT("AttackTurma: BlackList %d"), this->m_nFirstIndex);
		brs=FALSE;
	}
	
	return brs;
}

BOOL GEventHandler_Turma::_OnFinishedHandler()
{
	BOOL brs;
	BOOL bWin;

	brs=GameArenaServer::CheckFightReport(this->m_wb2, &bWin);
	if (brs)
	{
		this->m_nFirstIndex=-1;
		if (this->m_evQuest)
			this->m_evQuest->OnFightTurma(bWin);
		if (bWin)
		{
			int nGoldTotal, nGoldBase, nExp, nFame;
			GameArenaServer::GetFightWinInfo(this->m_wb2, 1, &nGoldTotal, &nGoldBase, &nExp, &nFame);
			GameArenaServer::nDFightWin++;
			GameArenaServer::nDGoldBase+=nGoldBase;
			GameArenaServer::nDGoldTotal+=nGoldTotal;
			GameArenaServer::nDExp+=nExp;
			GameArenaServer::nDFame+=nFame;
			LogWriteLine(gv_dbgConsole, TEXT("AttackTurma: Win Gold %d(%d) - Exp %d - Fame: %d"), nGoldTotal, nGoldBase, nExp, nFame);
		}
		else
		{
			GameArenaServer::nDFightLose++;
			LogWriteLine(gv_dbgConsole, TEXT("AttackTurma: Lose"));
		}
		LogWriteLine(gv_dbgConsole, TEXT("AttackTurma: Finished"));
	}
	return brs;
}

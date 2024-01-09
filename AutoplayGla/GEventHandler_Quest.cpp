#include "GEventHandler_Quest.h"
#include "Logs.h"


extern IOutputDebug *gv_dbgConsole;

GEventHandler_Quest::GEventHandler_Quest( IWebBrowser2 *wb2, IGameMod *gmod, GQuestObject_Quest *quest )
:GEventHandler_Base(wb2, gmod, quest)
{
	this->m_quest=quest;
}

BOOL GEventHandler_Quest::_CanHandler()
{
	BOOL brs;

	/*if (!this->m_quest->IsInited())
		brs=TRUE;
	else if (this->m_quest)// && this->m_quest->IsInited())
	{
		brs=this->m_quest->CanAction()||this->m_quest->HasQuestFinish();
	}*/

	brs=FALSE;
	if (this->m_quest)
	{
		if (!this->m_quest->IsInited())
			brs=TRUE;
		else
			brs=this->m_quest->CanAction()||this->m_quest->HasQuestFinish();
	}

	return brs;
}

BOOL GEventHandler_Quest::_OnHandler()
{
	BOOL brs;

	LogWriteLine(gv_dbgConsole, TEXT("Quest: OnHandler"));

// 	if (this->m_gm->GetModId(this->m_wb2)==this->m_nModId)
// 	{
// 		this->m_quest->Synchronized(this->m_wb2);
// 	}
	
	brs=FALSE;
	/*
	if (!this->m_quest->CanAction())
	{
		brs=FALSE;
	}
	else
	{
		brs=this->m_quest->TryAction(this->m_wb2);
	}
	*/
	if (this->m_quest->CanAction())
	{
		brs=this->m_quest->TryAction(this->m_wb2);
	}

	return brs;
}

BOOL GEventHandler_Quest::_OnProcessingHandler()
{
	LogWriteLine(gv_dbgConsole, TEXT("Quest: OnProcessing"));

	return TRUE;
}

BOOL GEventHandler_Quest::_OnFinishedHandler()
{
	//return TRUE;
	LogWriteLine(gv_dbgConsole, TEXT("Quest: OnFinished"));
	
	//this->m_quest->Synchronize();
	//if (this->m_gm->GetModId(this->m_wb2)==this->m_nModId)
	{
		this->m_quest->Synchronized(this->m_wb2);
	}
	//this->m_quest->SetInited(TRUE);
	if (this->m_quest->CanAction())
		return FALSE;
	return TRUE;
}

void GEventHandler_Quest::OnFightArena(BOOL bWin)
{
/*
	this->m_quest->IncQuestArena();
	this->m_quest->IncQuestCombat();
	
	if (this->m_quest->HasQuestFinished())
		this->FireEvent();*/
	this->m_quest->OnArenaFinish(bWin);
	if (this->m_quest->HasQuestFinish())
		this->FireEvent();
}

void GEventHandler_Quest::OnFightTurma(BOOL bWin)
{
/*
	this->m_quest->IncQuestTurma();
	this->m_quest->IncQuestCombat();

	if (this->m_quest->HasQuestFinished())
		this->FireEvent();*/
	this->m_quest->OnTurmaFinish(bWin);
	if (this->m_quest->HasQuestFinish())
		this->FireEvent();
}

void GEventHandler_Quest::_OnSynchronized( IWebBrowser2 *wb2 )
{	
	if (this->m_gmMod && this->m_gmMod->IsTruth(wb2))
	{
		this->m_quest->Synchronized(this->m_wb2);
	}
}


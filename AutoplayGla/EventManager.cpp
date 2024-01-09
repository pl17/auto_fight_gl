#include "EventManager.h"


EventManager::EventManager()
{
	this->m_gehArena=NULL;
	this->m_gehLocation=NULL;
	this->m_gehTurma=NULL;
	this->m_gehCurrent=NULL;
	this->m_gehDungeon=NULL;
	this->m_gehQuest=NULL;
	this->m_gehMarket=NULL;
	this->m_gehPlayer=NULL;
	this->m_gehOverview=NULL;
}

EventManager::~EventManager()
{

}

void EventManager::SetEventArena( IGameEventHandler *gehArena )
{
	this->m_gehArena=gehArena;
}

void EventManager::SetEventTurma( IGameEventHandler *gehTurma )
{
	this->m_gehTurma=gehTurma;
}

void EventManager::SetEventLocation( IGameEventHandler *gehLocation )
{
	this->m_gehLocation=gehLocation;
}

void EventManager::CheckEvent()
{
	if (this->m_gehCurrent)
	{
		if (!this->m_gehCurrent->RunEvent())
		{
			return;
		}
		else
			this->m_gehCurrent=NULL;
	}
	

	if (this->m_gehArena)
	{
		if (!this->m_gehArena->RunEvent())
		{
			this->m_gehCurrent=this->m_gehArena;
			return;
		}
	}

	if (this->m_gehTurma)
	{
		if (!this->m_gehTurma->RunEvent())
		{
			this->m_gehCurrent=this->m_gehTurma;
			return;
		}
	}

	if (this->m_gehLocation)
	{
		if (!this->m_gehLocation->RunEvent())
		{
			this->m_gehCurrent=this->m_gehLocation;
			return;
		}
	}

	if (this->m_gehQuest)
	{
		if (!this->m_gehQuest->RunEvent())
		{
			this->m_gehCurrent=this->m_gehQuest;
			return;
		}
	}

	if (this->m_gehMarket)
	{
		if (!this->m_gehMarket->RunEvent())
		{
			this->m_gehCurrent=this->m_gehMarket;
			return;
		}
	}

	if (this->m_gehOverview)
	{
		if (!this->m_gehOverview->RunEvent())
		{
			this->m_gehCurrent=this->m_gehOverview;
			return;
		}
	}
}

void EventManager::OnCooldown( int nCountdown )
{
	if (this->m_gehArena)
		this->m_gehArena->OnCoolDown(nCountdown);
	if (this->m_gehTurma)
		this->m_gehTurma->OnCoolDown(nCountdown);
	if (this->m_gehLocation)
		this->m_gehLocation->OnCoolDown(nCountdown);
	if (this->m_gehDungeon)
		this->m_gehDungeon->OnCoolDown(nCountdown);
	if (this->m_gehQuest)
		this->m_gehQuest->OnCoolDown(nCountdown);
}

void EventManager::SetEventPlayer( IGameEventHandler *gehPlayer )
{
	this->m_gehPlayer=gehPlayer;
}

void EventManager::SetEventDungeon( IGameEventHandler *gehDungeon )
{
	this->m_gehDungeon=gehDungeon;
}

void EventManager::SetEventQuest( IGameEventHandler *gehQuest )
{
	this->m_gehQuest=gehQuest;
}

void EventManager::SetEventMarket( IGameEventHandler *gehMarket )
{
	this->m_gehMarket=gehMarket;
}

void EventManager::SetEventOverview( IGameEventHandler *gehOverview )
{
	this->m_gehOverview=gehOverview;
}

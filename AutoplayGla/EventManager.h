#pragma once

#include "IGameEventHandler.h"

class EventManager
{
public:
	EventManager();
	~EventManager();

	void SetEventArena(IGameEventHandler *gehArena);
	void SetEventTurma(IGameEventHandler *gehTurma);
	void SetEventLocation(IGameEventHandler *gehLocation);
	void SetEventPlayer(IGameEventHandler *gehPlayer);
	void SetEventDungeon(IGameEventHandler *gehDungeon);
	void SetEventQuest(IGameEventHandler *gehQuest);
	void SetEventMarket(IGameEventHandler *gehMarket);
	void SetEventOverview(IGameEventHandler *gehOverview);

	void CheckEvent();
	void OnCooldown(int nCountdown);
private:
	IGameEventHandler *m_gehCurrent;

	IGameEventHandler *m_gehArena;
	IGameEventHandler *m_gehTurma;
	IGameEventHandler *m_gehLocation;
	IGameEventHandler *m_gehPlayer;
	IGameEventHandler *m_gehDungeon;
	IGameEventHandler *m_gehQuest;
	IGameEventHandler *m_gehMarket;
	IGameEventHandler *m_gehOverview;
};
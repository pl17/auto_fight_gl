#pragma once

#include <ExDisp.h>
#include "ULinkList.hpp"
#include "IGameEventHandler.h"

class GEventManager
{
public:
	GEventManager();
	~GEventManager();

	void AddEvent(IGameEventHandler *handler);
	void OnCooldown(int nCooldown);
	void Run();
	void OnDocumentCompleted(IWebBrowser2 *wb2);
private:
	ULinkList<IGameEventHandler*> m_listEvent;
	IGameEventHandler *m_evNow;
};
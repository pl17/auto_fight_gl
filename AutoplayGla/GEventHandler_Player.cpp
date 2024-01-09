#include "GEventHandler_Player.h"
#include "GameLink.h"


GEventHandler_Player::GEventHandler_Player( IWebBrowser2 *wb2, IGameObject *gameobj, GEventHandler_Market *market, GEventHandler_Overview *overview )
:GEventHandler_Base(wb2, NULL, gameobj)
{
	this->m_market=market;
	this->m_evOverview=overview;
}

void GEventHandler_Player::_OnAfterSynchronized( IWebBrowser2 *wb2 )
{
	if (this->m_market)
		this->m_market->FireEvent();

	if (this->m_evOverview)
	{
		this->m_evOverview->FireEvent();
	}
}





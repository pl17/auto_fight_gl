#include "GEventHandler_Base.h"
#include "IGameObject.h"
#include "GEventHandler_Market.h"
#include "GEventHandler_Overview.h"

class GEventHandler_Player : 
	public GEventHandler_Base
{
public:
	GEventHandler_Player(IWebBrowser2 *wb2, IGameObject *gameobj, GEventHandler_Market *market, GEventHandler_Overview *overview);

private:
	void _OnAfterSynchronized( IWebBrowser2 *wb2 );

	GEventHandler_Market *m_market;
	GEventHandler_Overview *m_evOverview;
};
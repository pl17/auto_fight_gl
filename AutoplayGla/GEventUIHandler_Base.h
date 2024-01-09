#pragma once

#include "IGameEventHandler.h"

class GEventUIHandler_Base :
	public IGameEventHandler
{
protected:
	BOOL Handler();
	void OnCoolDown( int nMinisecond );
	void SetCooldown( int nCooldown );
	int GetCooldown();
	BOOL CheckEvent();
	void FireEvent();
	void SetCanHandler( BOOL bCanHandler );
	BOOL GetCanHandler();

	virtual void AfterSynchronized(IWebBrowser2 *wb2);
};
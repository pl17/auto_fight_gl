#pragma once

#include "IGameEventHandler.h"
#include <ExDisp.h>
#include "IGameObject.h"
#include "IGameMod.h"

/*
Implement interface IGameEventHandler for basic call
*/
class GEventHandler_Base : 
	public IGameEventHandler
{
public:
	GEventHandler_Base(IWebBrowser2 *wb2, IGameMod *gmod, IGameObject *objMain);

	void Synchronized(IWebBrowser2 *wb2);

	void FireEvent();
	BOOL RunEvent();

	void SetCooldown(int nCooldown);
	int GetCooldown();
	void OnCoolDown(int nCooldown);

	void SetAutoHandler(BOOL bAutoHandler);
	BOOL GetAutoHandler();
protected:
	virtual BOOL _CanHandler();
	virtual BOOL _OnHandler();
	virtual BOOL _OnProcessingHandler();
	virtual BOOL _OnFinishedHandler();
	virtual void _OnSynchronized( IWebBrowser2 *wb2 );
	virtual void _OnAfterSynchronized(IWebBrowser2 *wb2);
	

	IWebBrowser2 *m_wb2;
	IGEH_Status m_status;
	IGameObject *m_objMain;
	IGameMod *m_gmMod;
private:
	BOOL _Handler();

	int m_nTimeoutCooldown;
	BOOL m_bEventFire;
	BOOL m_bAutoHandle;
};
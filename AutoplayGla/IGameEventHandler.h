#pragma once

#include <Windows.h>
#include <ExDisp.h>

class IGameEventHandler
{
public:
	/*
	Method for Synchronized when event finished
	*/
	virtual void Synchronized(IWebBrowser2 *wb2)=0;

	/*
	Method for cooldown time event
	*/
	virtual void OnCoolDown(int nCooldown)=0;
	virtual void SetCooldown(int nCooldown)=0;
	virtual int GetCooldown()=0;

	/*Method Run event, check all condition for event
	*/
	virtual BOOL RunEvent()=0;

	//Method for manually fire event
	virtual void FireEvent()=0;

	/*
	Method for auto option
	*/
	virtual void SetAutoHandler(BOOL bAutoHandler)=0;
	virtual BOOL GetAutoHandler()=0;

	//Event status
	enum IGEH_Status
	{
		EVENT_STATUS_FREE,
		EVENT_STATUS_PROCESSING,
		EVENT_STATUS_FINISHED,
		EVENT_STATUS_TIMEOUT,
		EVENT_STATUS_BUSY
	};

protected:
	//Event fire when Synchronized method is called
	virtual void _OnSynchronized(IWebBrowser2 *wb2)=0;

	//Event fire after Synchronized method is called
	virtual void _OnAfterSynchronized(IWebBrowser2 *wb2)=0;

	/*
	Method handler for event
	return
		TRUE:	Event handled, finished
		FALSE:	Event not handled, handle again
	*/
	virtual BOOL _Handler()=0;
};

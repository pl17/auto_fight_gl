#pragma once

#include <ExDisp.h>
#include "ISynchronized.h"

class IGameObject
{
public:
	enum GO_Status
	{
		STATUS_SUCCESS,
		STATUS_NOTINIT,
		STATUS_ZERO,
		STATUS_FORCE
	};

	virtual void Synchronized(IWebBrowser2 *wb2)=0;
	virtual void SetCooldown(int nCooldown)=0;
	virtual int GetCooldown()=0;
	virtual GO_Status OnCooldown(int nCountdown)=0;

protected:
	virtual void _SetIWeb2(IWebBrowser2 *wb2)=0;
	virtual void _SynchronizedCooldown()=0;
};

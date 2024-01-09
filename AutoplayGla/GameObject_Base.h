#pragma once

#include <ExDisp.h>
#include "IGameObject.h"

class GameObject_Base :
	public IGameObject
{
public:
	GameObject_Base();

	void SetCooldown( int nCooldown );
	int GetCooldown();
	GO_Status OnCooldown( int nCountdown );

protected:
	IWebBrowser2 *m_wb2;
	int m_nCooldown;
	GO_Status m_esCooldown;

	void _SetIWeb2(IWebBrowser2 *wb2);
	void _SynchronizedCooldown();
};
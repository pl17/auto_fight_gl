#pragma once

#include "GameObject_Base.h"

class GLocationObject_Base :
	public GameObject_Base
{
public:
	GLocationObject_Base(int nModId);

	//Implement virtual method
	void Synchronized( IWebBrowser2 *wb2 );

	//Local method
	int GetCurrentPoint();
	int GetMaxPoint();
protected:
	int m_nCurrentPoint;
	int m_nMaxPoint;
private:
	int m_nModId;
};
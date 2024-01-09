#pragma once

#include <ExDisp.h>
#include "GameObject_Base.h"

/*
Class provide method access to arena and turma
*/
class GArenaObject_Base :
	public GameObject_Base
{
public:
	GArenaObject_Base(int nModId);

	//Implement virtual method
	void Synchronized( IWebBrowser2 *wb2 );

	//Local method
	int GetRank();

protected:
	int m_nRank;

private:
	int m_nModId;
};
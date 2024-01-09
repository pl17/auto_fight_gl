#pragma once

#include "GameObject_Base.h"

class GPlayerObject_Player : 
	public GameObject_Base
{
public:
	GPlayerObject_Player();

	//Implement virtual method
	virtual void Synchronized( IWebBrowser2 *wb2 );



	//Local method
	int GetLevel();
	int GetRank();
	int GetRubi();
	int GetGold();
	int GetHpCurrent();
	int GetHpMax();
	int GetExpCurrent();
	int GetExpMax();
private:
	int m_nLevel;
	int m_nRank;
	int m_nRubi;
	int m_nGold;
	int m_nHpCurrent;
	int m_nHpMax;
	int m_nExpCurrent;
	int m_nExpMax;
};
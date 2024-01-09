#pragma once

#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <ExDisp.h>

#include "GameObj_XPathConst.h"
#include "GameLink.h"

class GameManager
{
public:
	GameManager(IWebBrowser2 *wb2Location);
	~GameManager();

	BOOL GotoMod(IWebBrowser2 *wb2, int nModId, int nSubModId);
	static BOOL SimulatorClick(IWebBrowser2 *wb2, GAMEOBJ_XPATH *xpath);
	int GetModId(IWebBrowser2 *wb2);
private:
	const GAMEOBJ_XPATH* _FindXpathByMod(int nModId, int nSubModId);
	//BOOL _GotoArena(int submod, int type);

	GameLink *m_gameLink;
	IWebBrowser2 *m_wb2Location;
};
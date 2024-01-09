#pragma once

#include "GameThread_Base.h"

class GameThread_General :
	public GameThread_Base
{
public:

private:
	HWND m_hMain;
	

	void _OnTimer1s();
	void _OnDocumentFinished();
	void _Init( IWebBrowser2 *wb2 );

};
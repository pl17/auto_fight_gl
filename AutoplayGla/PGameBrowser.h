#pragma once

#include <ExDisp.h>
#include "PCallbackBrowser.h"
#include "PBrowserWrapper.h"

class PGameBrowser
{
public:
	PGameBrowser();
	static BOOL Register();

private:
	IWebBrowser2 *m_wb2;
	int m_nStatus;
	int m_nActionId;
	int m_nLocationId;
	PBrowserWrapper *m_wrapper;

	void _Init();

	void _OnCreate(HWND hWnd);

	static LRESULT CALLBACK _WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static const TCHAR *m_lpcszClassName;
	static const TCHAR *m_lpcszCLSID;
};
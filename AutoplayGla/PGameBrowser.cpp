#include "PGameBrowser.h"


PGameBrowser::PGameBrowser()
{
	this->_Init();
}

BOOL PGameBrowser::Register()
{
	WNDCLASSEX wcex;

	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize=sizeof(wcex);
	wcex.style=CS_GLOBALCLASS|CS_DBLCLKS;
	wcex.lpfnWndProc=PGameBrowser::_WndProc;
	wcex.cbWndExtra=4;
	wcex.hInstance=GetModuleHandle(NULL);
	wcex.lpszClassName=PGameBrowser::m_lpcszClassName;
	return (BOOL)RegisterClassEx(&wcex);

}

LRESULT CALLBACK PGameBrowser::_WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	PGameBrowser *browser=NULL;

	browser=(PGameBrowser*)GetWindowLong(hWnd, GWL_USERDATA);
	switch(msg)
	{
	case WM_CREATE:
		browser=new PGameBrowser();
		browser->_OnCreate(hWnd);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

const TCHAR* PGameBrowser::m_lpcszClassName = TEXT("AutoFight");
const TCHAR* PGameBrowser::m_lpcszCLSID=TEXT("{8856F961-340A-11D0-A96B-00C04FD705A2}");

/*
Event wndproc
*/
void PGameBrowser::_OnCreate(HWND hWnd)
{

}


void PGameBrowser::_Init()
{
	CLSID clsid;

	CLSIDFromString((LPOLESTR)PGameBrowser::m_lpcszCLSID, &clsid);

}
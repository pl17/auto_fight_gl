#pragma once

#include <Windows.h>
#include <ExDisp.h>

class GameThread_Base
{
public:
	GameThread_Base();

	void Run();
protected:
	HWND m_hWnd;
	HWND m_hParent;
	IWebBrowser2 *m_wb2;
	HANDLE m_hThread;
	BOOL m_bCanRun;
	class AX *m_ax;

	static DWORD WINAPI _Run(LPVOID lpParams);
	static LRESULT CALLBACK _WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static BOOL _RegisterClass();

	static const TCHAR *_lpszClassName;

	virtual void _OnTimer1s()=0;
	virtual void _OnDocumentFinished()=0;
	virtual void _Init(IWebBrowser2 *wb2)=0;
};
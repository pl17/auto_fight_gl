#include "GameThread_Base.h"
#include "ax.h"


GameThread_Base::GameThread_Base()
{
	this->m_hWnd=NULL;
	this->m_hParent=NULL;
	this->m_wb2=NULL;
	this->m_hThread=NULL;
	this->m_ax=NULL;


}

void GameThread_Base::Run()
{
	this->m_hThread=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GameThread_Base::_Run, this, 0, NULL);
}

DWORD WINAPI GameThread_Base::_Run( LPVOID lpParams )
{
	GameThread_Base *pthis;

	CoInitialize(NULL);
	AXRegister();
	GameThread_Base::_RegisterClass();

	pthis=(GameThread_Base*)lpParams;

	pthis->m_hWnd=CreateWindow(GameThread_Base::_lpszClassName, TEXT("{8856F961-340A-11D0-A96B-00C04FD705A2}")
		, WS_OVERLAPPEDWINDOW
		, 0, 0, 1000, 700
		, NULL
		, NULL
		, NULL
		, NULL);

	if (pthis->m_hWnd)
	{
		SendMessage(pthis->m_hWnd, AX_INPLACE, 1, 0);
		//SendMessage(hBrowser, AX_ENABLE_MENUCONTEXT, 0, 0);

		//SendMessage(hBidItem, AX_SETCALLBACK_EVENTHANDLER, AX_EVENT_DOCUMENTCOMPLETE, (LPARAM)cbDocumentComplete);
		SendMessage(pthis->m_hWnd, AX_QUERYINTERFACE, (WPARAM)&IID_IWebBrowser2, (LPARAM)&pthis->m_wb2);

		pthis->m_ax=new AX("{8856F961-340A-11D0-A96B-00C04FD705A2}");

		if (pthis->m_wb2)
		{
			pthis->_Init(pthis->m_wb2);

			SetWindowLong(pthis->m_hWnd, GWL_USERDATA, (LONG)pthis);

			SetTimer(pthis->m_hWnd, 17, 1000, NULL);

			pthis->m_wb2->Navigate((BSTR)TEXT("s5.vn.gladiatus.gameforge.com/game"), 0, 0, 0, 0);
			pthis->m_wb2->put_Silent(TRUE);
		}
	}

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	CoUninitialize();
	return 0;
}


BOOL GameThread_Base::_RegisterClass()
{
	WNDCLASS wc;

	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor=LoadCursor(GetModuleHandle(NULL), IDC_ARROW);
	wc.hIcon=LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance=GetModuleHandle(NULL);
	wc.lpfnWndProc=GameThread_Base::_WndProc;
	wc.lpszClassName=GameThread_Base::_lpszClassName;
	wc.lpszMenuName=NULL;
	wc.style=CS_HREDRAW|CS_VREDRAW;

	return (BOOL)RegisterClass(&wc);
}

const TCHAR* GameThread_Base::_lpszClassName=TEXT("AutoGladiatus");

LRESULT CALLBACK GameThread_Base::_WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	LRESULT rs;
	GameThread_Base *pthis;

	pthis=(GameThread_Base*)GetWindowLong(hWnd, GWL_USERDATA);

	if (pthis && pthis->m_ax)
		rs=AXWndProcV2(pthis->m_ax, hWnd, msg, wParam, lParam);
	else
		rs=0;

	switch(msg) 
	{
	case WM_TIMER:
		pthis->_OnTimer1s();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return rs;
}

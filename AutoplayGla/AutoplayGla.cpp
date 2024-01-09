#define _WIN32_WINNT 0x0500
#define WIN32_LEAN_AND_MEAN

#pragma pack(1)

#include <Windows.h>
#include <Tchar.h>
#include <ObjIdl.h>
#include <GdiPlus.h>
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "msimg32.lib")
#include "resource.h"
#include "MControls.h"

INT_PTR CALLBACK DlgMainProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd )
{
	int rs;
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nShowCmd);

	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	//Init Gdiplus
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

__try
{
	rs=(int)DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLGMAIN), NULL, DlgMainProc);
}
__except (EXCEPTION_EXECUTE_HANDLER)
{
	OutputDebugString(TEXT("Error\n"));
}
	
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return rs;
}

INT_PTR CALLBACK DlgMainProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WORD id;
	PAINTSTRUCT ps;
	HDC hdc;

	switch(msg)
	{
	case WM_INITDIALOG:
		mcOnLoad(hDlg);
		//SetTimer(hDlg, 17, 1000, NULL);
		return (INT_PTR)TRUE;
	case WM_PAINT:
		hdc=BeginPaint(hDlg, &ps);
		if (tab)
			tab->OnDraw(hdc);
		EndPaint(hDlg, &ps);
		return (INT_PTR)TRUE;
	case WM_USER+17:
		InvalidateRect(hDlg, (RECT*)wParam, TRUE);
		return (INT_PTR)TRUE;
	case WM_TIMER:
		if (wParam==17)
		{
			LogWriteLine(gv_dbgConsole, TEXT("Timer: Start"));
			for (int i=0; i<nListCallbackTimer1s; i++)
			{
				listCallbackTimer1s[i](mc_lpParam[i]);
				mcDisplayValue();
			}
			LogWriteLine(gv_dbgConsole, TEXT("Timer: End"));
		}
		else if (wParam==88)
		{
			mcCooldownBidItem(NULL);
		}
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		id=LOWORD(wParam);
		switch(id)
		{
		case IDC_CHKSHOWBROWSER:
			mcOnChkShowBrowser(hDlg);
			break;
		case IDC_CHKAUTOARENA:
			mcOnChkAutoArena(hDlg);
			break;
		case IDC_CHKAUTOTURMA:
			mcOnChkAutoTurma(hDlg);
			break;
		case IDC_CHKAUTOLOCATION:
			mcOnChkAutoLocation(hDlg);
			break;
		case IDC_BTNTEST:
			mcOnBtnTest(hDlg);
			break;
		case IDC_CHKARENAHP:
			mcOnChkArenaHp(hDlg);
			break;
		case IDC_CHKAUTOBIDITEM:
			mcOnChkBidItem(hDlg);
			break;
		case IDC_BTNSELL:
			mcOnBtnSell(hDlg);
			break;
		case IDC_BTNBUY:
			mcOnBtnBuy(hDlg);
			break;
		}
		return (INT_PTR)TRUE;
	case WM_CLOSE:
		mcOnClose(hDlg);
		return (INT_PTR)TRUE;
	}

	return (INT_PTR)FALSE;
}
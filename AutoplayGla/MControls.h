#include "ax.h"
#include "PSimulator.h"
#include "GameArenaServer.h"
#include "PXPath.h"
#include "GameLink.h"
#include <mshtmdid.h>
#include <atlbase.h>
#include <atlcom.h>
#include "GEventHandler_Location.h"
#include "GEventHandler_Arena.h"
#include "GEventHandler_Turma.h"
#include "GEventHandler_Quest.h"
#include "GEventHandler_Player.h"
#include "GEventHandler_Dungeon.h"
#include "GEventHandler_Market.h"
#include "GEventHandler_Overview.h"


//#include "GameQuest.h"
#include "TestMouseEvent.h"
#include <ShlGuid.h>
#include "GameTabGeneral.h"

#include "GArenaObject_Arena.h"
#include "GArenaObject_Turma.h"
#include "GLocationObject_Location.h"
#include "GLocationObject_Dungeon.h"
#include "GPlayerObject_Player.h"

#include "GameMod_Arena.h"

#include "GEventUIHandler_Inventory.h"
#include "GameItem.h"
#include "PParser.h"

#include "EventManager.h"
#include "BrowserUtility.h"
#include "ActionSimulator.h"

#include "ItemObject.h"
#include "GItemObject_Market.h"
#include "ItemInvObject.h"
#include "GItemObject_Inventory.h"
#include "GItemObject_Shop.h"
#include "GItemObject_ShopInv.h"

#include "GameMod_Arena.h"
#include "GameMod_Quest.h"
#include "GameMod_Overview.h"

#include "MouseHandler.h"
#pragma warning(disable: 4996 4312)
//#include <CommCtrl.h>
//#pragma comment(lib, "comctl32.lib")

#include "WebForm.h"
#include "GEventManager.h"

#include "Logs.h"

HWND hBrowser=NULL;
HWND hBidItem=NULL;
HWND hBrowser1=NULL, hBrowser2=NULL;
IWebBrowser2 *gv_wb2;
IWebBrowser2 *gv_wb2BidItem=NULL;
PCallbackBrowser *cbDocumentComplete=NULL;
PCallbackBrowser *cbBidGold=NULL;
IOutputDebug *gv_dbgConsole;
GameTabGeneral *tab=NULL;
//GameQuest *gv_quest=NULL;;
LRESULT CALLBACK mcWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
DWORD WINAPI mcThreadTimer(LPARAM lpParam);
DWORD WINAPI mcThreadBidItem(LPARAM lpParam);

//Game objects
GArenaObject_Arena *gobj_arena=NULL;
GArenaObject_Turma *gobj_turma=NULL;
GLocationObject_Location *gobj_location=NULL;
GLocationObject_Dungeon *gobj_dungeon=NULL;
GPlayerObject_Player *gobj_player=NULL;
GQuestObject_Quest *gobj_quest;
GItemObject_Market *gobj_market=NULL;
//GameQuest *gobj_quest=NULL;
GItemObject_ShopInv *gobj_shopinv=NULL;
GItemObject_Shop *gobj_shop=NULL;
GItemObject_Inventory *gobj_inv=NULL;

//Game events
GEventHandler_Location *geh_loc=NULL;
GEventHandler_Arena *geh_arena=NULL;
GEventHandler_Turma *geh_turma=NULL;
GEventHandler_Quest *geh_quest=NULL;
GEventHandler_Player *geh_player=NULL;
GEventHandler_Dungeon *geh_dungeon=NULL;
GEventHandler_Market *geh_market=NULL;
GEventHandler_Overview *geh_overview=NULL;

//UI Event customize
GEventUIHandler_Inventory *geh_inv=NULL;

//Manager event
EventManager *eventmgr=NULL;
EventManager *eventBidItem=NULL;
HANDLE hEventBidGold=NULL;
GEventManager *gevMng=NULL;

GameMod_Arena *gm_arena=NULL;
GameMod_Quest *gm_quest=NULL;
GameMod_Overview *gm_overview=NULL;
GameMod_Arena *gm_turma=NULL;


#define MC_MAX_CALLBACK1S	20

typedef void (__stdcall *CallbackTimer1s)(void *lpParam);
CallbackTimer1s listCallbackTimer1s[MC_MAX_CALLBACK1S];
void* mc_lpParam[MC_MAX_CALLBACK1S];
int nListCallbackTimer1s=0;

void __stdcall mcCooldown(void *lpParam)
{
// 	if (eventmgr)
// 	{
// 		eventmgr->OnCooldown(1);
// 
// 		eventmgr->CheckEvent();
// 	}
	if (gevMng)
	{
		gevMng->OnCooldown(1);

		gevMng->Run();
	}
}

void __stdcall mcCooldownBidItem(void *lpParam)
{
	if (eventBidItem)
	{
		eventBidItem->OnCooldown(1);

		eventBidItem->CheckEvent();
	}
}

void _mcSetCallbackTimer1s(CallbackTimer1s fnc, void *lpParam)
{
	if (nListCallbackTimer1s<MC_MAX_CALLBACK1S)
	{
		listCallbackTimer1s[nListCallbackTimer1s]=fnc;
		mc_lpParam[nListCallbackTimer1s]=lpParam;
		nListCallbackTimer1s++;
	}
}


ATOM mcRegisterClass()
{
	WNDCLASS wc;

	wc.cbClsExtra=0;
	wc.cbWndExtra=0;
	wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wc.hCursor=LoadCursor(GetModuleHandle(NULL), IDC_ARROW);
	wc.hIcon=LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance=GetModuleHandle(NULL);
	wc.lpfnWndProc=mcWndProc;
	wc.lpszClassName=TEXT("AutoGladiatus");
	wc.lpszMenuName=NULL;
	wc.style=CS_HREDRAW|CS_VREDRAW;

	return RegisterClass(&wc);
}

void mcOnLoad2(HWND hDlg)
{
	CoInitialize(NULL);

	mcRegisterClass();
	hBrowser1=CreateWindow(TEXT("AutoGladiatus"), TEXT("SysMonitor"), WS_OVERLAPPEDWINDOW|WS_VISIBLE, 0, 0, 500, 500, NULL, NULL, NULL, NULL);
	SetTimer(hBrowser1, 17, 1000, NULL);

	hBrowser=CreateWindowEx(0,WEBFORM_CLASS,_T("about:blank"),WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_VSCROLL,0,0,100,100,hBrowser1,(HMENU)19,GetModuleHandle(0),0);
	//hBrowser=WebformCreate(hBrowser1, 19);
	WebformGo(hBrowser, TEXT("s5.vn.gladiatus.gameforge.com/game"));

	hBrowser2=CreateWindow(TEXT("AutoGladiatus"), TEXT("SysMonitor"), WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL, 0, 0, 500, 500, NULL, NULL, NULL, NULL);
	SetTimer(hBrowser2, 18, 1000, NULL);

	//hBidItem=WebformCreate(hBrowser2, 20);
	hBidItem=CreateWindow(WEBFORM_CLASS, TEXT("s5.vn.gladiatus.gameforge.com/game"), WS_CHILD|WS_CLIPSIBLINGS|WS_VISIBLE|WS_VSCROLL, 0, 0, 100, 100, hBrowser2, (HMENU)20, NULL, 0);
	WebformGo(hBidItem, TEXT("s5.vn.gladiatus.gameforge.com/game"));


	//Test tab
	tab=new GameTabGeneral(hDlg);

	LogCreateConsole(gv_dbgConsole);
	LogShowTime(gv_dbgConsole, FALSE);

	//Init game object
	gobj_player=new GPlayerObject_Player();
	gobj_turma=new GArenaObject_Turma();
	gobj_arena=new GArenaObject_Arena();
	gobj_dungeon=new GLocationObject_Dungeon();
	gobj_location=new GLocationObject_Location();
	gobj_quest=new GQuestObject_Quest();
	gobj_market=new GItemObject_Market(gobj_player);
	//gobj_quest=new GameQuest();

	if (hBrowser && hBidItem)
	{
		cbDocumentComplete=new PCallbackBrowser();
		cbBidGold=new PCallbackBrowser();

		gv_wb2=WebformGetBrowser(hBrowser);
		gv_wb2BidItem=WebformGetBrowser(hBidItem);

		if (gv_wb2 && gv_wb2BidItem)
		{
// 			geh_quest=new GEventHandler_Quest(gv_wb2, gm, gobj_quest);
// 			geh_arena=new GEventHandler_Arena(gv_wb2, gm, geh_quest, gobj_arena, gobj_player);
// 			geh_turma=new GEventHandler_Turma(gv_wb2, gm, geh_quest, gobj_turma, gobj_player);
// 			geh_loc=new GEventHandler_Location(gv_wb2, gm, gobj_location, gobj_player);
// 			geh_dungeon=new GEventHandler_Dungeon(gv_wb2, gm, gobj_dungeon, gobj_player);
// 			geh_inv=new GEventUIHandler_Inventory();
// 			//WaitForSingleObject(hEventBidGold, INFINITE);
// 			GameManager *newgm=new GameManager(gv_wb2BidItem);
// 			geh_market=new GEventHandler_Market(gv_wb2BidItem, newgm, gobj_market, gobj_player);
// 			geh_player=new GEventHandler_Player(gv_wb2, gm, gobj_player, geh_market);


			cbDocumentComplete->Add(geh_player);
			cbDocumentComplete->Add(geh_arena);
			cbDocumentComplete->Add(geh_turma);
			cbDocumentComplete->Add(geh_loc);
			cbDocumentComplete->Add(geh_dungeon);
			cbDocumentComplete->Add(geh_quest);
			cbDocumentComplete->Add(geh_inv);
			//cbDocumentComplete->Add(geh_market);

			cbBidGold->Add(geh_market);
			//SendMessage(hBidItem, AX_SETCALLBACK_EVENTHANDLER, AX_EVENT_DOCUMENTCOMPLETE, (LPARAM)cbBidGold);

			eventmgr=new EventManager();
			eventmgr->SetEventArena(geh_arena);
			eventmgr->SetEventTurma(geh_turma);
			eventmgr->SetEventLocation(geh_loc);
			eventmgr->SetEventDungeon(geh_dungeon);
			//eventmgr->SetEventQuest(geh_quest);
			eventmgr->SetEventMarket(geh_market);
			geh_quest->FireEvent();
			SetTimer(hBrowser, 17, 1000, NULL);
			SetTimer(hBidItem, 18, 1000, NULL);
			//SetTimer(hDlg, 17, 1000, NULL);
			_mcSetCallbackTimer1s(mcCooldown, NULL);

			//gv_wb2->Navigate((BSTR)TEXT("s5.vn.gladiatus.gameforge.com/game"), 0, 0, 0, 0);
			//gv_wb2->Navigate((BSTR)TEXT("http://s201.de.gladiatus.gameforge.com/game"), 0, 0, 0, 0);
			//gv_wb2->Navigate((BSTR)TEXT("localhost/test.html"), 0, 0, 0, 0);
			gv_wb2->put_Silent(TRUE);
			gv_wb2BidItem->put_Silent(TRUE);
		}
	}
}

void mcOnLoad(HWND hDlg)
{
	//Init browser
	CoInitialize(NULL);

	//InitCommonControls();
	AXRegister();
	mcRegisterClass();

	//Test tab
 	tab=new GameTabGeneral(hDlg);

	RECT rcParent;
	GetWindowRect(hDlg, &rcParent);

	hBrowser=CreateWindow(TEXT("AutoGladiatus"), TEXT("{8856F961-340A-11D0-A96B-00C04FD705A2}")
		, WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME
		, rcParent.left, rcParent.top, 1000, 700
		, NULL
		, NULL
		, NULL
		, NULL);

	LogCreateConsole(gv_dbgConsole);
	LogShowTime(gv_dbgConsole, FALSE);

	//Init game object
	gobj_player=new GPlayerObject_Player();
	gobj_turma=new GArenaObject_Turma();
	gobj_arena=new GArenaObject_Arena();
	gobj_dungeon=new GLocationObject_Dungeon();
	gobj_location=new GLocationObject_Location();
	gobj_quest=new GQuestObject_Quest();
	gobj_market=new GItemObject_Market(gobj_player);

	gobj_shop=new GItemObject_Shop();
	gobj_inv=new GItemObject_Inventory();
	gobj_shopinv=new GItemObject_ShopInv(gobj_shop, gobj_inv, gobj_player);

	hEventBidGold=CreateEvent(NULL, TRUE, FALSE, NULL);
	//CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mcThreadBidItem, (LPVOID)hDlg, 0, NULL));

	if (hBrowser)
	{
		SendMessage(hBrowser, AX_INPLACE, 1, 0);
		//SendMessage(hBrowser, AX_ENABLE_MENUCONTEXT, 0, 0);
		cbDocumentComplete=new PCallbackBrowser();
		cbBidGold=new PCallbackBrowser();
		
		SendMessage(hBrowser, AX_SETCALLBACK_EVENTHANDLER, AX_EVENT_DOCUMENTCOMPLETE, (LPARAM)cbDocumentComplete);
		SendMessage(hBrowser, AX_QUERYINTERFACE, (WPARAM)&IID_IWebBrowser2, (LPARAM)&gv_wb2);
		
		if (gv_wb2)
		{
			IUnknown *u1, *u2;
			DWORD dwCookie;

			u1=(IUnknown*)SendMessage(hBrowser, AX_GETAXINTERFACE, 0, 0);
			u1->QueryInterface(IID_IUnknown, (void**)&u2);
			AtlAdvise((IUnknown*)gv_wb2, u2, DIID_DWebBrowserEvents2, &dwCookie);
			u2->Release();
			u1->Release();

			gm_quest=new GameMod_Quest();
			gm_quest->SetMod(TEXT("?mod=quests"));
 			geh_quest=new GEventHandler_Quest(gv_wb2, gm_quest, gobj_quest);

			gm_arena=new GameMod_Arena();
			gm_arena->SetMod(TEXT("?mod=arena&submod=serverArena&aType=2"));
 			geh_arena=new GEventHandler_Arena(gv_wb2, gm_arena, gobj_arena, geh_quest, gobj_player);


			gm_overview=new GameMod_Overview();
			gm_overview->SetMod(TEXT("?mod=overview"));
			geh_overview=new GEventHandler_Overview(gv_wb2, gm_overview, gobj_player, gobj_inv);

			gm_turma=new GameMod_Arena();
			gm_turma->SetMod(TEXT("?mod=arena&submod=serverArena&aType=3"));
			geh_turma=new GEventHandler_Turma(gv_wb2, gm_turma, gobj_turma, geh_quest, gobj_player);

// 			geh_turma=new GEventHandler_Turma(gv_wb2, gm, geh_quest, gobj_turma, gobj_player);
// 			geh_loc=new GEventHandler_Location(gv_wb2, gm, gobj_location, gobj_player);
// 			geh_dungeon=new GEventHandler_Dungeon(gv_wb2, gm, gobj_dungeon, gobj_player);
// 			geh_inv=new GEventUIHandler_Inventory();
			//WaitForSingleObject(hEventBidGold, INFINITE);
			//mcThreadBidItem(NULL);

			CloseHandle(hEventBidGold);
			//geh_market=new GEventHandler_Market(gv_wb2BidItem, gm, gobj_market, gobj_player);
			//geh_player=new GEventHandler_Player(gv_wb2, gm, gobj_player, geh_market);
			geh_player=new GEventHandler_Player(gv_wb2, gobj_player, NULL, geh_overview);
			

			cbDocumentComplete->Add(geh_player);
 			cbDocumentComplete->Add(geh_arena);
 			cbDocumentComplete->Add(geh_turma);
 			cbDocumentComplete->Add(geh_loc);
 			cbDocumentComplete->Add(geh_dungeon);
 			cbDocumentComplete->Add(geh_quest);
 			cbDocumentComplete->Add(geh_inv);
			cbDocumentComplete->Add(geh_overview);

			//cbBidGold->Add(geh_market);
			//SendMessage(hBidItem, AX_SETCALLBACK_EVENTHANDLER, AX_EVENT_DOCUMENTCOMPLETE, (LPARAM)cbBidGold);

// 			eventmgr=new EventManager();
// 			eventmgr->SetEventArena(geh_arena);
// 			eventmgr->SetEventTurma(geh_turma);
// 			eventmgr->SetEventLocation(geh_loc);
// 			eventmgr->SetEventDungeon(geh_dungeon);
// 			eventmgr->SetEventQuest(geh_quest);
// 			eventmgr->SetEventOverview(geh_overview);

			gevMng=new GEventManager();
			gevMng->AddEvent(geh_arena);
			//gevMng->AddEvent(geh_turma);
			gevMng->AddEvent(geh_overview);
			gevMng->AddEvent(geh_quest);
			geh_quest->FireEvent();

			SetTimer(hBrowser, 17, 1000, NULL);
			//SetTimer(hDlg, 17, 1000, NULL);
			_mcSetCallbackTimer1s(mcCooldown, NULL);

			//gv_wb2->Navigate((BSTR)TEXT("s15.en.gladiatus.gameforge.com/game"), 0, 0, 0, 0);
			gv_wb2->Navigate((BSTR)TEXT("http://s201.de.gladiatus.gameforge.com/game"), 0, 0, 0, 0);
			//gv_wb2->Navigate((BSTR)TEXT("localhost/test.html"), 0, 0, 0, 0);
			gv_wb2->put_Silent(TRUE);
		}
	}
}

void mcOnLoad1(HWND hDlg)//Test mouse event
{
	CoInitialize(NULL);

	//InitCommonControls();
	AXRegister();
	mcRegisterClass();

	gobj_inv=new GItemObject_Inventory();
	gobj_player=new GPlayerObject_Player();

	hBrowser=CreateWindow(TEXT("AutoGladiatus"), TEXT("{8856F961-340A-11D0-A96B-00C04FD705A2}")
		, WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME
		, 0, 0, 1000, 700
		, NULL
		, NULL
		, NULL
		, NULL);

	

	if (hBrowser)
	{
		SendMessage(hBrowser, AX_INPLACE, 1, 0);
		SendMessage(hBrowser, AX_QUERYINTERFACE, (WPARAM)&IID_IWebBrowser2, (LPARAM)&gv_wb2);

		if (gv_wb2)
		{
			//gv_wb2->Navigate((BSTR)TEXT("s15.en.gladiatus.gameforge.com/game"), 0, 0, 0, 0);
			//gv_wb2->Navigate((BSTR)TEXT("localhost/testeventmouse.html"), 0, 0, 0, 0);
			gv_wb2->Navigate((BSTR)TEXT("s201.de.gladiatus.gameforge.com/game"), 0, 0, 0, 0);
			gv_wb2->put_Silent(TRUE);

			//geh_player=new GEventHandler_Player(gv_wb2, gobj_player, NULL);
		}
	}
}

void mcOnClose(HWND hDlg)
{
	LogClose(gv_dbgConsole);

	CoUninitialize();
	UnregisterClass(TEXT("AutoGladiatus"), GetModuleHandle(NULL));
	//if (player_header) delete player_header;
	//if (gm) delete gm;
	EndDialog(hDlg, 0);
}


void mcDisplayValue()
{
	TCHAR szTxt[255];
	int h, m, s;

	wsprintf(szTxt, TEXT("%d"), gobj_player->GetGold());
	tab->SetGold(szTxt);

	wsprintf(szTxt, TEXT("%d"), gobj_player->GetRubi());
	tab->SetRubi(szTxt);

	wsprintf(szTxt, TEXT("%d"), gobj_player->GetLevel());
	tab->SetLevel(szTxt);

	wsprintf(szTxt, TEXT("%d"), gobj_player->GetRank());
	tab->SetRank(szTxt);

	if (gobj_player->GetExpMax()!=0)
	{
		swprintf(szTxt, TEXT("Exp: %d/%d (%.2f%%)"), gobj_player->GetExpCurrent(), gobj_player->GetExpMax(), (float)gobj_player->GetExpCurrent()*100/gobj_player->GetExpMax());
		tab->SetExp(szTxt);
	}

	//wsprintf(szTxt, TEXT("%d/%d"), gobj_player->GetExpCurrent(), gobj_player->GetExpMax());
	if (gobj_player->GetHpMax()!=0)
	{
		swprintf(szTxt, TEXT("HP: %d/%d (%.2f%%)"), gobj_player->GetHpCurrent(), gobj_player->GetHpMax(), (float)gobj_player->GetHpCurrent()*100/gobj_player->GetHpMax());
		tab->SetHp(szTxt);
	}

	s=gobj_arena->GetCooldown();
	h=s/3600;
	s=s%3600;
	m=s/60;
	s=s%60;

	_stprintf(szTxt, TEXT("%02d:%02d:%02d"), h, m, s);
	tab->SetArena(szTxt);

	s=gobj_quest->GetCooldown();
	h=s/3600;
	s=s%3600;
	m=s/60;
	s=s%60;
	_stprintf(szTxt, TEXT("Quest: %02d:%02d:%02d"), h, m, s);
	tab->SetQuest(szTxt);

	s=gobj_turma->GetCooldown();
	h=s/3600;
	s=s%3600;
	m=s/60;
	s=s%60;

	_stprintf(szTxt, TEXT("%02d:%02d:%02d"), h, m, s);
	tab->SetTurma(szTxt);

	s=gobj_location->GetCooldown();
	h=s/3600;
	s=s%3600;
	m=s/60;
	s=s%60;
	_stprintf(szTxt, TEXT("%d/%d - %d:%d:%d"), gobj_location->GetCurrentPoint()
		, gobj_location->GetMaxPoint()
		, h, m, s);
	tab->SetLocation(szTxt);

	s=gobj_dungeon->GetCooldown();
	h=s/3600;
	s=s%3600;
	m=s/60;
	s=s%60;
	_stprintf(szTxt, TEXT("%d/%d - %d:%d:%d"), gobj_dungeon->GetCurrentPoint()
		, gobj_dungeon->GetMaxPoint()
		, h, m, s);
	tab->SetDungeon(szTxt);

	wsprintf(szTxt, TEXT("%d/%d(Win/Total) - %d(Gold) - %d(Exp) - %d(Hornor)")
		, GameArenaServer::nFightWin
		, GameArenaServer::nFightLose+GameArenaServer::nFightWin
		, GameArenaServer::nGoldTotal
		, GameArenaServer::nExp
		, GameArenaServer::nHornor);
	tab->SetArenaInfo(szTxt);

	wsprintf(szTxt, TEXT("%d/%d(Win/Total) - %d(Gold) - %d(Exp) - %d(Fame)")
		, GameArenaServer::nDFightWin
		, GameArenaServer::nDFightLose+GameArenaServer::nDFightWin
		, GameArenaServer::nDGoldTotal
		, GameArenaServer::nDExp
		, GameArenaServer::nDFame);
	tab->SetDungeonInfo(szTxt);

	//End test
	return;
}

IGameMod *modArena, *modQuest;
BOOL bProcessing=FALSE;

void CALLBACK GotoMod(HWND hWnd, UINT msg, UINT id, DWORD dwTime)
{
	VARIANT_BOOL busy;

	if (gv_wb2->get_Busy(&busy)==S_OK && !busy)
	{
		bProcessing=TRUE;
		if (modArena->Go(gv_wb2))
		{
			KillTimer(hWnd, id);
		}
		bProcessing=FALSE;
	}
}

void mcOnBtnTest(HWND hDlg)
{
	geh_overview->FireEvent();

	return;

	int i, j;
	int cx, cy;
	BOOL bFound;

	gobj_player->Synchronized(gv_wb2);
	gobj_inv->Synchronized(gv_wb2);

	bFound=FALSE;
	for (i=0; i<INV_HEIGHT; i++)
	{
		for (j=0; j<INV_WIDTH; j++)
		{
			if (gobj_inv->m_items[i][j].m_bActive 
				&& gobj_inv->m_items[i][j].m_enType==ITEMTYPE_FOOD
				&& gobj_inv->m_items[i][j].m_bNormalUse
				&& !gobj_inv->m_items[i][j].m_bSpecialUse)
			{
				if (gobj_player->GetHpCurrent()+gobj_inv->m_items[i][j].m_nHeal<gobj_player->GetHpMax())
				{
					cx=i;
					cy=j;
					bFound=TRUE;
					break;
				}
			}
		}
	}
	if (bFound)
	{
		IHTMLDOMNode *nodePlayer;
		IHTMLDocument3 *doc3;
		IHTMLDOMNode *nodeItem;

		doc3=BrowserUtility::GetDocument3(gv_wb2);
		nodePlayer=BrowserUtility::GetDomNodeById(doc3, TEXT("p8_1_1"));
		nodeItem=gobj_inv->GetSlotNode(gv_wb2, cx, cy);

		ActionSimulator::MouseFromTo(nodeItem, 5, 5, nodePlayer, 5, 5);
	}
}


LRESULT CALLBACK mcWndProc2( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	WORD wId, wEvent;

	switch(msg)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		if (wParam==17)
		{
			mcCooldown(NULL);
			mcDisplayValue();
		}
		else if (wParam==18)
			mcCooldownBidItem(NULL);
		break;
	case WM_SIZE:
		if (hWnd==hBrowser1)
		{
			if (hBrowser)
				MoveWindow(hBrowser, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		}
		else if (hWnd==hBrowser2)
		{
			if (hBidItem)
				MoveWindow(hBidItem, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		}
		break;
	case WM_COMMAND:
		wId=LOWORD(wParam);
		wEvent=HIWORD(wParam);

		switch(wId)
		{
		case 19:
			if (wEvent==WEBFN_LOADED)
			{
				if (cbDocumentComplete)
					cbDocumentComplete->ExecuteAll(gv_wb2, NULL);
			}
			break;
		case 20:
			if (wEvent==WEBFN_LOADED)
			{
				if (cbBidGold)
					cbBidGold->ExecuteAll(gv_wb2BidItem, NULL);
			}
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
	/*LRESULT rs;
	AX* ax;

	

	switch(msg) 
	{
	case WM_CREATE: 
		//SetWindowText(hWnd, TEXT("AutoPlay Gladiatus"));
		break;
	case WM_CLOSE: case WM_QUIT:
		ax=(AX*)GetWindowLong(hWnd, GWL_USERDATA);
		if (ax)
		{
			EnableWindow(ax->Site.Parent, TRUE);
			SetFocus(ax->Site.Parent);
		}
		break;

	case WM_TIMER:
		if (wParam==17)
		{
			for (int i=0; i<nListCallbackTimer1s; i++)
			{
				listCallbackTimer1s[i](mc_lpParam[i]);
				mcDisplayValue();
			}
		}
		else if (wParam==88)
		{
			mcCooldownBidItem(NULL);
		}
		break;
	case WM_DESTROY:
		ax=(AX*)GetWindowLong(hWnd, GWL_USERDATA);
		if (ax)
		{
			EnableWindow(ax->Site.Parent, TRUE);
			SetFocus(ax->Site.Parent);
		}
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		break;
	}

	rs=CallWindowProc(AXWndProc, hWnd, msg, wParam, lParam);
	return rs;*/
}

LRESULT CALLBACK mcWndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	LRESULT rs;
	AX* ax;

	rs=CallWindowProc(AXWndProc, hWnd, msg, wParam, lParam);

	switch(msg) 
	{
	case WM_CREATE: 
		//SetWindowText(hWnd, TEXT("AutoPlay Gladiatus"));
		break;
	case WM_QUIT:
		//PostQuitMessage(0);
		/*ax=(AX*)GetWindowLong(hWnd, GWL_USERDATA);
		if (ax)
		{
			EnableWindow(ax->Site.Parent, TRUE);
			SetFocus(ax->Site.Parent);
		}*/
		break;

	case WM_TIMER:
		if (wParam==17)
		{
			for (int i=0; i<nListCallbackTimer1s; i++)
			{
				listCallbackTimer1s[i](mc_lpParam[i]);
				mcDisplayValue();
			}
		}
		else if (wParam==88)
		{
			mcCooldownBidItem(NULL);
		}
		break;
	case WM_DESTROY:
/*
		ax=(AX*)GetWindowLong(hWnd, GWL_USERDATA);
		if (ax)
		{
			EnableWindow(ax->Site.Parent, TRUE);
			SetFocus(ax->Site.Parent);
		}*/
		PostQuitMessage(0);
		return 0;
	case WM_COMMAND:
		break;
	}

	return rs;
}

void mcOnChkShowBrowser(HWND hDlg)
{
	if (SendMessage(GetDlgItem(hDlg, IDC_CHKSHOWBROWSER), BM_GETCHECK, 0, 0)==BST_CHECKED)
	{
		ShowWindow(hBrowser, SW_SHOW);
	}
	else
	{
		ShowWindow(hBrowser, SW_HIDE);
	}
}


DWORD WINAPI mcThreadTimer(LPARAM lpParam)
{
	DWORD dwLastTime;
	DWORD dwNowTime;
	int i;

	dwLastTime=GetTickCount();
	while (1)
	{
		Sleep(200);

		dwNowTime=GetTickCount();
		if (dwNowTime-dwLastTime>=1000)
		{
			dwLastTime=dwNowTime;

			for (i=0; i<nListCallbackTimer1s; i++)
			{
				listCallbackTimer1s[i](mc_lpParam[i]);
				mcDisplayValue();
			}
		}
	}

	return 0;
}

void FindPosition(IHTMLElement *elm, long *left, long *top)
{
	long cl, ct;
	IHTMLElement *parent, *tmp;

	*left=0;
	*top=0;

	elm->get_offsetLeft(left);
	elm->get_offsetTop(top);

	elm->get_offsetParent(&parent);
	while (parent)
	{
		parent->get_offsetLeft(&cl);
		parent->get_offsetTop(&ct);
		*left=*left+cl;
		*top=*top+ct;

		parent->get_offsetParent(&tmp);
		parent->Release();
		parent=tmp;
	}
}

void mcOnChkAutoArena(HWND hDlg)
{
	if (geh_arena)
		geh_arena->SetAutoHandler(SendMessage(GetDlgItem(hDlg, IDC_CHKAUTOARENA), BM_GETCHECK, 0, 0)==BST_CHECKED);
}

void mcOnChkAutoLocation(HWND hDlg)
{
	if (geh_loc)
		geh_loc->SetAutoHandler(SendMessage(GetDlgItem(hDlg, IDC_CHKAUTOLOCATION), BM_GETCHECK, 0, 0)==BST_CHECKED);
}

void mcOnChkArenaHp(HWND hDlg)
{
	int nHp;
	BOOL bEnable;
	TCHAR szTxt[100];
	
	bEnable=(SendDlgItemMessage(hDlg, IDC_CHKARENAHP, BM_GETCHECK, NULL, NULL)==BST_CHECKED);
	EnableWindow(GetDlgItem(hDlg, IDC_TXTARENAHP), !bEnable);
	nHp=0;
	if (bEnable)
	{
		GetDlgItemText(hDlg, IDC_TXTARENAHP, szTxt, 100);
		nHp=_wtoi(szTxt);
		if (nHp>gobj_player->GetHpMax())
			nHp=gobj_player->GetHpMax();
	}

	geh_arena->SetHpLow(bEnable, nHp);
}

void mcOnChkAutoTurma(HWND hDlg)
{
	if (geh_turma)
		geh_turma->SetAutoHandler(SendMessage(GetDlgItem(hDlg, IDC_CHKAUTOTURMA), BM_GETCHECK, 0, 0)==BST_CHECKED);
}

DWORD WINAPI mcThreadBidItem(LPARAM lpParam)
{
	CoInitialize(NULL);
	//InitCommonControls();
	//AXRegister();

	hBidItem=CreateWindow(TEXT("AutoGladiatus"), TEXT("{8856F961-340A-11D0-A96B-00C04FD705A2}")
		, WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX|WS_THICKFRAME|WS_VISIBLE
		, 0, 0, 1000, 700
		, NULL
		, NULL
		, NULL
		, NULL);
	DWORD dwErr=GetLastError();

	if (hBidItem)
	{
		SendMessage(hBidItem, AX_INPLACE, 1, 0);
		//SendMessage(hBrowser, AX_ENABLE_MENUCONTEXT, 0, 0);

		//SendMessage(hBidItem, AX_SETCALLBACK_EVENTHANDLER, AX_EVENT_DOCUMENTCOMPLETE, (LPARAM)cbBidGold);
		SendMessage(hBidItem, AX_QUERYINTERFACE, (WPARAM)&IID_IWebBrowser2, (LPARAM)&gv_wb2BidItem);
		


		if (gv_wb2BidItem)
		{
			IUnknown *u1, *u2;
			DWORD dwCookie;

			u1=(IUnknown*)SendMessage(hBidItem, AX_GETAXINTERFACE, 0, 0);
			u1->QueryInterface(IID_IUnknown, (void**)&u2);
			AtlAdvise((IUnknown*)gv_wb2BidItem, u2, DIID_DWebBrowserEvents2, &dwCookie);
			u2->Release();
			u1->Release();

			//geh_market=new GEventHandler_Market(gv_wb2BidItem, newgm, gobj_market, gobj_player);
			eventBidItem=new EventManager();
			eventBidItem->SetEventMarket(geh_market);
			SetTimer(hBidItem, 88, 1000, NULL);
			SetEvent(hEventBidGold);

			//gv_wb2BidItem->Navigate((BSTR)TEXT("s15.en.gladiatus.gameforge.com/game"), 0, 0, 0, 0);
			gv_wb2BidItem->Navigate((BSTR)TEXT("s201.de.gladiatus.gameforge.com/game"), 0, 0, 0, 0);
			//gv_wb2->Navigate((BSTR)TEXT("localhost/test.html"), 0, 0, 0, 0);
			gv_wb2BidItem->put_Silent(TRUE);
		}
	}
	
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	
	return 0;
}

void mcOnChkBidItem(HWND hDlg)
{
	if (geh_market)
		geh_market->SetAutoHandler(SendMessage(GetDlgItem(hDlg, IDC_CHKAUTOBIDITEM), BM_GETCHECK, 0, 0)==BST_CHECKED);
}

void mcOnBtnBuy(HWND hDlg)
{
	int srcx, srcy, desx, desy;
	TCHAR szTmp[50];

	GetDlgItemText(hDlg, IDC_TXTSRCX, szTmp, 50);
	ppParseToNumber(szTmp, NULL, NULL, 1, &srcx);

	GetDlgItemText(hDlg, IDC_TXTSRCY, szTmp, 50);
	ppParseToNumber(szTmp, NULL, NULL, 1, &srcy);

	GetDlgItemText(hDlg, IDC_TXTDESX, szTmp, 50);
	ppParseToNumber(szTmp, NULL, NULL, 1, &desx);

	GetDlgItemText(hDlg, IDC_TXTDESY, szTmp, 50);
	ppParseToNumber(szTmp, NULL, NULL, 1, &desy);

	
	gobj_shopinv->Synchronized(gv_wb2);
	gobj_shopinv->BuyItem(gv_wb2, srcx, srcy, desx, desy);
	MessageBox(hDlg, TEXT("Buy Finished"), TEXT("Notify"), MB_OK);
}

void mcOnBtnSell(HWND hDlg)
{
	int srcx, srcy, desx, desy;
	TCHAR szTmp[50];

	GetDlgItemText(hDlg, IDC_TXTSRCX, szTmp, 50);
	ppParseToNumber(szTmp, NULL, NULL, 1, &srcx);

	GetDlgItemText(hDlg, IDC_TXTSRCY, szTmp, 50);
	ppParseToNumber(szTmp, NULL, NULL, 1, &srcy);

	GetDlgItemText(hDlg, IDC_TXTDESX, szTmp, 50);
	ppParseToNumber(szTmp, NULL, NULL, 1, &desx);

	GetDlgItemText(hDlg, IDC_TXTDESY, szTmp, 50);
	ppParseToNumber(szTmp, NULL, NULL, 1, &desy);


	gobj_shopinv->Synchronized(gv_wb2);
	gobj_shopinv->SellItem(gv_wb2, srcx, srcy, desx, desy);
	MessageBox(hDlg, TEXT("Sell Finished"), TEXT("Notify"), MB_OK);
}

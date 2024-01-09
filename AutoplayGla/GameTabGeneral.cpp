#include "GameTabGeneral.h"
#include <GdiPlus.h>
#include <GdiPlusFlat.h>

GameTabGeneral::GameTabGeneral(HWND hParent)
{
	this->m_ListControl.next=NULL;
	this->m_hParent=hParent;
	this->_InitControls();
}

GameTabGeneral::~GameTabGeneral()
{
	DRAWINFO *info, *next;

	info=this->m_ListControl.next;
	while (info)
	{
		next=info->next;
		DeleteObject(info->hFont);
		DeleteObject(info->hPen);
		DeleteObject(info->bitmap);
		LocalFree(info);
		info=next;
	}
}

void GameTabGeneral::OnDraw( HDC hdc )
{
	DRAWINFO *info;

	info=this->m_ListControl.next;
	while (info)
	{
		this->_DrawControl(hdc, info);

		info=info->next;
	}
}

void GameTabGeneral::_InitControls()
{
	this->m_diGold=this->_CreateControl(TEXT("E:\\MySpace\\Cheat Game\\Gladiatus\\Resource\\icon_gold.gif")
		, NULL, 15, 0, 10, 10);
	this->_AddControl(this->m_diGold);

	this->m_diArenaInfo=this->_CreateControl(NULL
		, NULL, 15, 0, 110, 10);
	this->_AddControl(this->m_diArenaInfo);

	this->m_diRubi=this->_CreateControl(TEXT("E:\\MySpace\\Cheat Game\\Gladiatus\\Resource\\icon_rubies.gif")
		, NULL, 15, 0, 10, 40);
	this->_AddControl(this->m_diRubi);

	this->m_diDungeonInfo=this->_CreateControl(NULL
		, NULL, 15, 0, 110, 40);
	this->_AddControl(this->m_diDungeonInfo);

	this->m_diLevel=this->_CreateControl(TEXT("E:\\MySpace\\Cheat Game\\Gladiatus\\Resource\\icon_level.gif")
		, NULL, 15, 0, 10, 70);
	this->_AddControl(this->m_diLevel);

	this->m_diQuest=this->_CreateControl(NULL
		, NULL, 15, 0, 110, 70);
	this->_AddControl(this->m_diQuest);

	this->m_diRank=this->_CreateControl(TEXT("E:\\MySpace\\Cheat Game\\Gladiatus\\Resource\\icon_highscore.gif")
		, NULL, 15, 0, 10, 100);
	this->_AddControl(this->m_diRank);

	this->m_diLocation=this->_CreateControl(TEXT("E:\\MySpace\\Cheat Game\\Gladiatus\\Resource\\icon_expeditionpoints.gif")
		, NULL, 15, 0, 110, 100);
	this->_AddControl(this->m_diLocation);


	this->m_diArena=this->_CreateControl(TEXT("E:\\MySpace\\Cheat Game\\Gladiatus\\Resource\\icon_arena.gif")
		, NULL, 15, 0, 10, 130);
	this->_AddControl(this->m_diArena);

	this->m_diDungeon=this->_CreateControl(TEXT("E:\\MySpace\\Cheat Game\\Gladiatus\\Resource\\icon_dungeonpoints.gif")
		, NULL, 15, 0, 110, 130);
	this->_AddControl(this->m_diDungeon);

	this->m_diTurma=this->_CreateControl(TEXT("E:\\MySpace\\Cheat Game\\Gladiatus\\Resource\\icon_grouparena.gif")
		, NULL, 15, 0, 10, 160);
	this->_AddControl(this->m_diTurma);

	this->m_diHp=this->_CreateControl(NULL
		, NULL, 15, 0, 10, 190);
	this->_AddControl(this->m_diHp);

	this->m_diExp=this->_CreateControl(NULL
		, NULL, 15, 0, 10, 220);
	this->_AddControl(this->m_diExp);
}

DRAWINFO* GameTabGeneral::_CreateControl( TCHAR *lpszImgPath, TCHAR *lpszText, int nSize, COLORREF color, int left, int top )
{
	DRAWINFO *info;

	info=(DRAWINFO*)LocalAlloc(LMEM_FIXED, sizeof(DRAWINFO));
	info->hPen=CreatePen(PS_SOLID, 1, color);
	info->lpszText=lpszText;
	info->next=NULL;
	info->hFont=CreateFont(nSize,0,0,0,FW_REGULAR,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS
		,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Arial"));
	info->bCalcRect=FALSE;
	info->pPos.x=left;
	info->pPos.y=top;
	info->color=color;
	info->lpszImgFile=lpszImgPath;
	info->bitmap=GameTabGeneral::_CreateGradienBrush(info);
	
	HDC hdc;
	hdc=GetDC(this->m_hParent);
	info->bCalcRect=FALSE;
	this->_Recalc(hdc, info);
	ReleaseDC(this->m_hParent, hdc);

	return info;
}

void GameTabGeneral::_AddControl( DRAWINFO *info )
{
	DRAWINFO *last;
	last=&this->m_ListControl;
	while (last->next)
	{
		last=last->next;
	}
	last->next=info;
	last->next->next=NULL;

	RECT rc;
	rc.left=info->pPos.x;
	rc.top=info->pPos.y;
	rc.right=rc.left+info->sizeBoundary.cx;
	rc.bottom=rc.top+info->sizeBoundary.cy;
	//InvalidateRect(this->m_hParent, &rc, TRUE);
	SendMessage(this->m_hParent, WM_USER+17, (WPARAM)&rc, NULL);
}

void GameTabGeneral::_DrawControl( HDC hdc, DRAWINFO *info )
{
	RECT rc;

	if (info->lpszText)
	{
 		if (!info->bCalcRect)
		{
// 			info->bCalcRect=TRUE;
// 			GetTextExtentPoint32(hdc, info->lpszText, wcslen(info->lpszText), &info->size);
// 			info->sizeBoundary.cy=(info->size.cy>info->sizeImg.cy?info->size.cy:info->sizeImg.cy);
// 			info->sizeBoundary.cx=info->sizeImg.cx+info->size.cx+5;
// 			this->_Recalc(hdc, info);
// 			info->bCalcRect=TRUE;
		}

		rc.left=info->pPos.x+info->sizeImg.cx+5;
		rc.right=rc.left+info->size.cx;
		rc.top=info->pPos.y+info->sizeBoundary.cy/2-info->size.cy/2;
		rc.bottom=rc.top+info->size.cy;

		SelectObject(hdc, info->hFont);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, info->color);
		DrawText(hdc, info->lpszText, -1, &rc, DT_LEFT);
	}
	
	if (info->bitmap)
	{
		rc.top=info->pPos.y+info->sizeBoundary.cy/2-info->sizeImg.cy/2;
		rc.left=info->pPos.x;
		rc.right=rc.left+info->sizeImg.cx;
		rc.bottom=rc.top+info->sizeImg.cy;
		
		HDC hdcMem;
		hdcMem=CreateCompatibleDC(hdc);
		SelectObject(hdcMem, info->bitmap);
		//BitBlt(hdc, rc.left, rc.top, info->sizeImg.cx, info->sizeImg.cy, hdcMem, 0, 0, SRCCOPY);
		TransparentBlt(hdc, rc.left, rc.top, info->sizeImg.cx, info->sizeImg.cy, hdcMem, 0, 0, info->sizeImg.cx, info->sizeImg.cy, RGB(255, 255, 255));
		DeleteDC(hdcMem);
	}
}

HBITMAP GameTabGeneral::_CreateGradienBrush( DRAWINFO *info )
{
	Gdiplus::Bitmap *bitmap=NULL;
	HBRUSH hBrush;
	HBITMAP hBitmap;

	info->sizeImg.cx=0;
	info->sizeImg.cy=0;

	if (info->lpszImgFile==NULL)
		return NULL;

	hBrush=NULL;
	bitmap=new Gdiplus::Bitmap(info->lpszImgFile, false);
	
	bitmap->GetLastStatus();
	if (bitmap!=NULL)
	{
		bitmap->GetHBITMAP(Gdiplus::Color::Transparent, &hBitmap);

		info->sizeImg.cy=bitmap->GetHeight();
		info->sizeImg.cx=bitmap->GetWidth();

		delete bitmap;
	}
	return hBitmap;
}

void GameTabGeneral::_SetText( DRAWINFO *info, TCHAR *lpszText )
{
	int len;

	if (lpszText && info->lpszText)
	{
		if (wcscmp(lpszText, info->lpszText)==0)
			return;
	}

	LocalFree(info->lpszText);
	info->lpszText=NULL;

	info->bCalcRect=FALSE;
	if (lpszText)
	{
		len=wcslen(lpszText);
		info->lpszText=(TCHAR*)LocalAlloc(LMEM_FIXED, (len+1)*sizeof(TCHAR));
		CopyMemory(info->lpszText, lpszText, (len+1)*sizeof(TCHAR));
	}

	RECT rc;
// 	rc.left=info->pPos.x+info->sizeImg.cx+5;
// 	rc.top=info->pPos.y;
// 	rc.bottom=rc.top+info->sizeBoundary.cy;
// 	rc.right=rc.left+info->sizeImg.cx+info->size.cx;
// 
// 	SendMessage(this->m_hParent, WM_USER+17, (WPARAM)&rc, NULL);

	HDC hdc;
	hdc=GetDC(this->m_hParent);
	this->_Recalc(hdc, info);
	ReleaseDC(this->m_hParent, hdc);

	rc.left=info->pPos.x+info->sizeImg.cx+5;
	rc.top=info->pPos.y;
	rc.bottom=rc.top+info->sizeBoundary.cy;
	rc.right=rc.left+info->sizeImg.cx+info->size.cx;

	SendMessage(this->m_hParent, WM_USER+17, (WPARAM)&rc, NULL);

}

void GameTabGeneral::SetGold( TCHAR *lpszText )
{
	this->_SetText(this->m_diGold,lpszText);
}

void GameTabGeneral::_Recalc( HDC hdc, DRAWINFO *info )
{
	if (!info->bCalcRect)
	{
		info->bCalcRect=TRUE;
		if (info->lpszText)
			GetTextExtentPoint32(hdc, info->lpszText, wcslen(info->lpszText), &info->size);
		else
		{
			info->size.cx=0;
			info->size.cy=0;
		}
		info->sizeBoundary.cy=(info->size.cy>info->sizeImg.cy?info->size.cy:info->sizeImg.cy);
		info->sizeBoundary.cx=info->sizeImg.cx+5+info->size.cx;
	}
}

void GameTabGeneral::SetLevel( TCHAR *lpszLevel )
{
	this->_SetText(this->m_diLevel, lpszLevel);
}

void GameTabGeneral::SetRubi( TCHAR *lpszText )
{
	this->_SetText(this->m_diRubi, lpszText);
}

void GameTabGeneral::SetRank( TCHAR *lpszRank )
{
	this->_SetText(this->m_diRank, lpszRank);
}

void GameTabGeneral::SetArena( TCHAR *lpszText )
{
	this->_SetText(this->m_diArena, lpszText);
}

void GameTabGeneral::SetTurma( TCHAR *lpszText )
{
	this->_SetText(this->m_diTurma, lpszText);
}

void GameTabGeneral::SetHp( TCHAR *lpszText )
{
	this->_SetText(this->m_diHp, lpszText);
}

void GameTabGeneral::SetLocation( TCHAR *lpszText )
{
	this->_SetText(this->m_diLocation, lpszText);
}

void GameTabGeneral::SetDungeon( TCHAR *lpszText )
{
	this->_SetText(this->m_diDungeon, lpszText);
}

void GameTabGeneral::SetExp( TCHAR *lpszExp )
{
	this->_SetText(this->m_diExp, lpszExp);
}

void GameTabGeneral::SetQuest( TCHAR *lpszQuest )
{
	this->_SetText(this->m_diQuest, lpszQuest);
}

void GameTabGeneral::SetArenaInfo( TCHAR *lpszArenaInfo )
{
	this->_SetText(this->m_diArenaInfo, lpszArenaInfo);
}

void GameTabGeneral::SetDungeonInfo( TCHAR *lpszDungeonInfo )
{
	this->_SetText(this->m_diDungeonInfo, lpszDungeonInfo);
}

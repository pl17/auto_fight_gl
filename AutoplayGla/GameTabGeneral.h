#pragma once

#define _WIN32_WINNT 0x0501
#include <Windows.h>

typedef struct _DRAWINFO
{
	POINT pPos;
	SIZE size;
	TCHAR *lpszText;
	HFONT hFont;
	HPEN hPen;
	BOOL bCalcRect;
	COLORREF color;
	HBITMAP bitmap;
	SIZE sizeImg;
	TCHAR *lpszImgFile;
	SIZE sizeBoundary;

	struct _DRAWINFO *next;
} DRAWINFO;

class GameTabGeneral
{
public:
	GameTabGeneral(HWND hParent);
	~GameTabGeneral();

	void OnDraw(HDC hdc);
	void SetGold(TCHAR *lpszText);
	void SetRubi(TCHAR *lpszText);
	void SetLevel(TCHAR *lpszLevel);
	void SetRank(TCHAR *lpszRank);
	void SetArena(TCHAR *lpszText);
	void SetTurma(TCHAR *lpszText);
	void SetHp(TCHAR *lpszText);
	void SetLocation(TCHAR *lpszText);
	void SetDungeon(TCHAR *lpszText);
	void SetExp(TCHAR *lpszExp);
	void SetQuest(TCHAR *lpszQuest);
	void SetArenaInfo(TCHAR *lpszArenaInfo);
	void SetDungeonInfo(TCHAR *lpszDungeonInfo);
private:
	void _InitControls();
	DRAWINFO* _CreateControl(TCHAR *lpszImgPath, TCHAR *lpszText, int nSize, COLORREF color, int left, int top);
	void _AddControl(DRAWINFO *info);
	void _DrawControl(HDC hdc, DRAWINFO *info);
	void _SetText(DRAWINFO *info, TCHAR *lpszText);
	void _Recalc(HDC hdc, DRAWINFO *info);

	static HBITMAP _CreateGradienBrush( DRAWINFO *info );

	DRAWINFO m_ListControl;
	DRAWINFO *m_diGold;
	DRAWINFO *m_diRubi;
	DRAWINFO *m_diLevel;
	DRAWINFO *m_diRank;
	DRAWINFO *m_diArena;
	DRAWINFO *m_diTurma;
	DRAWINFO *m_diHp;
	DRAWINFO *m_diLocation;
	DRAWINFO *m_diDungeon;
	DRAWINFO *m_diQuest;
	DRAWINFO *m_diExp;
	DRAWINFO *m_diArenaInfo;
	DRAWINFO *m_diDungeonInfo;
	HWND m_hParent;
};
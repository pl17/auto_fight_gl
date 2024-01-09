#ifndef _GAMELINK_H
#define _GAMELINK_H

#include <ExDisp.h>

//game mod
#define GAMELINK_MOD_UNKNOWN	0
#define GAMELINK_MOD_QUEST		1
#define GAMELINK_MOD_ARENA		2
#define GAMELINK_MOD_REPORT		3
#define GAMELINK_MOD_HIGHSCORE	4
#define GAMELINK_MOD_PLAYER		5
#define GAMELINK_MOD_GUILD		6
#define GAMELINK_MOD_PREMIUM	7
#define GAMELINK_MOD_OVERVIEW	8
#define GAMELINK_MOD_LOCATION	9
#define GAMELINK_MOD_DUNGEON	10
#define GAMELINK_MOD_TURMA		11
#define GAMELINK_MOD_MARKET		12
#define GAMELINK_MOD_ARENASERVER	13
#define GAMELINK_MOD_TURMASERVER	14

#define GAMELINK_MOD_NOTFOUND	-1

//game submod
#define GAMELINK_SUBMOD_UNKNOWN		0


typedef struct _GL_SUBMOD
{
	const int nModId;
	const int nSubmodId;

	const TCHAR **lpcszSubmodList;
} GL_SUBMOD;

typedef struct _GL_MOD
{
	const int nModId;
	const TCHAR *lpszModName;
}GL_MOD;


class GameLink
{
public:
	GameLink(IWebBrowser2 *wb2);
	~GameLink();

	void UpdateValue();
	void SetIWeb(IWebBrowser2 *wb2);
	int GetModId();
	BOOL ParseQuery(const TCHAR *szKey, TCHAR *szValue, int nsize);
protected:
	int m_nMod;
	int m_nSubmod;
	BSTR m_bsUrl;
	IWebBrowser2 *m_wb2;

	BOOL _UpdateURL();
	int _UpdateMod();
	int _ParseSubmod();
	
	BOOL _ParseQuery(const TCHAR *szKey, TCHAR *szValue, int nsize);

	static const GL_MOD m_ListMod[];
	static const int m_nListMod;
	static const TCHAR* _FindModName(int nId);
	static const int _FindModId(const TCHAR *szModName);

	static BOOL _IsEqualIgnoreCase(const TCHAR *src, const TCHAR *des, int nsize);
	static const TCHAR* _FindSubString(const TCHAR *src, const TCHAR *des, int nsize);
};

#endif

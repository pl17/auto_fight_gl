#include <ExDisp.h>
#include <MsHTML.h>

#define GAMEARENA_MAXPLAYER	5

#include "ArenaPlayer.h"

class GameArenaServer
{
public:
	GameArenaServer(IWebBrowser2 *wb2);
	~GameArenaServer();

	void UpdateValue();
	ARENA_PLAYER* GetListArenaPlayer();
	BOOL AttackPlayer(int index);
	BOOL AttackPlayerMinLevel(int nFirstIndex);
	int GetIndexPlayerMinLevel(int nFirstIndex);
	static BOOL CheckBash(IWebBrowser2 *wb2);
	static BOOL CheckFightReport(IWebBrowser2 *wb2, BOOL *lpbWin);
	static BOOL GetFightWinInfo(IWebBrowser2 *wb2, int nType, int *lpnGoldTotal, int *lpnGoldBase, int *lpnExp, int *lpnHonor);

	static int nFightWin, nFightLose, nGoldTotal, nGoldBase, nHornor, nExp;
	static int nDFightWin, nDFightLose, nDGoldTotal, nDGoldBase, nDExp, nDFame;
protected:
	IWebBrowser2 *m_wb2;
	ARENA_PLAYER m_listPlayer[GAMEARENA_MAXPLAYER];
	BOOL m_bListPlayer;
	int m_listIndexPlayer[GAMEARENA_MAXPLAYER];

	BOOL _GetListPlayer();
	void _SortListPlayer();
	IHTMLDOMNode* _GetNodeList(IHTMLDocument3 *doc3);
};
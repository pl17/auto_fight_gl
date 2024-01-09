#pragma once

#include <ExDisp.h>
#include <MsHTML.h>
#include "GameObject_Base.h"

enum QUESTTYPE
{
	QUESTTYPE_ARENA,
	QUESTTYPE_TURMA,
	QUESTTYPE_EXPEDITION,
	QUESTTYPE_COMBAT,
	QUESTTYPE_DUNGEON,
	QUESTTYPE_UNKNOWN
};

enum QUESTSTATUS
{
	QUESTSTATUS_SUCCESS,
	QUESTSTATUS_RESTART,
	QUESTSTATUS_PROCESSING,
	QUESTSTATUS_NA,
	QUESTSTATUS_FREE
};

typedef struct _GAMEQUEST_INFO
{
	QUESTTYPE nType;
	int nBattleNow;
	int nBattleMax;
	int nCoolDown;
	int bCoolDown;
	QUESTSTATUS enStatus;
	int bIsActive;

} GAMEQUEST_INFO;

#define GAMEQUEST_MAX_LIST	10

class GameQuest :
	public GameObject_Base
{
public:
	GameQuest();
	GAMEQUEST_INFO m_listQuest[GAMEQUEST_MAX_LIST];

	void Synchronized( IWebBrowser2 *wb2 );
	GAMEQUEST_INFO* GetListQuest();
	BOOL RefreshQuest();
	BOOL RestartQuest(int nIndex);
	BOOL FinishQuest(int nIndex);
	BOOL StartQuest(int nIndex);
	int FindFightQuest();
	BOOL CanAction();
	BOOL DoAction();
	BOOL IsInited();
	void SetInited(BOOL bInit);
	void IncQuestArena();
	void IncQuestTurma();
	void IncQuestCombat();
	BOOL HasQuestFinished();
	int GetCooldown();
	void SetCooldown(int nCooldown);
	BOOL CanStartQuest();
private:
	void _IncQuest(QUESTTYPE type);
	void _GetListQuest();
	void _GetQuestType(IHTMLDOMNode *parent, int nIndex);
	void _GetQuestStatus(IHTMLDOMNode *parent, int nindex);
	void _GetBattleCount(IHTMLDOMNode *parent, int nIndex);
	void _GetQuestCooldown(IHTMLDOMNode *parent, int nIndex);
	void _GetCooldown(IHTMLDOMNode *parent);
	void _GetQuestAcceptInfo(IHTMLDOMNode *parent);
	BOOL _IsQuestAcceptArea(IHTMLElement *elm);
	void _GetReward(IHTMLDOMNode *parent, int nIndex);
	BOOL _IsQuestArea(IHTMLDOMNode *node);

	void _GetQuestHeader(IHTMLDOMNode *parent);
	BOOL _IsQuestHeaderArea(IHTMLDOMNode *node);

	IHTMLDOMNode* _GetQuestRoot();
	IHTMLDOMNode* _GetQuestNode(int nIndex);
	IHTMLDOMNode* _GetQuestButtonNode(int nIndex);
	
	BOOL _ActionQuestButton(int nIndex, QUESTSTATUS status);
	BOOL _IsFightQuest(int nIndex);

	IWebBrowser2 *m_wb2;
	int m_nListQuest;
	int m_nMaxRecvQuest;
	int m_nCurRecvQuest;
	BOOL m_bInit;
};
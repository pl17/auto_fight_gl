#pragma once

#include "GameObject_Base.h"
#include "QuestObject.h"

#define QUEST_MAXQUEST	20

class GQuestObject_Quest :
	public GameObject_Base
{
public:
	GQuestObject_Quest();
	~GQuestObject_Quest();

	//Implement virtual method
	void Synchronized( IWebBrowser2 *wb2 );

	//Event thorugh objects
	void OnArenaFinish(BOOL bWin);
	void OnTurmaFinish(BOOL bWin);
	void OnExpeditionFinish(BOOL bWin);

	//Local method
	BOOL RefrestQuest(IWebBrowser2 *wb2);
	BOOL ActionQuest(IWebBrowser2 *wb2, int nIndex);
	BOOL CanAction();
	BOOL TryAction(IWebBrowser2 *wb2);
	int FindQuest();
	BOOL HasQuestFinish();
	BOOL IsInited();

private:
	QuestObject *m_quests;
	int m_nCurrentRecvQuest;
	int m_nMaxRecvQuest;
	int m_nTotalQuest;
	BOOL m_bInited;

	BOOL _IsQuestHeaderArea(IHTMLDOMNode *node);
	void _SynchronizedQuestList(IHTMLDOMNode *rootQuest);
	void _SynchronizedQuestHeader(IHTMLDOMNode *rootQuest);
	void _SynchronizedQuest(IWebBrowser2 *wb2);

	void _ParseQuestHeaderCooldown(IHTMLDOMNode *rootQuest);
	void _ParseQuestHeaderCountInfo(IHTMLDOMNode *rootQuest);

	BOOL _ActionQuest(IWebBrowser2 *wb2, int nIndex);
	IHTMLDOMNode* _GetQuestButtonNode(IHTMLDocument3 *doc3, int nIndex);
	IHTMLDOMNode* _GetQuestNode(IHTMLDocument3 *doc3, int nIndex);
	IHTMLDOMNode* _GetQuestListRoot(IHTMLDocument3 *doc3);
};
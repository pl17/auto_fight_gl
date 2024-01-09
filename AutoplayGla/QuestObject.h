#pragma once

#include <Windows.h>
#include <ExDisp.h>
#include <MsHTML.h>

//Type enum
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
	QUESTSTATUS_FREE,
	QUESTSTATUS_UNKNOWN
};

enum QUESTTARGET
{
	QUESTTARGET_ARENA,
	QUESTTARGET_TURMA,
	QUESTTARGET_COMBAT,
	QUESTTARGET_EXPEDITION_0,
	QUESTTARGET_EXPEDITION_1,
	QUESTTARGET_EXPEDITION_2,
	QUESTTARGET_EXPEDITION_3,
	QUESTTARGET_EXPEDITION_ALL,
	QUESTTARGET_EXPEDITION_EACH,
	QUESTTARGET_UNKNOWN
};

class QuestObject
{
public:
	QuestObject();

	//Public method
	BOOL Synchronized(IHTMLDOMNode *node);
	QUESTSTATUS GetQuestStatus();
	void SetRestartStatus();
	QUESTTYPE GetQuestType();
	BOOL IsActive();
	int GetCurrentBattle();
	int GetMaxBattle();
	void IncBattleCount();
	BOOL IsFinished();
	BOOL IsFightQuest();
	BOOL IsInSuccessionQuest();

private:
	QUESTTYPE m_enType;
	QUESTSTATUS m_enStatus;
	QUESTTARGET m_enTarget;

	int m_nBattleNow;
	int m_nBattleMax;
	int m_nCooldown;
	BOOL m_bCooldown;
	BOOL m_bActive;
	BOOL m_bInSuccession;

	BOOL _IsQuestArea(IHTMLDOMNode *node);
	void _ParseQuestStatus(IHTMLDOMNode *node);
	void _ParseQuestTypeAndActive(IHTMLDOMNode *node);
	void _ParseQuestTarget(IHTMLDOMNode *node);
	void _ParseQuestBattleCount(IHTMLDOMNode *node);
	void _ParseQuestContent(IHTMLDOMNode *node);
	void _ParseQuestContent(BSTR str);
	void _ParseInSuccession(BSTR str);
};
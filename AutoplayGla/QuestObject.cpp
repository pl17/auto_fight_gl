#include "QuestObject.h"
#include "BrowserUtility.h"
#include "PParser.h"
#include "PXPath.h"

QuestObject::QuestObject()
{
	this->m_enStatus=QUESTSTATUS_UNKNOWN;
	this->m_enTarget=QUESTTARGET_UNKNOWN;
	this->m_enType=QUESTTYPE_UNKNOWN;
	this->m_bActive=FALSE;
	this->m_bCooldown=FALSE;
	this->m_nCooldown=0;
	this->m_nBattleMax=0;
	this->m_nBattleNow=0;
	this->m_bInSuccession=FALSE;
}


BOOL QuestObject::Synchronized( IHTMLDOMNode *node )
{
	BOOL brs;

	brs=FALSE;

	if (node)
	{
		//node->Release();
		if (this->_IsQuestArea(node))
		{
			brs=TRUE;
			this->_ParseQuestBattleCount(node);
			this->_ParseQuestStatus(node);
			this->_ParseQuestTarget(node);
			this->_ParseQuestTypeAndActive(node);
			this->_ParseQuestContent(node);
		}
	}

	return brs;
}

BOOL QuestObject::_IsQuestArea( IHTMLDOMNode *node )
{
	return BrowserUtility::IsClass(node, TEXT("contentboard_slot"));
}

void QuestObject::_ParseQuestStatus( IHTMLDOMNode *node )
{
	IHTMLDOMNode *nodeButton;
	BSTR str;

	this->m_enStatus=QUESTSTATUS_UNKNOWN;
	if (node)
	{
		nodeButton=pxpGetXPathNode(node, TEXT("a"));
		if (nodeButton)
		{
			BrowserUtility::GetClass(nodeButton, &str);
			if (str)
			{
				if (ppIsContainIgnoreCase(str, TEXT("quest_slot_button_cancel"), -1))
				{
					this->m_enStatus=QUESTSTATUS_PROCESSING;
				}
				else if (ppIsContainIgnoreCase(str, TEXT("quest_slot_button_finish"), -1))
				{
					this->m_enStatus=QUESTSTATUS_SUCCESS;
				}
				else if (ppIsContainIgnoreCase(str, TEXT("quest_slot_button_accept"), -1))
				{
					this->m_enStatus=QUESTSTATUS_FREE;
				}
				else if (ppIsContainIgnoreCase(str, TEXT("quest_slot_button_restart"), -1))
				{
					this->m_enStatus=QUESTSTATUS_RESTART;
				}

				SysFreeString(str);
			}

			nodeButton->Release();
		}
		else//Tag a not found
		{
			this->m_enStatus=QUESTSTATUS_NA;
		}
	}
}

void QuestObject::_ParseQuestTypeAndActive( IHTMLDOMNode *node )
{
	IHTMLDOMNode *nodeIcon;
	BSTR str;


	this->m_enType=QUESTTYPE_UNKNOWN;
	this->m_bActive=FALSE;
	if (node)
	{
		nodeIcon=pxpGetXPathNode(node, TEXT("div"));
		if (nodeIcon)
		{
			BrowserUtility::GetBkImage(nodeIcon, &str);
			if (str)
			{
				//Check quest type
				if (ppIsContainIgnoreCase(str, TEXT("icon_expedition"), -1))
				{
					this->m_enType=QUESTTYPE_EXPEDITION;
				}
				else if (ppIsContainIgnoreCase(str, TEXT("icon_grouparena"), -1))
				{
					this->m_enType=QUESTTYPE_TURMA;
				}
				else if (ppIsContainIgnoreCase(str, TEXT("icon_arena"), -1))
				{
					this->m_enType=QUESTTYPE_ARENA;
				}
				else if (ppIsContainIgnoreCase(str, TEXT("icon_dungeon"), -1))
				{
					this->m_enType=QUESTTYPE_DUNGEON;
				}
				else if (ppIsContainIgnoreCase(str, TEXT("icon_combat"), -1))
				{
					this->m_enType=QUESTTYPE_COMBAT;
				}

				//Check quest active
				if (ppIsContainIgnoreCase(str, TEXT("inactive"), -1))
				{
					this->m_bActive=FALSE;
				}
				else
				{
					this->m_bActive=TRUE;
				}

				SysFreeString(str);
			}

			nodeIcon->Release();
		}
	}
}

void QuestObject::_ParseQuestTarget( IHTMLDOMNode *node )
{
	this->m_enTarget=QUESTTARGET_UNKNOWN;
}

void QuestObject::_ParseQuestBattleCount( IHTMLDOMNode *node )
{
	BSTR str;
	IHTMLDOMNode *child;

	this->m_nBattleMax=0;
	this->m_nBattleNow=0;

	if (node)
	{
		child=pxpGetXPathNode(node, TEXT("div[4]"));
		if (child)
		{
			BrowserUtility::GetNodeInnerText(child, &str);
			if (str)
			{
				ppParseToNumber((TCHAR*)str, TEXT("/"), NULL, 2, &this->m_nBattleNow, &this->m_nBattleMax);

				SysFreeString(str);
			}

			child->Release();
		}
	}
}

QUESTSTATUS QuestObject::GetQuestStatus()
{
	return this->m_enStatus;
}

QUESTTYPE QuestObject::GetQuestType()
{
	return this->m_enType;
}

BOOL QuestObject::IsActive()
{
	return this->m_bActive;
}

int QuestObject::GetCurrentBattle()
{
	return this->m_nBattleNow;
}

int QuestObject::GetMaxBattle()
{
	return this->m_nBattleMax;
}

void QuestObject::IncBattleCount()
{
	if (this->m_nBattleNow<this->m_nBattleMax)
		this->m_nBattleNow++;
}

BOOL QuestObject::IsFinished()
{
	return (this->m_nBattleMax==this->m_nBattleNow);
}

BOOL QuestObject::IsFightQuest()
{
	if (this->m_enType==QUESTTYPE_ARENA
		|| this->m_enType==QUESTTYPE_TURMA
		|| this->m_enType==QUESTTYPE_COMBAT)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL QuestObject::IsInSuccessionQuest()
{
	return this->m_bInSuccession;
}

void QuestObject::_ParseQuestContent( IHTMLDOMNode *node )
{
	IHTMLDOMNode *child;
	BSTR strContent;

	child=pxpGetXPathNode(node, TEXT("div[2]"));
	if (child)
	{
		if (BrowserUtility::IsClass(child, TEXT("quest_slot_title")))
		{
			BrowserUtility::GetNodeInnerText(child, &strContent);
			if (strContent)
			{
				this->_ParseQuestContent(strContent);

				SysFreeString(strContent);
			}
		}

		child->Release();
	}
}

void QuestObject::_ParseQuestContent( BSTR str )
{
	if (str)
	{
		this->_ParseInSuccession(str);
	}
}

void QuestObject::_ParseInSuccession( BSTR str )
{
#ifdef _LANG_GERMANY
	if (ppIsContainIgnoreCase(str, TEXT("folge"), -1))//Parse in success
#else
	if (ppIsContainIgnoreCase(str, TEXT("succession"), -1))//Parse in success
#endif
	{
		this->m_bInSuccession=TRUE;
	}
	else
		this->m_bInSuccession=FALSE;
}

void QuestObject::SetRestartStatus()
{
	this->m_enStatus=QUESTSTATUS_RESTART;
}


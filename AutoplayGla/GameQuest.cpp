#include "GameQuest.h"
#include "GameObj_XPathConst.h"
#include "PXPath.h"
#include "PParser.h"
#include "PSimulator.h"
#include "BrowserUtility.h"
#include "GameManager.h"

#include "Logs.h"

extern IOutputDebug *gv_dbgConsole;

GameQuest::GameQuest()
{
	this->m_nListQuest=0;
	this->m_nCooldown=0;
	this->m_bInit=FALSE;
	this->m_wb2=NULL;

	//this->Synchronize();
}

void GameQuest::Synchronized(IWebBrowser2 *wb2)
{
	GameManager *gm;

	gm=new GameManager(wb2);
	if (gm->GetModId(wb2)==GAMELINK_MOD_QUEST)
	{
		this->m_bInit=TRUE;
		this->m_wb2=wb2;
		this->_GetListQuest();
	}
}

GAMEQUEST_INFO* GameQuest::GetListQuest()
{
	return NULL;
}

void GameQuest::_GetListQuest()
{
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *rootNode, *node;
	TCHAR szTmp[100];
	IHTMLElement *elm;
	IHTMLStyle *style;
	BSTR str;
	int nIndex;


	doc3=BrowserUtility::GetDocument3(this->m_wb2);

	if (doc3)
	{
		rootNode=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_LISTQUEST);
		if (rootNode)
		{
			//Process quest header
			this->_GetQuestHeader(rootNode);


			this->m_nListQuest=0;
			nIndex=1;
			do
			{
				nIndex++;
				wsprintf(szTmp, TEXT("div[%d]"), nIndex);//Icon quest
				node=pxpGetXPathNode(rootNode, szTmp);

				if (this->_IsQuestArea(node))
				{
					this->_GetQuestType(node, this->m_nListQuest);
					this->_GetQuestStatus(node, this->m_nListQuest);
					this->_GetBattleCount(node, this->m_nListQuest);
					this->m_nListQuest++;
					
					node->Release();
				}
				else break;

			} while (1);

			rootNode->Release();
		}

		doc3->Release();
	}
}

void GameQuest::_GetQuestType( IHTMLDOMNode *parent, int nIndex )
{
	TCHAR szTmp[100];
	IHTMLElement *elm;
	IHTMLStyle *style;
	IHTMLDOMNode *node;
	BSTR str;

	wsprintf(szTmp, TEXT("div"));
	node=pxpGetXPathNode(parent, szTmp);
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_style(&style);
			if (style)
			{
				style->get_backgroundImage(&str);
				if (str)
				{
					if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("icon_expedition"), -1))
					{
						this->m_listQuest[nIndex].nType=QUESTTYPE_EXPEDITION;
					}
					else if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("icon_grouparena"), -1))
					{
						this->m_listQuest[nIndex].nType=QUESTTYPE_TURMA;
					}
					else if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("icon_arena"), -1))
					{
						this->m_listQuest[nIndex].nType=QUESTTYPE_ARENA;
					}
					else if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("icon_dungeon"), -1))
					{
						this->m_listQuest[nIndex].nType=QUESTTYPE_DUNGEON;
					}
					else if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("icon_combat"), -1))
					{
						this->m_listQuest[nIndex].nType=QUESTTYPE_COMBAT;
					}
					else
					{
						this->m_listQuest[nIndex].nType=QUESTTYPE_UNKNOWN;
					}

					//Check active
					if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("inactive"), -1))
					{
						this->m_listQuest[nIndex].bIsActive=FALSE;
					}
					else
						this->m_listQuest[nIndex].bIsActive=TRUE;

					SysFreeString(str);
				}

				style->Release();
			}

			elm->Release();
		}

		node->Release();
	}
}

void GameQuest::_GetQuestStatus( IHTMLDOMNode *parent, int nIndex )
{
	TCHAR szTmp[100];
	IHTMLElement *elm;
	IHTMLStyle *style;
	IHTMLDOMNode *node;
	BSTR str;

	wsprintf(szTmp, TEXT("a"));
	node=pxpGetXPathNode(parent, szTmp);

	this->m_listQuest[nIndex].enStatus=QUESTSTATUS_NA;

	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_className(&str);
			if (str)
			{
				if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("quest_slot_button_cancel"), -1))
				{
					this->m_listQuest[nIndex].enStatus=QUESTSTATUS_PROCESSING;
				}
				else if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("quest_slot_button_finish"), -1))
				{
					this->m_listQuest[nIndex].enStatus=QUESTSTATUS_SUCCESS;
				}
				else if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("quest_slot_button_accept"), -1))
				{
					this->m_listQuest[nIndex].enStatus=QUESTSTATUS_FREE;
				}
				else if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("quest_slot_button_restart"), -1))
				{
					this->m_listQuest[nIndex].enStatus=QUESTSTATUS_RESTART;
				}

				SysFreeString(str);
			}
			
			elm->Release();
		}

		node->Release();
	}
}

BOOL GameQuest::_IsQuestArea( IHTMLDOMNode *node )
{
	IHTMLElement *elm;
	BSTR str;
	BOOL brs;

	brs=FALSE;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (BrowserUtility::IsClass(node, TEXT("contentboard_slot")))
			brs=TRUE;
	}

	return brs;
}

void GameQuest::_GetBattleCount( IHTMLDOMNode *parent, int nIndex )
{
	TCHAR szTmp[100];
	IHTMLElement *elm;
	IHTMLStyle *style;
	IHTMLDOMNode *node;
	BSTR str;

	wsprintf(szTmp, TEXT("div[4]"));
	node=pxpGetXPathNode(parent, szTmp);

	this->m_listQuest[nIndex].nBattleMax=0;
	this->m_listQuest[nIndex].nBattleNow=0;

	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_innerText(&str);
			if (str)
			{
				ppParseToNumber((TCHAR*)str, TEXT("/"), NULL, 2
					, &this->m_listQuest[nIndex].nBattleNow, &this->m_listQuest[nIndex].nBattleMax);

				SysFreeString(str);
			}

			elm->Release();
		}

		node->Release();
	}
}


void GameQuest::_GetQuestCooldown( IHTMLDOMNode *parent, int nIndex )
{
	TCHAR szTmp[100];
	IHTMLElement *elm;
	IHTMLStyle *style;
	IHTMLDOMNode *node;
	BSTR str;

	wsprintf(szTmp, TEXT("div[4]"));
	node=pxpGetXPathNode(parent, szTmp);

	this->m_listQuest[nIndex].nBattleMax=0;
	this->m_listQuest[nIndex].nBattleNow=0;

	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_innerText(&str);
			if (str)
			{
				ppParseToNumber((TCHAR*)str, TEXT("/"), NULL, 2
					, &this->m_listQuest[nIndex].nBattleNow, &this->m_listQuest[nIndex].nBattleMax);

				SysFreeString(str);
			}

			elm->Release();
		}

		node->Release();
	}
}

void GameQuest::_GetCooldown(IHTMLDOMNode *parent)
{
	IHTMLDOMNode *node, *tickNode;
	IHTMLElement *elm;
	BSTR str;
	int h, m, s;
	TCHAR szTmp[100];


	wsprintf(szTmp, TEXT("div[2]"));
	node=pxpGetXPathNode(parent, szTmp);

	if (node)
	{
		if (BrowserUtility::IsId(node, TEXT("quest_header_cooldown")))
		{
			wsprintf(szTmp, TEXT("b/span"));
			tickNode=pxpGetXPathNode(node, szTmp);
			if (tickNode)
			{
				tickNode->QueryInterface(IID_IHTMLElement, (void**)&elm);
				if (elm)
				{
					if (BrowserUtility::IsClass(elm, TEXT("z")))
					{
						elm->get_innerText(&str);
						if (str)
						{
							h=0; m=0; s=0;
							if (ppParseToNumber((TCHAR*)str, TEXT(":"), NULL, 3, &h, &m, &s))
							{
								this->_SynchronizedCooldown();
								this->SetCooldown((h*60+m)*60+s);
							}

							SysFreeString(str);
						}
					}
					elm->Release();
				}
				tickNode->Release();
			}			
		}
		node->Release();
	}
}

void GameQuest::_GetReward( IHTMLDOMNode *parent, int nIndex )
{
	TCHAR szTmp[100];
	IHTMLElement *elm;
	IHTMLStyle *style;
	IHTMLDOMNode *node;
	BSTR str;
	IHTMLScriptElement *script;

	wsprintf(szTmp, TEXT("div[3]/div[3]/span"));
	node=pxpGetXPathNode(parent, szTmp);


	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			VARIANT vt;
			elm->get_onmouseover(&vt);
			//GetScript(vt.pdispVal);

			str=NULL;
			if (str)
			{
				SysFreeString(str);
			}

			elm->Release();
		}

		node->Release();
	}
}

void GameQuest::_GetQuestAcceptInfo(IHTMLDOMNode *parent)
{
	IHTMLDOMNode *node;
	IHTMLElement *elm;
	BSTR str;
	int h, m, s;

	node=pxpGetXPathNode(parent, TEXT("div"));
	this->m_nCurRecvQuest=0;
	this->m_nMaxRecvQuest=0;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			if (BrowserUtility::IsId(elm, TEXT("quest_header_accepted")))
			{
				elm->get_innerText(&str);
				if (str)
				{
					ppParseToNumberIgnoreText((TCHAR*)str, TEXT("/"), NULL, 2, &this->m_nCurRecvQuest, &this->m_nMaxRecvQuest);

					SysFreeString(str);
				}
			}

			elm->Release();
		}

		node->Release();
	}
}

void GameQuest::_GetQuestHeader( IHTMLDOMNode *parent )
{
	IHTMLDOMNode *node;
	IHTMLElement *elm;
	BSTR str;
	int h, m, s;
	TCHAR szTmp[100];

	wsprintf(szTmp, TEXT("div/div"));
	node=pxpGetXPathNode(parent, szTmp);

	if (node)
	{
		if (this->_IsQuestHeaderArea(node))
		{
			this->_GetQuestAcceptInfo(node);
			this->_GetCooldown(node);
		}

		node->Release();
	}
}

BOOL GameQuest::_IsQuestHeaderArea( IHTMLDOMNode *node )
{
	return BrowserUtility::IsClass(node, TEXT("contentboard_inner"));
}

BOOL GameQuest::_IsQuestAcceptArea( IHTMLElement *elm )
{
	return BrowserUtility::IsId(elm, TEXT("quest_header_accepted"));
}

BOOL GameQuest::RefreshQuest()
{
	IDispatch *dis;
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *node;
	BOOL brs;

	brs=FALSE;
	this->m_wb2->get_Document(&dis);
	if (dis)
	{
		dis->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
		if (doc3)
		{
			node=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_QUESTREFRESH);
			if (node)
			{
				LogWriteLine(gv_dbgConsole, TEXT("Quest: Refresh"));
				brs=psSimulatorClick(node);

				node->Release();
			}
			doc3->Release();
		}

		dis->Release();
	}

	return brs;
}

BOOL GameQuest::RestartQuest( int nIndex )
{
	return this->_ActionQuestButton(nIndex, QUESTSTATUS_RESTART);
}


BOOL GameQuest::FinishQuest( int nIndex )
{
	return this->_ActionQuestButton(nIndex, QUESTSTATUS_SUCCESS);
}

BOOL GameQuest::StartQuest( int nIndex )
{
	return this->_ActionQuestButton(nIndex, QUESTSTATUS_FREE);
}

IHTMLDOMNode* GameQuest::_GetQuestButtonNode( int nIndex )
{
	IHTMLDOMNode *questNode;
	IHTMLDOMNode *buttonNode;
	TCHAR szTmp[100];

	questNode=this->_GetQuestNode(nIndex);
	if (questNode)
	{
		wsprintf(szTmp, TEXT("a"));//Icon quest
		buttonNode=pxpGetXPathNode(questNode, szTmp);

		questNode->Release();
	}

	return buttonNode;
}

IHTMLDOMNode* GameQuest::_GetQuestRoot()
{
	IHTMLDocument3 *doc3;
	IDispatch *dis;
	IHTMLDOMNode *node;

	node=NULL;
	if (this->m_wb2)
	{
		this->m_wb2->get_Document(&dis);
		if (dis)
		{
			dis->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
			if (doc3)
			{
				node=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_LISTQUEST);
				if (!BrowserUtility::IsClass(node, TEXT("contentboard_start")))
				{
					if (node)
						node->Release();
					node=NULL;
				}

				doc3->Release();
			}
			dis->Release();
		}
	}

	return node;
}

IHTMLDOMNode* GameQuest::_GetQuestNode( int nIndex )
{
	IHTMLDOMNode *rootNode;
	IHTMLDOMNode *questNode;
	TCHAR szTmp[100];

	questNode=NULL;
	rootNode=this->_GetQuestRoot();
	if (rootNode)
	{
		wsprintf(szTmp, TEXT("div[%d]"), nIndex+2);//Icon quest
		questNode=pxpGetXPathNode(rootNode, szTmp);

		rootNode->Release();
	}

	return questNode;
}

BOOL GameQuest::_ActionQuestButton( int nIndex, QUESTSTATUS status )
{
	IHTMLDOMNode *questButton;
	BOOL brs;

	if (this->m_listQuest[nIndex].enStatus!=status)
		return TRUE;

	questButton=this->_GetQuestButtonNode(nIndex);
	brs=FALSE;
	if (questButton)
	{
		switch(this->m_listQuest[nIndex].enStatus)
		{
		case QUESTSTATUS_FREE:
			LogWriteLine(gv_dbgConsole, TEXT("Quest: Start %d"), nIndex);
			break;
		case QUESTSTATUS_RESTART:
			LogWriteLine(gv_dbgConsole, TEXT("Quest: Restart %d"), nIndex);
			break;
		case QUESTSTATUS_SUCCESS:
			LogWriteLine(gv_dbgConsole, TEXT("Quest: Finished %d"), nIndex);
			break;
		}
		brs=psSimulatorClick(questButton);

		questButton->Release();
	}
	return brs;
}

int GameQuest::FindFightQuest()
{
	int index;

	index=-1;
	for (int i=0; i<this->m_nListQuest; i++)
	{
		if (this->m_listQuest[i].bIsActive==FALSE
			&& (this->m_listQuest[i].nType==QUESTTYPE_ARENA
				|| this->m_listQuest[i].nType==QUESTTYPE_TURMA
				|| this->m_listQuest[i].nType==QUESTTYPE_COMBAT)
			)
		{
			index=i;
			break;
		}
	}
	return index;
}

BOOL GameQuest::CanAction()
{
	BOOL brs;

	brs=FALSE;
	for (int i=0; i<this->m_nListQuest; i++)
	{
		if (this->m_listQuest[i].enStatus==QUESTSTATUS_FREE
			|| this->m_listQuest[i].enStatus==QUESTSTATUS_RESTART
			|| this->m_listQuest[i].enStatus==QUESTSTATUS_SUCCESS)
		{
			brs=TRUE;
			break;
		}
	}
	if (this->m_nCurRecvQuest<this->m_nMaxRecvQuest && this->m_nCooldown==0)
		brs=TRUE;

	return brs;
}

BOOL GameQuest::DoAction()
{
	BOOL brs;
	IHTMLDOMNode *node;

	brs=FALSE;
	for (int i=0; i<this->m_nListQuest; i++)
	{
		if (this->m_listQuest[i].enStatus==QUESTSTATUS_RESTART
			|| this->m_listQuest[i].enStatus==QUESTSTATUS_SUCCESS)
		{
			brs=this->_ActionQuestButton(i, this->m_listQuest[i].enStatus);
			break;
		}

		if (this->m_listQuest[i].enStatus==QUESTSTATUS_FREE
			&& this->_IsFightQuest(i))
		{
			brs=this->StartQuest(i);
			break;
		}
	}

	if (!brs)
		brs=this->RefreshQuest();

	return brs;
}

void GameQuest::SetInited( BOOL bInit )
{
	this->m_bInit=bInit;
}

BOOL GameQuest::IsInited()
{
	return this->m_bInit;
}

void GameQuest::IncQuestArena()
{
	this->_IncQuest(QUESTTYPE_ARENA);
}

void GameQuest::IncQuestTurma()
{
	this->_IncQuest(QUESTTYPE_TURMA);
}

void GameQuest::IncQuestCombat()
{
	this->_IncQuest(QUESTTYPE_COMBAT);
}

void GameQuest::_IncQuest( QUESTTYPE type )
{
	for (int i=0; i<this->m_nListQuest; i++)
	{
		if (this->m_listQuest[i].enStatus==QUESTSTATUS_PROCESSING
			&& this->m_listQuest[i].bIsActive
			&& this->m_listQuest[i].nType==type
			&& this->m_listQuest[i].nBattleNow<this->m_listQuest[i].nBattleMax)
		{
			this->m_listQuest[i].nBattleNow++;
		}
	}
}

BOOL GameQuest::HasQuestFinished()
{
	for (int i=0; i<this->m_nListQuest; i++)
	{
		if (this->m_listQuest[i].bIsActive && this->m_listQuest[i].nBattleMax==this->m_listQuest[i].nBattleNow)
			return TRUE;
	}

	return FALSE;
}

int GameQuest::GetCooldown()
{
	return this->m_nCooldown;
}

void GameQuest::SetCooldown( int nCooldown )
{
	this->m_nCooldown=nCooldown;
}

BOOL GameQuest::CanStartQuest()
{
	if (this->m_nCurRecvQuest<this->m_nMaxRecvQuest)
		return TRUE;
	return FALSE;
}

BOOL GameQuest::_IsFightQuest( int nIndex )
{
	if (this->m_listQuest[nIndex].nType==QUESTTYPE_ARENA
		|| this->m_listQuest[nIndex].nType==QUESTTYPE_TURMA
		|| this->m_listQuest[nIndex].nType==QUESTTYPE_COMBAT)
		return TRUE;

	return FALSE;
}

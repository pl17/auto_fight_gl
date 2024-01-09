#include "GQuestObject_Quest.h"
#include "BrowserUtility.h"
#include "PParser.h"
#include "PXPath.h"

#include "Logs.h"

extern IOutputDebug *gv_dbgConsole;

GQuestObject_Quest::GQuestObject_Quest()
{
	this->m_quests=new QuestObject[QUEST_MAXQUEST]();
	this->m_bInited=FALSE;
	this->m_nTotalQuest=0;
}

GQuestObject_Quest::~GQuestObject_Quest()
{
	delete[] this->m_quests;
}

void GQuestObject_Quest::Synchronized( IWebBrowser2 *wb2 )
{
	this->_SynchronizedQuest(wb2);
}

void GQuestObject_Quest::OnArenaFinish( BOOL bWin )
{
	for (int i=0; i<this->m_nTotalQuest; i++)
	{
		if (this->m_quests[i].IsActive() 
			&& (this->m_quests[i].GetQuestType()==QUESTTYPE_ARENA || this->m_quests[i].GetQuestType()==QUESTTYPE_COMBAT))
		{
			if (bWin)
			{
				this->m_quests[i].IncBattleCount();
			}
			else if (this->m_quests[i].IsInSuccessionQuest())
			{
				this->m_quests[i].SetRestartStatus();//Switch status to restart
			}
		}
	}
}

void GQuestObject_Quest::OnTurmaFinish( BOOL bWin )
{
	for (int i=0; i<this->m_nTotalQuest; i++)
	{
		if (this->m_quests[i].IsActive() 
			&& (this->m_quests[i].GetQuestType()==QUESTTYPE_TURMA || this->m_quests[i].GetQuestType()==QUESTTYPE_COMBAT))
		{
			if (bWin)
			{
				this->m_quests[i].IncBattleCount();
			}
			else if (this->m_quests[i].IsInSuccessionQuest())
			{
				this->m_quests[i].SetRestartStatus();
			}
		}
	}
}

void GQuestObject_Quest::OnExpeditionFinish( BOOL bWin )
{
	
}

BOOL GQuestObject_Quest::RefrestQuest(IWebBrowser2 *wb2)
{
	BOOL brs;
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *node;

	brs=FALSE;

	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		node=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_QUESTREFRESH);
		if (node)
		{
			if (!BrowserUtility::IsDisabled(node))
			{
				LogWriteLine(gv_dbgConsole, TEXT("Quest: Refresh"));
				brs=BrowserUtility::Simulator(node);
			}

			node->Release();
		}

		doc3->Release();
	}

	return brs;
}


BOOL GQuestObject_Quest::ActionQuest( IWebBrowser2 *wb2, int nIndex )
{
	return this->_ActionQuest(wb2, nIndex);
}


BOOL GQuestObject_Quest::CanAction()
{
	QUESTSTATUS status;
	BOOL brs;

	brs=FALSE;
	for (int i=0; i<this->m_nTotalQuest; i++)
	{
		status=this->m_quests[i].GetQuestStatus();
		if (status==QUESTSTATUS_FREE
			|| status==QUESTSTATUS_RESTART
			|| status==QUESTSTATUS_SUCCESS)
		{
			brs=TRUE;
			break;
		}
	}
	if (this->m_nCooldown==0 && this->m_nCurrentRecvQuest<this->m_nMaxRecvQuest)
		brs=TRUE;

	return brs;
}


BOOL GQuestObject_Quest::TryAction(IWebBrowser2 *wb2)
{
	BOOL brs;
	QUESTSTATUS status;
	int index;

	brs=FALSE;
	index=-1;
	for (int i=0; i<this->m_nTotalQuest; i++)
	{
		status=this->m_quests[i].GetQuestStatus();
		if (status==QUESTSTATUS_RESTART || status==QUESTSTATUS_SUCCESS
			|| (status==QUESTSTATUS_FREE && this->m_quests[i].IsFightQuest()))
		{
			brs=TRUE;
			index=i;
			break;
		}
	}

	if (brs)
	{
		brs=this->_ActionQuest(wb2, index);
	}
	else
	{
		brs=this->RefrestQuest(wb2);
	}

	return brs;
}

int GQuestObject_Quest::FindQuest()
{
	return TRUE;
}


BOOL GQuestObject_Quest::HasQuestFinish()
{
	for (int i=0; i<this->m_nTotalQuest; i++)
	{
		if (this->m_quests[i].IsActive() && this->m_quests[i].GetMaxBattle()==this->m_quests[i].GetCurrentBattle())
			return TRUE;
	}
	return FALSE;
}

BOOL GQuestObject_Quest::_IsQuestHeaderArea( IHTMLDOMNode *node )
{
	return BrowserUtility::IsClass(node, TEXT("contentboard_inner"));
}

void GQuestObject_Quest::_SynchronizedQuestList( IHTMLDOMNode *rootQuest )
{
	IHTMLDOMNode *node;
	TCHAR szTmp[100];
	int nIndex;
	BOOL bCanLoop;


	if (rootQuest)
	{
		this->m_nTotalQuest=0;
		nIndex=1;
		bCanLoop=TRUE;
		do
		{
			nIndex++;
			wsprintf(szTmp, TEXT("div[%d]"), nIndex);//Root quest
			node=pxpGetXPathNode(rootQuest, szTmp);

			if (node)
			{
				if (this->m_quests[this->m_nTotalQuest].Synchronized(node))
				{
					this->m_nTotalQuest++;
				}
				else
					bCanLoop=FALSE;
					
				
				node->Release();
			}
		} while (bCanLoop && node);

		//rootQuest->Release();
	}
}

void GQuestObject_Quest::_SynchronizedQuestHeader( IHTMLDOMNode *rootQuest )
{
	IHTMLDOMNode *nodeHeader;

	if (rootQuest)
	{
		nodeHeader=pxpGetXPathNode(rootQuest, TEXT("div[1]/div"));
		if (nodeHeader)
		{
			if (this->_IsQuestHeaderArea(nodeHeader))
			{
				this->_ParseQuestHeaderCountInfo(nodeHeader);
				this->_ParseQuestHeaderCooldown(nodeHeader);
			}

			nodeHeader->Release();
		}
	}
}

void GQuestObject_Quest::_SynchronizedQuest( IWebBrowser2 *wb2 )
{
	IHTMLDocument3 *doc3;
	IDispatch *disDoc;
	IHTMLDOMNode *rootQuestList;


	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		rootQuestList=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_LISTQUEST);
		if (rootQuestList)
		{
			this->m_bInited=TRUE;
			this->_SynchronizedQuestHeader(rootQuestList);
			this->_SynchronizedQuestList(rootQuestList);
			rootQuestList->Release();
		}

		doc3->Release();
	}
}

void GQuestObject_Quest::_ParseQuestHeaderCooldown( IHTMLDOMNode *rootQuest )
{
	IHTMLDOMNode *node, *tickNode;
	BSTR str;
	int h, m, s;
	TCHAR szTmp[100];


	if (rootQuest)
	{
		node=pxpGetXPathNode(rootQuest, TEXT("div[2]"));
		if (node)
		{
			if (BrowserUtility::IsId(node, TEXT("quest_header_cooldown")))
			{
				wsprintf(szTmp, TEXT("b/span"));
				tickNode=pxpGetXPathNode(node, TEXT("b/span"));
				BSTR str;
				BrowserUtility::GetNodeInnerText(tickNode, &str);
				if (tickNode)
				{
					//if (BrowserUtility::IsClass(node, TEXT("z")))
					{
						BrowserUtility::GetNodeInnerText(tickNode, &str);
						if (str)
						{
							h=0; m=0; s=0;
							if (ppParseToNumber(str, TEXT(":"), NULL, 3, &h, &m, &s))
							{
								this->SetCooldown((h*60+m)*60+s);
							}
							SysFreeString(str);
						}
					}
					tickNode->Release();
				}			
			}
			node->Release();
		}
	}
}

void GQuestObject_Quest::_ParseQuestHeaderCountInfo( IHTMLDOMNode *rootQuest )
{
	IHTMLDOMNode *node;
	BSTR str;

	if (rootQuest)
	{
		node=pxpGetXPathNode(rootQuest, TEXT("div"));
		this->m_nCurrentRecvQuest=0;
		this->m_nMaxRecvQuest=0;
		if (node)
		{
			if (BrowserUtility::IsId(node, TEXT("quest_header_accepted")))
			{
				BrowserUtility::GetNodeInnerText(node, &str);
				if (str)
				{
					ppParseToNumberIgnoreText((TCHAR*)str, TEXT("/"), NULL, 2, &this->m_nCurrentRecvQuest, &this->m_nMaxRecvQuest);
					SysFreeString(str);
				}
			}

			node->Release();
		}
	}
}

BOOL GQuestObject_Quest::_ActionQuest( IWebBrowser2 *wb2, int nIndex )
{
	BOOL brs;
	IHTMLDOMNode *questButton;
	IHTMLDocument3 *doc3;
	IDispatch *disDoc;

	brs=FALSE;
	VARIANT_BOOL vb;
	wb2->get_Busy(&vb);
	if (vb==VARIANT_TRUE) return FALSE;
	
	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		questButton=this->_GetQuestButtonNode(doc3, nIndex);
		if (questButton)
		{
			switch(this->m_quests[nIndex].GetQuestStatus())
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
			brs=BrowserUtility::Simulator(questButton);

			questButton->Release();
		}

		doc3->Release();
	}

	return brs;
}

IHTMLDOMNode* GQuestObject_Quest::_GetQuestButtonNode( IHTMLDocument3 *doc3, int nIndex )
{
	IHTMLDOMNode *questNode;
	IHTMLDOMNode *buttonNode;

	questNode=this->_GetQuestNode(doc3, nIndex);
	buttonNode=NULL;
	if (questNode)
	{
		buttonNode=pxpGetXPathNode(questNode, TEXT("a"));

		questNode->Release();
	}

	return buttonNode;
}

IHTMLDOMNode* GQuestObject_Quest::_GetQuestNode( IHTMLDocument3 *doc3, int nIndex )
{
	IHTMLDOMNode *questList;
	IHTMLDOMNode *questNode;
	TCHAR szTxt[50];

	questNode=NULL;
	questList=this->_GetQuestListRoot(doc3);
	if (questList)
	{
		wsprintf(szTxt, TEXT("div[%d]"), nIndex+2);
		questNode=pxpGetXPathNode(questList, szTxt);
		questList->Release();
	}

	return questNode;
}

IHTMLDOMNode* GQuestObject_Quest::_GetQuestListRoot( IHTMLDocument3 *doc3 )
{
	IHTMLDOMNode *node;

	node=NULL;
	if (doc3)
	{
		node=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_LISTQUEST);
		if (!BrowserUtility::IsClass(node, TEXT("contentboard_start")))
		{
			if (node)
				node->Release();
			node=NULL;
		}
	}

	return node;
}

BOOL GQuestObject_Quest::IsInited()
{
	return this->m_bInited;
}


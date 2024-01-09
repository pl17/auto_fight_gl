#include "GameManager.h"
#include "GameArenaServer.h"
#include "GameObj_XPathConst.h"
#include "PXPath.h"
#include "PParser.h"
#include "PSimulator.h"
#include "BrowserUtility.h"

GameArenaServer::GameArenaServer( IWebBrowser2 *wb2 )
{
	this->m_wb2=wb2;
	this->m_bListPlayer=FALSE;
	this->UpdateValue();
}

GameArenaServer::~GameArenaServer()
{
// 	if (this->m_wb2)
// 		this->m_wb2->Release();
}

void GameArenaServer::UpdateValue()
{
	this->_GetListPlayer();
	this->_SortListPlayer();
}

void GameArenaServer::_SortListPlayer()
{
	int i, j, t;

	for (i=0; i<GAMEARENA_MAXPLAYER; i++)
		this->m_listIndexPlayer[i]=i;

	for (i=0; i<GAMEARENA_MAXPLAYER-1; i++)
	{
		for (j=i+1; j<GAMEARENA_MAXPLAYER; j++)
		{
			if (this->m_listPlayer[this->m_listIndexPlayer[i]].nLevel>this->m_listPlayer[this->m_listIndexPlayer[j]].nLevel)
			{
				t=this->m_listIndexPlayer[i];
				this->m_listIndexPlayer[i]=this->m_listIndexPlayer[j];
				this->m_listIndexPlayer[j]=t;
			}
		}
	}
}

BOOL GameArenaServer::_GetListPlayer()
{
	TCHAR szTmp[100];
	IHTMLDocument3 *doc3;
	IDispatch *dis;
	IHTMLDOMNode *rootList, *node;
	VARIANT vt;
	int nMinLevelIndex, nMinLevel, nTmp;

	if (this->m_wb2)
	{
		this->m_wb2->get_Document(&dis);
		if (dis)
		{
			dis->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
			if (doc3)
			{
				rootList=this->_GetNodeList(doc3);

				if (rootList)
				{
					this->m_bListPlayer=TRUE;
					nMinLevelIndex=2;
					nMinLevel=10000;
					for (int i=2; i<=6; i++)
					{
						this->m_listPlayer[i-2].bEnable=TRUE;

						//Get name player
						_stprintf(szTmp, TEXT("tr[%d]/td[1]/a"), i);
						node=pxpGetXPathNode(rootList, szTmp);
						if (node)
						{
							pxpGetNodeValue(node, &vt);
							node->Release();
							if (vt.vt==VT_BSTR)
							{
								CopyMemory(this->m_listPlayer[i-2].szPlayerName, vt.bstrVal, (1+_tcslen((TCHAR*)vt.bstrVal))*sizeof(TCHAR));
								SysFreeString(vt.bstrVal);
							}
						}
						else
						{
							this->m_listPlayer[i-2].bEnable=FALSE;
						}

						//Get player level
						_stprintf(szTmp, TEXT("tr[%d]/td[2]"), i);
						node=pxpGetXPathNode(rootList, szTmp);
						if (node)
						{
							pxpGetNodeValue(node, &vt);
							ppParseToNumber((TCHAR*)vt.bstrVal, NULL, NULL, 1, &this->m_listPlayer[i-2].nLevel);
// 							if (nTmp<nMinLevel)
// 							{
// 								nMinLevel=nTmp;
// 								nMinLevelIndex=i;
// 							}
							node->Release();
							if (vt.vt==VT_BSTR) SysFreeString(vt.bstrVal);
						}
						else
						{
							this->m_listPlayer[i-2].bEnable=TRUE;
						}

						//Get player server
						_stprintf(szTmp, TEXT("tr[%d]/td[3]"), i);
						node=pxpGetXPathNode(rootList, szTmp);
						if (node)
						{
							pxpGetNodeValue(node, &vt);
							ppParseToNumber((TCHAR*)vt.bstrVal, NULL, NULL, 1, &this->m_listPlayer[i-2].nServer);
							node->Release();
							if (vt.vt==VT_BSTR) SysFreeString(vt.bstrVal);
						}
						else
						{
							this->m_listPlayer[i-2].bEnable=TRUE;
						}
					}
				}

				doc3->Release();
			}
			dis->Release();
		}
	}

	return TRUE;
}

ARENA_PLAYER* GameArenaServer::GetListArenaPlayer()
{
	return this->m_listPlayer;
}

BOOL GameArenaServer::AttackPlayer( int index )
{
	TCHAR szTmp[100];
	IHTMLDOMNode *node, *rootList;
	IDispatch *dis;
	IHTMLDocument3 *doc3;
	BOOL brs;

	brs=FALSE;
	if (this->m_wb2 && index>=0)
	{
		this->m_wb2->get_Document(&dis);
		if (dis)
		{
			dis->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
			if (doc3)
			{
				rootList=this->_GetNodeList(doc3);
				if (rootList)
				{
					_stprintf(szTmp, TEXT("tr[%d]/td[4]/span"), index+2);
					node=pxpGetXPathNode(rootList, szTmp);
					if (node)
					{
						brs=psSimulatorClick(node);

						node->Release();
					}
					rootList->Release();
				}

				doc3->Release();
			}
			dis->Release();
		}
	}

	return brs;
}

IHTMLDOMNode* GameArenaServer::_GetNodeList( IHTMLDocument3 *doc3 )
{
	IHTMLDOMNode *rootList;

	rootList=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_LISTARENASERVER);
	if (rootList==NULL)
		rootList=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_LISTARENASERVER_EMAILNOTACTIVE);
	if (rootList==NULL)
		rootList=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_LISTARENASERVER_BASH);

	return rootList;
}

BOOL GameArenaServer::AttackPlayerMinLevel(int nFirstIndex)
{
	BOOL brs;
	int index;

	brs=FALSE;
	//index=this->GetIndexPlayerMinLevel();
	brs=this->AttackPlayer(this->m_listIndexPlayer[nFirstIndex+1]);

	return brs;
}

int GameArenaServer::GetIndexPlayerMinLevel(int nFirstIndex)
{
	int index;

	return this->m_listIndexPlayer[nFirstIndex+1];

	if (this->m_bListPlayer)
	{
		index=0;
		for (int i=0; i<GAMEARENA_MAXPLAYER; i++)
		{
			if (this->m_listPlayer[i].nLevel<this->m_listPlayer[index].nLevel)
				index=i;
		}
	}
	else
		index=-1;

	return index;
}

BOOL GameArenaServer::CheckBash( IWebBrowser2 *wb2 )
{
	GAMEOBJ_XPATH xpath;
	BOOL brs;
	IHTMLElement *elm;
	IHTMLElement2 *elm2;
	IHTMLDocument3 *doc3;
	IHTMLCurrentStyle *style;
	IDispatch *dis1, *dis2;
	BSTR str;


	xpath.lpcszId=TEXT("blackoutDialogbod");
	xpath.lpcszXPath=TEXT("div[2]/table/tbody/tr/td[2]/div/input");

	brs=FALSE;

	str=NULL;
	if (wb2)
	{
		wb2->get_Document(&dis1);
		if (dis1)
		{
			dis1->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
			if (doc3)
			{
				doc3->getElementById(TEXT("blackoutDialogbod"), &elm);
				if (elm)
				{
					elm->QueryInterface(IID_IDispatch, (void**)&dis2);
					if (dis2)
					{
						dis2->QueryInterface(IID_IHTMLElement2, (void**)&elm2);
						if (elm2)
						{
							elm2->get_currentStyle(&style);
							if (style)
							{
								style->get_display(&str);
								if (str)
								{
									if (wcsicmp((TCHAR*)str, TEXT("block"))==0)
										brs=TRUE;

									SysFreeString(str);
								}
								style->Release();
							}

							elm2->Release();
						}
						dis2->Release();
					}

					elm->Release();
				}

				doc3->Release();
			}
			dis1->Release();
		}
	}

	GameManager::SimulatorClick(wb2, &xpath);

	return brs;
}

BOOL GameArenaServer::CheckFightReport( IWebBrowser2 *wb2, BOOL *lpbWin )
{
	IHTMLDocument3 *doc3;
	IDispatch *dis;
	IHTMLElement *elm;
	BSTR str;
	BOOL brs;

	brs=FALSE;
	if (wb2)
	{
		wb2->get_Document(&dis);
		if (dis)
		{
			dis->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
			if (doc3)
			{
				doc3->getElementById(TEXT("reportHeader"), &elm);
				if (elm)
				{
					elm->get_className(&str);
					if (str)
					{
						brs=TRUE;
						if (wcsicmp((TCHAR*)str, TEXT("reportwin"))==0)
						{
							*lpbWin=TRUE;
						}
						else
						{
							*lpbWin=FALSE;
						}

						SysFreeString(str);
					}
					doc3->Release();
				}
			}
			dis->Release();
		}
	}

	return brs;
}

void gasGetValue(IHTMLDOMNode *node, VARIANT *vt)
{
	if (node)
	{
		node->get_nodeValue(vt);
	}
}

BOOL GameArenaServer::GetFightWinInfo( IWebBrowser2 *wb2, int nType, int *lpnGoldTotal, int *lpnGoldBase, int *lpnExp, int *lpnHonor )
{
	GAMEOBJ_XPATH xpath;
	IHTMLDOMNode *rootInfo, *node;
	IHTMLDocument3 *doc3;
	IDispatch *disDoc;
	VARIANT vt;
	BOOL brs;

	xpath.lpcszId=TEXT("content");
	if (nType==0)//Arena
		xpath.lpcszXPath=TEXT("div[2]/div[2]/div/table/tbody/tr[1]/td");
	else //Turma
		xpath.lpcszXPath=TEXT("div[3]/div[2]/div/table/tbody/tr[1]/td");

	if (lpnGoldTotal) *lpnGoldTotal=0;
	if (lpnGoldBase) *lpnGoldBase=0;
	if (lpnExp) *lpnExp=0;
	if (lpnHonor) *lpnHonor=0;

	brs=FALSE;
	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		rootInfo=pxpGetXPathNode(doc3, &xpath);
		if (rootInfo)
		{
			node=pxpGetXPathNode(rootInfo, TEXT("p/#text"));
			if (node)
			{
				gasGetValue(node, &vt);
				if (vt.vt==VT_BSTR && vt.bstrVal!=NULL)
				{
					if (lpnGoldTotal)
						ppParseToNumberIgnoreText((TCHAR*)vt.bstrVal, NULL, TEXT("."), 1, lpnGoldTotal);
					SysFreeString(vt.bstrVal);
				}
				node->Release();
			}

			node=pxpGetXPathNode(rootInfo, TEXT("p/#text[3]"));
			if (node)
			{
				gasGetValue(node, &vt);
				if (vt.vt==VT_BSTR && vt.bstrVal!=NULL)
				{
					if (lpnGoldBase)
						ppParseToNumberIgnoreText((TCHAR*)vt.bstrVal, NULL, TEXT("."), 1, lpnGoldBase);
					SysFreeString(vt.bstrVal);
				}
				node->Release();
			}

			node=pxpGetXPathNode(rootInfo, TEXT("p[2]/#text"));
			if (node)
			{
				gasGetValue(node, &vt);
				if (vt.vt==VT_BSTR && vt.bstrVal!=NULL)
				{
					if (lpnExp)
						ppParseToNumberIgnoreText((TCHAR*)vt.bstrVal, NULL, TEXT("."), 1, lpnExp);
					SysFreeString(vt.bstrVal);
				}
				node->Release();
			}

			node=pxpGetXPathNode(rootInfo, TEXT("p[3]/#text"));
			if (node)
			{
				gasGetValue(node, &vt);
				if (vt.vt==VT_BSTR && vt.bstrVal!=NULL)
				{
					if (lpnHonor)
						ppParseToNumberIgnoreText((TCHAR*)vt.bstrVal, NULL, TEXT("."), 1, lpnHonor);
					SysFreeString(vt.bstrVal);
				}
				node->Release();
			}
			brs=TRUE;

			rootInfo->Release();
		}

		doc3->Release();
	}

	return brs;
}

int GameArenaServer::nGoldBase=0;
int GameArenaServer::nGoldTotal=0;
int GameArenaServer::nFightLose=0;
int GameArenaServer::nFightWin=0;
int GameArenaServer::nExp=0;
int GameArenaServer::nHornor=0;

int GameArenaServer::nDGoldBase=0;
int GameArenaServer::nDGoldTotal=0;
int GameArenaServer::nDFightLose=0;
int GameArenaServer::nDFightWin=0;
int GameArenaServer::nDExp=0;
int GameArenaServer::nDFame=0;

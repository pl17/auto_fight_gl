#include "GameManager.h"
#include "PSimulator.h"
#include "Logs.h"
#include "BrowserUtility.h"

extern IOutputDebug *gv_dbgConsole;


GameManager::GameManager( IWebBrowser2 *wb2Location )
{
	this->m_wb2Location=wb2Location;

	this->m_gameLink=new GameLink(this->m_wb2Location);
}

GameManager::~GameManager()
{
	//if (this->m_wb2Location)
	//	this->m_wb2Location->Release();

	if (this->m_gameLink)
		delete this->m_gameLink;
}

int GameManager::GetModId(IWebBrowser2 *wb2)
{
	int nModId;

	this->m_gameLink->SetIWeb(wb2);
	this->m_gameLink->UpdateValue();

	nModId=this->m_gameLink->GetModId();
	if (nModId==GAMELINK_MOD_ARENA)
	{
		BSTR str;

		wb2->get_LocationURL(&str);
		if (str)
		{
			if (wcsstr((TCHAR*)str, TEXT("aType=3")))
				nModId=GAMELINK_MOD_TURMASERVER;
			else if (wcsstr((TCHAR*)str, TEXT("aType=2")))
				nModId=GAMELINK_MOD_ARENASERVER;
			else if (wcsstr((TCHAR*)str, TEXT("submod=grouparena")))
				nModId=GAMELINK_MOD_TURMA;

			SysFreeString(str);
		}
	}

	return nModId;
}

BOOL GameManager::GotoMod( IWebBrowser2 *wb2, int nModId, int nSubModId )
{
	int nCurrentMod, nCurrentSubMod;
	const GAMEOBJ_XPATH *xpath;
	IDispatch *dis;
	IHTMLDocument3 *doc3;
	BOOL brs;
	IDispatch *disDoc;

	//this->m_gameLink->SetIWeb(wb2);
	//this->m_gameLink->UpdateValue();
	//nCurrentSubMod=this->m_gameLink->GetModId();
	nCurrentSubMod=this->GetModId(wb2);

	brs=FALSE;

	if (nCurrentSubMod!=nModId)
	{
		wb2->get_Document(&disDoc);
		if (disDoc)
		{
			disDoc->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
			if (doc3)
			{
				xpath=this->_FindXpathByMod(nModId, nSubModId);
				if (xpath)
				{
					brs=psSimulatorClick(doc3, xpath);
				}

				doc3->Release();
			}

			disDoc->Release();
		}
	}
	else
	{
		brs=TRUE;
	}

	return brs;

	
	/*wb2->get_Document(&dis);

	doc3=NULL;
	brs=FALSE;
	if (dis)
	{
		dis->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
	}
	if (nCurrentSubMod!=nModId)
	{
		xpath=this->_FindXpathByMod(nModId, nSubModId);
		if (xpath)
		{
			brs=psSimulatorClick(doc3, xpath);

			if (gv_dbgConsole)
				LogWriteLine(gv_dbgConsole, TEXT("GotoMod: %d-%d"), nCurrentSubMod, nModId);
		}
	}
	else
	{
		brs=TRUE;
	}

	if (doc3)
		doc3->Release();
	if (dis)
		dis->Release();*/

	return brs;
}

const GAMEOBJ_XPATH* GameManager::_FindXpathByMod( int nModId, int nSubModId )
{
	const GAMEOBJ_XPATH *rs;

	rs=NULL;
	switch (nModId)
	{
/*
	case GAMELINK_MOD_ARENA:
		rs=&GameObj_XPathConst::MOD_ARENA;
		break;
	case GAMELINK_MOD_TURMA:
		rs=&GameObj_XPathConst::MOD_TURMA;
		break;*/
	case GAMELINK_MOD_TURMA:
		rs=&GameObj_XPathConst::MOD_TURMASERVER;
		break;
	case GAMELINK_MOD_ARENA:
		rs=&GameObj_XPathConst::MOD_ARENASERVER;
		break;
	case GAMELINK_MOD_ARENASERVER:
		rs=&GameObj_XPathConst::MOD_ARENA;
		break;
	case GAMELINK_MOD_TURMASERVER:
		rs=&GameObj_XPathConst::MOD_TURMA;
		break;
	case GAMELINK_MOD_LOCATION:
		rs=&GameObj_XPathConst::MOD_LOCATION;
		break;
	case GAMELINK_MOD_DUNGEON:
		rs=&GameObj_XPathConst::MOD_DUNGEON;
		break;
	case GAMELINK_MOD_QUEST:
		rs=&GameObj_XPathConst::MOD_QUEST;
		break;
	}

	return rs;
}

BOOL GameManager::SimulatorClick( IWebBrowser2 *wb2, GAMEOBJ_XPATH *xpath )
{
	IDispatch *dis;
	IHTMLDocument3 *doc3;
	BOOL brs;


	wb2->get_Document(&dis);

	doc3=NULL;
	brs=FALSE;
	if (dis)
	{
		dis->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
		if (doc3)
		{
			brs=psSimulatorClick(doc3, xpath);
			doc3->Release();
		}
		dis->Release();
	}

	return brs;
}

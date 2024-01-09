#include "GameMod_Quest.h"
#include "PXPath.h"
#include "GameObj_XPathConst.h"
#include "BrowserUtility.h"

IHTMLDOMNode* GameMod_Quest::_GetNextNode( IWebBrowser2 *wb2, UQueryString *src )
{
	ModQuest modSrc, modDes;
	IHTMLDOMNode *node;
	IHTMLDocument3 *doc3;

	node=NULL;
	if (wb2 && src && this->m_qsTarget)
	{
		modSrc=this->_GetMod(src);
		modDes=this->_GetMod(this->m_qsTarget);
		doc3=BrowserUtility::GetDocument3(wb2);
		if (doc3)
		{
			if (modSrc==MODQUEST_OTHERMOD)
			{
				node=pxpGetXPathNode(doc3, &GameObj_XPathConst::MOD_QUEST);
			}

			doc3->Release();
		}
	}

	return node;
}

GameMod_Quest::ModQuest GameMod_Quest::_GetMod( UQueryString *query )
{
	ModQuest mod;

	mod=MODQUEST_UNKNOWN;

	if (query)
	{
		if (query->IsEqual(TEXT("mod"), TEXT("quests")))//Check mod
		{
			mod=MODQUEST_QUEST;
		}
		else
		{
			mod=MODQUEST_OTHERMOD;
		}
	}

	return mod;
}

BOOL GameMod_Quest::_IsTruth( UQueryString *qsSrc )
{
	BOOL brs;

	brs=FALSE;

	if (qsSrc)
	{
		brs=qsSrc->IsEqual(TEXT("mod"), TEXT("quests"));
	}

	return brs;
}


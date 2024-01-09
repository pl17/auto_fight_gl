#include "GameMod_Overview.h"
#include "BrowserUtility.h"
#include "PXPath.h"
#include "GameObj_XPathConst.h"

IHTMLDOMNode* GameMod_Overview::_GetNextNode( IWebBrowser2 *wb2, UQueryString *src )
{
	MODOVERVIEW mod;
	IHTMLDOMNode *node;
	IHTMLDocument3 *doc3;

	node=NULL;

	if (wb2 && src)
	{
		mod=this->_GetMod(src);
		doc3=BrowserUtility::GetDocument3(wb2);
		if (doc3)
		{
			if (mod!=MODOVERVIEW_OVERVIEW)
			{
				node=pxpGetXPathNode(doc3, &GameObj_XPathConst::MOD_OVERVIEW);
			}

			doc3->Release();
		}
	}

	return node;
}

BOOL GameMod_Overview::_IsTruth( UQueryString *qsSrc )
{
	BOOL brs;

	brs=FALSE;
	if (qsSrc)
	{
		brs=qsSrc->IsEqual(TEXT("mod"), TEXT("overview"));
	}

	return brs;
}

GameMod_Overview::MODOVERVIEW GameMod_Overview::_GetMod(UQueryString *query)
{
	MODOVERVIEW mod;

	mod=MODOVERVIEW_UNKNOWN;
	if (query)
	{
		if (query->IsEqual(TEXT("mod"), TEXT("overview")))
		{
			mod=MODOVERVIEW_OVERVIEW;
		}
		else
		{
			mod=MODOVERVIEW_OTHERMOD;
		}
	}

	return mod;
}

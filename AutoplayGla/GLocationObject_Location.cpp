#include "GLocationObject_Location.h"
#include "GameLink.h"
#include "GameObj_XPathConst.h"
#include "BrowserUtility.h"
#include "PXPath.h"

#include "Logs.h"

extern IOutputDebug *gv_dbgConsole;

GLocationObject_Location::GLocationObject_Location()
:GLocationObject_Base(GAMELINK_MOD_LOCATION)
{

}

BOOL GLocationObject_Location::AttackMonster( IWebBrowser2 *wb2, int nIndex )
{
	GAMEOBJ_XPATH xpath;
	IHTMLDOMNode *rootNode, *node;
	IHTMLDocument3 *doc3;
	IDispatch *disDoc;
	TCHAR szXpath[100];
	BOOL brs;

	brs=FALSE;
	wb2->get_Document(&disDoc);
	if (disDoc)
	{
		if (doc3)
		{
			xpath.lpcszId=TEXT("content");
			xpath.lpcszXPath=TEXT("div[3]");

			rootNode=pxpGetXPathNode(doc3, &xpath);
			if (rootNode)
			{
				wsprintf(szXpath, TEXT("div[%d]/div[2]/button"), nIndex+1);
				node=pxpGetXPathNode(rootNode, szXpath);
				if (node)
				{
					if (BrowserUtility::IsClass(node, TEXT("expedition_button")))
					{
						brs=BrowserUtility::Simulator(node);
						if (brs)
						{
							BSTR strName;
							strName=this->GetMonsterName(doc3, nIndex);
							if (strName)
							{
								LogWriteLine(gv_dbgConsole, TEXT("Location: Attack monster %s"), strName);
								SysFreeString(strName);
							}
							else
							{
								LogWriteLine(gv_dbgConsole, TEXT("Location: Attack monster unknown"));
							}
						}
					}

					node->Release();
				}

				rootNode->Release();
			}

			doc3->Release();
		}

		disDoc->Release();
	}

	return brs;
}

BSTR GLocationObject_Location::GetMonsterName( IHTMLDocument3 *doc3, int nIndex )
{
	GAMEOBJ_XPATH xpath;
	TCHAR szId[50];
	IHTMLDOMNode *node;
	VARIANT vtName;

	wsprintf(szId, TEXT("expedition_info%d"), nIndex+1);
	xpath.lpcszId=szId;
	xpath.lpcszXPath=TEXT("div");

	vtName.bstrVal=NULL;
	node=pxpGetXPathNode(doc3, &xpath);
	if (node)
	{
		pxpGetNodeValue(node, &vtName);
		node->Release();
	}

	return vtName.bstrVal;
}

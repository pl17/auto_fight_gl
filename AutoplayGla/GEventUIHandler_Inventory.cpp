#include "GEventUIHandler_Inventory.h"
#include "BrowserUtility.h"
#include "PXPath.h"
#include "PParser.h"
#include "GameLink.h"


GEventUIHandler_Inventory::GEventUIHandler_Inventory()
{
	this->m_nLastInvId=0;
}


void GEventUIHandler_Inventory::Synchronized( IWebBrowser2 *wb2 )
{
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *rootMenu, *nodeMenu, *nodeTmp;
	IDispatch *disDoc;

	this->_SynchronizedInvId(wb2);
	

	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		rootMenu=this->_GetRootMenu(doc3);
		if (rootMenu)
		{
			rootMenu->get_firstChild(&nodeMenu);
			while (nodeMenu)
			{
				this->_GetHref(nodeMenu);

				nodeMenu->get_nextSibling(&nodeTmp);
				nodeMenu->Release();
				nodeMenu=nodeTmp;
			}

			rootMenu->Release();
		}

		doc3->Release();
	}
}

IHTMLDOMNode* GEventUIHandler_Inventory::_GetRootMenu( IHTMLDocument3 *doc3 )
{
	IHTMLElement *elm;
	IHTMLDOMNode *rs;

	rs=NULL;
	if (doc3)
	{
		doc3->getElementById(TEXT("submenu1"), &elm);
		if (elm)
		{
			elm->QueryInterface(IID_IHTMLDOMNode, (void**)&rs);
			elm->Release();
		}
	}

	return rs;
}

BOOL GEventUIHandler_Inventory::_CheckMenuTag( IHTMLDOMNode *node )
{
	BOOL rs;
	BSTR str;

	//rs=BrowserUtility::IsClass(node, TEXT("submenuitem"));
	//if (rs)
	{
		node->get_nodeName(&str);
		rs=FALSE;
		if (str)
		{
			if (ppIsEqualIgnoreCase((TCHAR*)str, TEXT("a"), -1))
				rs=TRUE;

			SysFreeString(str);
		}
	}

	return rs;
}

BSTR GEventUIHandler_Inventory::_GetHref( IHTMLDOMNode *node )
{
	BSTR str;
	IHTMLAnchorElement *elmA;
	TCHAR szTxt[200];

	str=NULL;

	if (this->_CheckMenuTag(node))
	{
		node->QueryInterface(IID_IHTMLAnchorElement, (void**)&elmA);
		if (elmA)
		{
			elmA->get_href(&str);
			if (str)
			{
				if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("mod=inventory"), -1))
				{
					wsprintf(szTxt, TEXT("%s&subsub=2&inv=%d"), (TCHAR*)str, this->m_nLastInvId);
					elmA->put_href((BSTR)szTxt);
				}

				SysFreeString(str);
			}

			elmA->Release();
		}
	}

	return str;
}

void GEventUIHandler_Inventory::_SynchronizedInvId(IWebBrowser2 *wb2)
{
	BSTR str;
	GameLink *gl;
	TCHAR szInvId[10];

	if (wb2)
	{
		wb2->get_LocationURL(&str);
		if (str)
		{
			if (ppIsContainIgnoreCase((TCHAR*)str, TEXT("mod=inventory"), -1))
			{
				szInvId[0]=NULL;
				gl=new GameLink(wb2);
				gl->UpdateValue();
				gl->ParseQuery(TEXT("inv"), szInvId, 10);
				delete gl;

				ppParseToNumber(szInvId, NULL, NULL, 1, &this->m_nLastInvId);
			}

			SysFreeString(str);
		}
	}
}

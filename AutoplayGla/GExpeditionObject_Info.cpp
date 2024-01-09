#include "GExpeditionObject_Info.h"
#include "BrowserUtility.h"
#include "PXPath.h"
#include "PParser.h"


GExpeditionObject_Info::GExpeditionObject_Info()
{
	this->m_bValid=FALSE;
}

void GExpeditionObject_Info::Synchronized( IWebBrowser2 *wb2 )
{
	this->m_bValid=TRUE;
	this->_ParseInfo(wb2);
}

void GExpeditionObject_Info::_ParseInfo( IWebBrowser2 *wb2 )
{
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *nodeRoot, *nodeChild, *nodeTmp;

	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		nodeRoot=BrowserUtility::GetDomNodeById(wb2, TEXT("submenu2"));
		if (nodeRoot)
		{
			nodeRoot->get_firstChild(&nodeChild);
			while (nodeChild)
			{
				if (this->_IsExpeditionInfo(nodeChild))
				{

				}

				nodeChild->get_nextSibling(&nodeTmp);
				nodeChild->Release();
				nodeChild=nodeTmp;
			}

			nodeRoot->Release();
		}

		doc3->Release();
	}
}

BOOL GExpeditionObject_Info::_IsExpeditionInfo( IHTMLDOMNode *node )
{
	BOOL brs;
	IHTMLAnchorElement *elmA;
	BSTR url;

	brs=FALSE;
	if (node)
	{
		node->QueryInterface(IID_IHTMLAnchorElement, (void**)&elmA);
		if (elmA)
		{
			elmA->get_href(&url);
			if (url)
			{
				brs=ppIsContainIgnoreCase(url, TEXT("mod=location"), -1);
				SysFreeString(url);
			}

			elmA->Release();
		}
	}

	return brs;
}

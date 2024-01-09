#include "GItemObject_Shop.h"
#include "BrowserUtility.h"
#include "PXPath.h"


GItemObject_Shop::GItemObject_Shop()
{
	for (int i=0; i<SHOP_HEIGHT; i++)
		for (int j=0; j<SHOP_WIDTH; j++)
			this->m_items[i][j].SetActive(FALSE);
}

void GItemObject_Shop::Synchronized( IWebBrowser2 *wb2 )
{
	IHTMLDOMNode *nodeRoot;
	IHTMLElement *elm;
	IHTMLDOMNode *nodeItem, *nodeTmp;
	IHTMLDocument3 *doc3;
	int i, j;

	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		//Get list item node
		doc3->getElementById(TEXT("shop"), &elm);
		nodeRoot=NULL;
		if (elm)
		{
			elm->QueryInterface(IID_IHTMLDOMNode, (void**)&nodeRoot);
			elm->Release();
		}

		//Parse item list
		if (nodeRoot)
		{
			i=0; j=0;
			nodeRoot->get_firstChild(&nodeItem);
			while (nodeItem && i<SHOP_HEIGHT && j<SHOP_WIDTH)//Force exception
			{
				if (BrowserUtility::IsTagName(nodeItem, TEXT("div")))
				{
					this->m_items[i][j].Synchronized(doc3, nodeItem);

					i++;
					if (i>=SHOP_HEIGHT)
					{
						i=0;
						j++;
					}
				}


				nodeItem->get_nextSibling(&nodeTmp);
				nodeItem->Release();
				nodeItem=nodeTmp;
			}

			nodeRoot->Release();
		}

		doc3->Release();
	}
}

IHTMLDOMNode* GItemObject_Shop::GetSlotNode( IWebBrowser2 *wb2, int nRow, int nColumn )
{
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *slot;
	IHTMLDOMNode *shop;
	TCHAR szTmp[10];

	doc3=BrowserUtility::GetDocument3(wb2);
	slot=NULL;
	if (doc3)
	{
		shop=BrowserUtility::GetDomNodeById(doc3, TEXT("shop"));
		if (shop)
		{
			wsprintf(szTmp, TEXT("div[%d]"), nRow+nColumn*SHOP_HEIGHT+1);
			slot=pxpGetXPathNode(shop, szTmp);

			shop->Release();
		}

		doc3->Release();
	}

	return slot;
}

BOOL GItemObject_Shop::IsExistItemDirect( IWebBrowser2 *wb2, int nRow, int nColumn )
{
	IHTMLDOMNode *node, *item;
	BOOL brs;

	brs=FALSE;

	node=this->GetSlotNode(wb2, nRow, nColumn);
	if (node)
	{
		item=pxpGetXPathNode(node, TEXT("img"));
		if (item)
		{
			brs=TRUE;
			item->Release();
		}

		node->Release();
	}

	return brs;
}

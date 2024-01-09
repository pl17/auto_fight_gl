#include "GItemObject_Inventory.h"
#include "BrowserUtility.h"
#include "PXPath.h"

GItemObject_Inventory::GItemObject_Inventory()
{
	for (int i=0; i<INV_HEIGHT; i++)
		for (int j=0; j<INV_WIDTH; j++)
			this->m_items[i][j].SetActive(FALSE);

	this->m_bIsValid=FALSE;
}

void GItemObject_Inventory::Synchronized( IWebBrowser2 *wb2 )
{
	IHTMLDOMNode *nodeRoot;
	IHTMLDOMNode *nodeItem, *nodeTmp;
	IHTMLDocument3 *doc3;
	int i, j;
	
	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		//Get list item node
		nodeRoot=BrowserUtility::GetDomNodeById(doc3, TEXT("inv"));

		//Parse item list
		if (nodeRoot)
		{
			this->m_bIsValid=TRUE;

			i=0; j=0;
			nodeRoot->get_firstChild(&nodeItem);
			while (nodeItem && i<INV_HEIGHT && j<INV_WIDTH)//Force exception
			{
				if (BrowserUtility::IsTagName(nodeItem, TEXT("div")))
				{
					this->m_items[i][j].Synchronized(doc3, nodeItem);

					i++;
					if (i>=INV_HEIGHT)
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

IHTMLDOMNode* GItemObject_Inventory::GetSlotNode( IWebBrowser2 *wb2, int nRow, int nColumn )
{
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *slot;
	IHTMLDOMNode *inv;
	TCHAR szTmp[10];

	doc3=BrowserUtility::GetDocument3(wb2);
	slot=NULL;
	if (doc3)
	{
		inv=BrowserUtility::GetDomNodeById(doc3, TEXT("inv"));
		if (inv)
		{
			wsprintf(szTmp, TEXT("div[%d]"), nRow+nColumn*INV_HEIGHT+1);
			slot=pxpGetXPathNode(inv, szTmp);

			inv->Release();
		}

		doc3->Release();
	}

	return slot;
}


IHTMLDOMNode* GItemObject_Inventory::GetSlotItem( IWebBrowser2 *wb2, int nRow, int nColumn )
{
	IHTMLDOMNode *node;
	IHTMLDOMNode *item;

	node=this->GetSlotNode(wb2, nRow, nColumn);
	item=NULL;
	if (node)
	{
		item=pxpGetXPathNode(node, TEXT("img"));

		node->Release();
	}

	return item;
}

BOOL GItemObject_Inventory::IsExistItemDirect( IWebBrowser2 *wb2, int nRow, int nColumn )
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

BOOL GItemObject_Inventory::IsValid()
{
	return this->m_bIsValid;
}

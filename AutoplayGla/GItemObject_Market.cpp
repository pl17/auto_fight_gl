#include "GItemObject_Market.h"
#include "PXPath.h"
#include "BrowserUtility.h"
#include "GameObj_XPathConst.h"
#include "GameManager.h"

#include "Logs.h"

extern IOutputDebug *gv_dbgConsole;

GItemObject_Market::GItemObject_Market(GPlayerObject_Player *player)
{
	this->m_items=new ItemMarketObject[MARKET_MAXITEM]();
	this->m_nItemCount=0;
	this->m_player=player;
	this->m_nMaxGold=0;
}

GItemObject_Market::~GItemObject_Market()
{
	delete[] this->m_items;
}

void GItemObject_Market::Synchronized( IWebBrowser2 *wb2 )
{
	GameManager *gm;

	gm=new GameManager(wb2);
	if (gm->GetModId(wb2)==GAMELINK_MOD_MARKET)
	{
		this->_SynchronizedItemList(wb2);
		this->HightLightAllItem(wb2);
	}

	delete gm;
}

void GItemObject_Market::_SynchronizedItemList( IHTMLDocument3 *doc3, IHTMLDOMNode *listItems )
{
	IHTMLDOMNode *nodeTr, *nodeTd, *nodeTmp;
	IHTMLDOMNode *nodeItem;
	float cpu;
	
	cpu=0;
	this->m_nMaxGold=0;
	if (listItems)
	{
		this->m_nItemCount=0;
		listItems->get_firstChild(&nodeTr);
		while (nodeTr)
		{
			nodeTr->get_firstChild(&nodeTd);
			while (nodeTd)
			{
				nodeItem=pxpGetXPathNode(nodeTd, TEXT("div/div/form"));
				if (nodeItem)
				{
					this->m_items[this->m_nItemCount].Synchronized(doc3, nodeItem);
					nodeItem->Release();

					//Get Max gold and max 
					if (this->m_items[this->m_nItemCount].m_fCostPerUnit>cpu
						&& this->m_items[this->m_nItemCount].m_nCost==this->m_items[this->m_nItemCount].m_nValue)
					{
						cpu=this->m_items[this->m_nItemCount].m_fCostPerUnit;
						this->m_nMaxGold=this->m_items[this->m_nItemCount].m_nCost;
					}
				}

				nodeTd->get_nextSibling(&nodeTmp);
				nodeTd->Release();
				nodeTd=nodeTmp;
				this->m_nItemCount++;
			}

			nodeTr->get_nextSibling(&nodeTmp);
			nodeTr->Release();
			nodeTr=nodeTmp;
		}
	}
}

void GItemObject_Market::_SynchronizedItemList( IWebBrowser2 *wb2 )
{
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *nodeListItem;
	IDispatch *disDoc;

	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		nodeListItem=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_LISTITEMMARKET);
		if (nodeListItem)
		{
			this->_SynchronizedItemList(doc3, nodeListItem);
			nodeListItem->Release();
		}

		doc3->Release();
	}
}

IHTMLDOMNode* GItemObject_Market::_GetRootListItem( IWebBrowser2 *wb2 )
{
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *nodeListItem;
	IDispatch *disDoc;

	nodeListItem=NULL;
	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		nodeListItem=pxpGetXPathNode(doc3, &GameObj_XPathConst::CONT_LISTITEMMARKET);
		doc3->Release();
	}

	return nodeListItem;
}

void GItemObject_Market::HightLightAllItem( IWebBrowser2 *wb2 )
{
	IHTMLDOMNode *listItem;
	IHTMLDOMNode *item;

	listItem=this->_GetRootListItem(wb2);
	if (listItem)
	{
		for (int i=0; i<this->m_nItemCount; i++)
		{
			item=this->_GetItem(listItem, i);
			if (item)
			{
				this->_HightLightItem(item, i);
				this->_HightLightBuyable(item, i);

				item->Release();
			}
		}

		listItem->Release();
	}
}

BOOL GItemObject_Market::BidItem( IWebBrowser2 *wb2 )
{
	int index;
	int i;
	IHTMLDOMNode *rootList;
	IHTMLDOMNode *item, *buttonBid;
	BOOL brs;
	float cpu;

	index=-1;
	brs=FALSE;
	cpu=0;
	for (i=0; i<this->m_nItemCount; i++)
	{
		if (this->m_items[i].m_nCost==this->m_items[i].m_nValue
			&& this->m_items[i].m_nCost<=this->m_player->GetGold()
			&& cpu<this->m_items[i].m_fCostPerUnit)
		{
			/*if (index<0) 
			{
				index=i;
				cpu=this->m_items[i].m_fCostPerUnit;
			}
			else if (this->m_items[i].m_nCost>this->m_items[index].m_nCost)
			{
				index=i;
				cpu=this->m_items[i].m_fCostPerUnit;
			}*/
			index=i;
			cpu=this->m_items[i].m_fCostPerUnit;
		}
	}

	if (index>=0 && this->m_items[index].m_nCost<=this->m_player->GetGold())
	{
		rootList=this->_GetRootListItem(wb2);
		if (rootList)
		{
			item=this->_GetItem(rootList, index);
			if (item)
			{
				buttonBid=pxpGetXPathNode(item, TEXT("div[2]/input[2]"));
				if (buttonBid)
				{
					LogWriteLine(gv_dbgConsole, TEXT("Bid Item: %s [%d Gold](%d)")
						, this->m_items[index].m_bstrName
						, this->m_items[index].m_nCost
						, (int)this->m_items[index].m_fCostPerUnit);

					BrowserUtility::Simulator(buttonBid);
					buttonBid->Release();
				}

				item->Release();
			}
			rootList->Release();
		}
	}

	return brs;
}

IHTMLDOMNode* GItemObject_Market::_GetItem( IHTMLDOMNode *listItem, int nIndex )
{
	IHTMLDOMNode *nodeItem;
	TCHAR szTxt[50];
	
	nodeItem=NULL;
	if (listItem)
	{
		wsprintf(szTxt, TEXT("tr[%d]/td[%d]/div/div/form"), nIndex/2+1, nIndex%2+1);
		nodeItem=pxpGetXPathNode(listItem, szTxt);
	}

	return nodeItem;
}

void GItemObject_Market::_HightLightItem( IHTMLDOMNode *item, int nIndex )
{
	IHTMLDOMNode *node;

	if (item)
	{
		node=pxpGetXPathNode(item, TEXT("div/div/div"));
		if (node)
		{
			BrowserUtility::SetNodeStyleSize(node, 64, 96);
			BrowserUtility::SetNodeStyleBkColorARGB(node, this->m_items[nIndex].m_nNameColor, 0x32);
			node->Release();
		}
	}
}

void GItemObject_Market::_HightLightBuyable( IHTMLDOMNode *item, int nIndex )
{
	IHTMLDOMNode *node;

	if (item)
	{
		node=pxpGetXPathNode(item, TEXT("div[2]/input[2]"));//Button bid
		if (node)
		{
			if (this->m_player && this->m_player->GetGold()>=this->m_items[nIndex].m_nCost)
			{
				BrowserUtility::SetNodeTextColor(node, 0x006600);
			}
			else
			{
				BrowserUtility::SetNodeTextColor(node, 0x660000);
			}
			node->Release();
		}

		node=pxpGetXPathNode(item, TEXT("div[2]/input[1]"));//text bid
		if (node)
		{
			if (this->m_items[nIndex].m_nCost<=this->m_items[nIndex].m_nValue)
			{
				BrowserUtility::SetNodeStyleBkColorRGB(node, 0xffcc66);
			}
			node->Release();
		}
	}
}

int GItemObject_Market::GetMaxGold()
{
	return this->m_nMaxGold;
}

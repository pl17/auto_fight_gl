#pragma once

#include "ItemMarketObject.h"
#include "GameObject_Base.h"
#include "GPlayerObject_Player.h"

#define MARKET_MAXITEM	1000

class GItemObject_Market :
	public GameObject_Base
{
public:
	GItemObject_Market(GPlayerObject_Player *player);
	~GItemObject_Market();

	//Implement virtual method
	void Synchronized( IWebBrowser2 *wb2 );

	//Local method
	void HightLightAllItem(IWebBrowser2 *wb2);
	BOOL BidItem(IWebBrowser2 *wb2);
	int GetMaxGold();
private:
	ItemMarketObject *m_items;
	int m_nItemCount;
	int m_nMaxGold;
	GPlayerObject_Player *m_player;

	void _SynchronizedItemList(IHTMLDocument3 *doc3, IHTMLDOMNode *listItems);
	void _SynchronizedItemList(IWebBrowser2 *wb2);

	IHTMLDOMNode* _GetRootListItem(IWebBrowser2 *wb2);
	IHTMLDOMNode* _GetItem(IHTMLDOMNode *listItem, int nIndex);
	void _HightLightItem(IHTMLDOMNode *item, int nIndex);
	void _HightLightBuyable(IHTMLDOMNode *item, int nIndex);
};
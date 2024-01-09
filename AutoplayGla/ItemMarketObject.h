#pragma once

#include <MsHTML.h>
#include "ItemObject.h"

/*
ItemMarket node start with form element
*/
class ItemMarketObject :
	public ItemObject
{
public:
	ItemMarketObject();
	void Synchronized(IHTMLDocument3 *doc3, IHTMLDOMNode *marketitem);

//private:
	int m_nCost;
	BOOL m_bCost;

	int m_nHeight;
	int m_nWidth;
	float m_fCostPerUnit;

	void _SynchronizedCost(IHTMLDOMNode *marketitem);
	void _SynchronizedCostPerUnit(IHTMLDOMNode *marketitem);
	void _SynchronizedItemInfo(IHTMLDocument3 *doc3, IHTMLDOMNode *marketitem);
	BOOL _IsNodeBidGold(IHTMLDOMNode *node);
};
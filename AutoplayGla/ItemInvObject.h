#pragma once

#include "ItemObject.h"
#include <MsHTML.h>

enum ITEMTYPE
{
	ITEMTYPE_WEAR,
	ITEMTYPE_FOOD,
	ITEMTYPE_UNKNOWN
};

class ItemInvObject :
	public ItemObject
{
public:
	ItemInvObject();
	void Synchronized(IHTMLDocument3 *doc3, IHTMLDOMNode *invitem);

	void SetActive(BOOL bActive);
	BOOL GetActive();
//private:
	int m_nHeight;
	int m_nWidth;
	BOOL m_bActive;
	ITEMTYPE m_enType;

	void _SynchronizedItemInfo(IHTMLDocument3 *doc3, IHTMLDOMNode *invitem);
	void _SynchronizedItemSize(IHTMLDOMNode *invitem);
	void _SynchronizedItemType(IHTMLImgElement *item);
};
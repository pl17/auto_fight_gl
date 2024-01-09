#include "GItemObject_ShopInv.h"
#include "ActionSimulator.h"
#include "PXPath.h"


GItemObject_ShopInv::GItemObject_ShopInv( GItemObject_Shop *itemShop, GItemObject_Inventory *itemInv, GPlayerObject_Player *player )
{
	this->m_itemInv=itemInv;
	this->m_itemShop=itemShop;
	this->m_player=player;
}

BOOL GItemObject_ShopInv::CanAction()
{
	BOOL brs;

	brs=FALSE;


	return brs;
}

BOOL GItemObject_ShopInv::TryAction()
{
	BOOL brs;

	brs=FALSE;

	return brs;
}

void GItemObject_ShopInv::Synchronized( IWebBrowser2 *wb2 )
{
	if (this->m_itemInv)
		this->m_itemInv->Synchronized(wb2);
	if (this->m_itemShop)
		this->m_itemShop->Synchronized(wb2);
}

BOOL GItemObject_ShopInv::SellItem( IWebBrowser2 *wb2, int nInvRow, int nInvColumn, int nShopRow, int nShopColumn )
{
	IHTMLDOMNode *nodeShop;
	IHTMLDOMNode *nodeInv;
	IHTMLDOMNode *nodeItem;
	BOOL brs;

	nodeShop=this->m_itemShop->GetSlotNode(wb2, nShopRow, nShopColumn);
	nodeInv=this->m_itemInv->GetSlotNode(wb2, nInvRow, nInvColumn);
	nodeItem=pxpGetXPathNode(nodeInv, TEXT("img"));

	brs=ActionSimulator::MouseFromTo(nodeItem, 5, 5, nodeShop, 5, 5);

	if (nodeShop) nodeShop->Release();
	if (nodeInv) nodeInv->Release();
	if (nodeItem) nodeItem->Release();

	return brs;
}

BOOL GItemObject_ShopInv::BuyItem( IWebBrowser2 *wb2, int nInvRow, int nInvColumn, int nShopRow, int nShopColumn )
{
	IHTMLDOMNode *nodeShop;
	IHTMLDOMNode *nodeInv;
	IHTMLDOMNode *nodeItem;
	BOOL brs;

	nodeShop=this->m_itemShop->GetSlotNode(wb2, nShopRow, nShopColumn);
	nodeInv=this->m_itemInv->GetSlotNode(wb2, nInvRow, nInvColumn);
	nodeItem=pxpGetXPathNode(nodeShop, TEXT("img"));

	brs=ActionSimulator::MouseFromTo(nodeItem, 5, 5, nodeInv, 5, 5);

	if (nodeShop) nodeShop->Release();
	if (nodeInv) nodeInv->Release();
	return brs;
}

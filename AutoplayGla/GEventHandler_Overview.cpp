#include "GEventHandler_Overview.h"
#include "BrowserUtility.h"
#include "ActionSimulator.h"
#include "Logs.h"

extern IOutputDebug *gv_dbgConsole;


GEventHandler_Overview::GEventHandler_Overview( IWebBrowser2 *wb2, IGameMod *gmod, GPlayerObject_Player *player, GItemObject_Inventory *inventory )
:GEventHandler_Base(wb2, gmod, NULL)
{
	this->m_player=player;
	this->m_inventory=inventory;
}

BOOL GEventHandler_Overview::_CanHandler()
{
	BOOL brs;
	int i, j;

	brs=FALSE;
	if (this->m_player && this->m_inventory)
	{
		if (this->m_player->GetHpCurrent()*100/this->m_player->GetHpMax()<50)//<50%
		{
			brs=this->_FindFood(NULL, NULL);

			if (brs)
				LogWriteLine(gv_dbgConsole, TEXT("Overview: Food found"));
		}
	}

	return brs;
}

BOOL GEventHandler_Overview::_OnHandler()
{
	BOOL brs;
	int i, j;
	IHTMLDOMNode *item, *player;

	brs=this->_FindFood(&i, &j);
	if (brs)
	{
		item=this->m_inventory->GetSlotItem(this->m_wb2, i, j);
		player=BrowserUtility::GetDomNodeById(this->m_wb2, TEXT("p8_1_1"));

		if (item && player)
			brs=ActionSimulator::MouseFromTo(item, 5, 5, player, 5, 5);

		if (brs) 
			LogWriteLine(gv_dbgConsole, TEXT("Overview: Use food: %s (%d)")
			, this->m_inventory->m_items[i][j].m_bstrName
			, this->m_inventory->m_items[i][j].m_nHeal);

		if (item) item->Release();
		if (player) player->Release();
	}

	return brs;

	/*for (i=0; i<INV_HEIGHT; i++)
	{
		for (j=0; j<INV_WIDTH; j++)
		{
			if (this->m_inventory->m_items[i][j].m_bActive
				&& this->m_inventory->m_items[i][j].m_enType==ITEMTYPE_FOOD
				&& !this->m_inventory->m_items[i][j].m_bSpecialUse
				&& this->m_inventory->m_items[i][j].m_nHeal+this->m_player->GetHpCurrent()<this->m_player->GetHpMax())
			{
				item=this->m_inventory->GetSlotItem(this->m_wb2, i, j);
				player=BrowserUtility::GetDomNodeById(this->m_wb2, TEXT("p8_1_1"));

				if (item && player)
					brs=ActionSimulator::MouseFromTo(item, 5, 5, player, 5, 5);
				if (item) item->Release();
				if (player) player->Release();
				
				break;
			}
		}
	}*/

	//return brs;
}

BOOL GEventHandler_Overview::_OnProcessingHandler()
{
	if (this->m_player) this->m_player->Synchronized(this->m_wb2);

	this->m_status=EVENT_STATUS_FINISHED;

	return TRUE;
}

BOOL GEventHandler_Overview::_OnFinishedHandler()
{
	return TRUE;
}

void GEventHandler_Overview::_OnSynchronized( IWebBrowser2 *wb2 )
{
	//if (this->m_player)
	//	this->m_player->Synchronized(wb2);

	if (this->m_inventory)
		this->m_inventory->Synchronized(wb2);	
}

BOOL GEventHandler_Overview::_FindFood( int *nRow, int *nColumn )
{
	int i, j;

	if (this->m_inventory && this->m_inventory->IsValid())
	{
		for (i=0; i<INV_HEIGHT; i++)
		{
			for (j=0; j<INV_WIDTH; j++)
			{
				if (this->m_inventory->m_items[i][j].m_bActive
					&& this->m_inventory->m_items[i][j].m_enType==ITEMTYPE_FOOD
					&& !this->m_inventory->m_items[i][j].m_bSpecialUse
					&& this->m_inventory->m_items[i][j].m_nHeal+this->m_player->GetHpCurrent()<this->m_player->GetHpMax())
				{
					if (nRow && nColumn)
					{
						*nRow=i;
						*nColumn=j;
					}
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}


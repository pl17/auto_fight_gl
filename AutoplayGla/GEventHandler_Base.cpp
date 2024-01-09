#include "GEventHandler_Base.h"
#include "Logs.h"

extern IOutputDebug *gv_dbgConsole;

/*
return TRUE:	event handled
return FALSE:	event need handled
*/
BOOL GEventHandler_Base::_Handler()
{
	BOOL brs;
	VARIANT_BOOL vb;
	HRESULT hr;

	hr=this->m_wb2->get_Busy(&vb);
	if (hr==S_OK && vb==VARIANT_TRUE)//Check browser busy
		return FALSE;

	if (!this->_CanHandler() && this->m_status==EVENT_STATUS_FREE)
		return TRUE;

	brs=FALSE;
	if (this->m_gmMod)
	{
		if (this->m_status==EVENT_STATUS_FREE)
		{
			if (this->m_gmMod->Go(this->m_wb2))//Finished Goto mod
			//{
				//this->m_gm->GotoMod(this->m_wb2, this->m_nModId, 0);
			//}
			//else
			{
				if (this->_OnHandler())
				{
					this->m_status=EVENT_STATUS_PROCESSING;
					this->m_nTimeoutCooldown=0;
					LogWriteLine(gv_dbgConsole, TEXT("Event: Handler"));
				}
			}
		}
		else if (this->m_status==EVENT_STATUS_PROCESSING)
		{
			this->m_nTimeoutCooldown++;
			LogWriteLine(gv_dbgConsole, TEXT("Event: Processing %d"), this->m_nTimeoutCooldown);
			if (this->m_nTimeoutCooldown>30)
			{
				LogWriteLine(gv_dbgConsole, TEXT("Event: Timeout"));
				brs=TRUE;
			}
			
			if (!this->_OnProcessingHandler())
			{
				this->m_status=EVENT_STATUS_FREE;
				LogWriteLine(gv_dbgConsole, TEXT("Event: Processing Faild"));
			}
		}
		else if (this->m_status==EVENT_STATUS_FINISHED)//Finished handler
		{
			if (this->_OnFinishedHandler())
			{
				LogWriteLine(gv_dbgConsole, TEXT("Event: Finished"));
				this->m_status=EVENT_STATUS_FREE;
				brs=TRUE;
			}
			else
			{
				this->m_status=EVENT_STATUS_FREE;
			}
		}
	}
	

	return brs;
}

BOOL GEventHandler_Base::_CanHandler()
{
	return TRUE;
}

GEventHandler_Base::GEventHandler_Base( IWebBrowser2 *wb2, IGameMod *gmod, IGameObject *objMain )
{
	this->m_wb2=wb2;
	this->m_status=EVENT_STATUS_FREE;
	this->m_bEventFire=FALSE;
	this->m_bAutoHandle=FALSE;
	this->m_gmMod=gmod;
	this->m_objMain=objMain;
}


BOOL GEventHandler_Base::_OnHandler()
{
	return TRUE;
}

void GEventHandler_Base::Synchronized(IWebBrowser2 *wb2)
{
	this->_OnSynchronized(wb2);

	if (this->m_status==EVENT_STATUS_PROCESSING)
	{
		this->m_status=EVENT_STATUS_FINISHED;
	}

	this->_OnAfterSynchronized(wb2);
}

BOOL GEventHandler_Base::_OnProcessingHandler()
{
	return TRUE;
}

BOOL GEventHandler_Base::_OnFinishedHandler()
{
	return TRUE;
}

void GEventHandler_Base::OnCoolDown( int nCooldown)
{
	if (this->m_objMain)
	{
		if (this->m_objMain->OnCooldown(nCooldown)==IGameObject::STATUS_ZERO)
		{
			this->m_bEventFire=TRUE;
		}
	}
}

void GEventHandler_Base::FireEvent()
{
	this->m_bEventFire=TRUE;
}

BOOL GEventHandler_Base::RunEvent()
{
	BOOL brs;

	brs=TRUE;

	if (this->m_bEventFire)
	{
		if (this->_Handler())
		{
			this->m_bEventFire=FALSE;
		}
		else
			brs=FALSE;
	}

	return brs;
}

void GEventHandler_Base::SetCooldown( int nCooldown )
{
	if (this->m_objMain)
	{
		this->m_objMain->SetCooldown(nCooldown);
		if (this->m_objMain->GetCooldown()==0)
		{
			this->FireEvent();
		}
	}
}

int GEventHandler_Base::GetCooldown()
{
	if (this->m_objMain)
		return this->m_objMain->GetCooldown();

	return 0;
}

void GEventHandler_Base::SetAutoHandler( BOOL bAutoHandler )
{
	this->m_bAutoHandle=bAutoHandler;
	if (bAutoHandler)
		this->m_bEventFire=TRUE;
}

BOOL GEventHandler_Base::GetAutoHandler()
{
	return this->m_bAutoHandle;
}

void GEventHandler_Base::_OnAfterSynchronized( IWebBrowser2 *wb2 )
{
	return;
}

void GEventHandler_Base::_OnSynchronized( IWebBrowser2 *wb2 )
{
 	if (this->m_objMain)
 		this->m_objMain->Synchronized(wb2);
	return;
}



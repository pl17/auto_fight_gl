#include "GEventUIHandler_Base.h"

BOOL GEventUIHandler_Base::Handler()
{
	return TRUE;
}

void GEventUIHandler_Base::OnCoolDown( int nMinisecond )
{
	return;
}

void GEventUIHandler_Base::SetCooldown( int nCooldown )
{
	return;
}

int GEventUIHandler_Base::GetCooldown()
{
	return 0;
}

BOOL GEventUIHandler_Base::CheckEvent()
{
	return FALSE;
}

void GEventUIHandler_Base::FireEvent()
{
	return;
}

void GEventUIHandler_Base::SetCanHandler( BOOL bCanHandler )
{
}

BOOL GEventUIHandler_Base::GetCanHandler()
{
	return FALSE;
}

void GEventUIHandler_Base::AfterSynchronized( IWebBrowser2 *wb2 )
{
	return;
}

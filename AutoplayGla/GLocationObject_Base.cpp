#include "GLocationObject_Base.h"
#include "GameLink.h"
#include "BrowserUtility.h"

GLocationObject_Base::GLocationObject_Base( int nModId )
{
	this->m_nModId=nModId;

	this->m_nCurrentPoint=0;
	this->m_nMaxPoint=0;
}

void GLocationObject_Base::Synchronized( IWebBrowser2 *wb2 )
{
	const GAMEOBJ_XPATH *xpPoint, *xpCooldown;
	int h, m, s;
	int nInitedValue;
	
	xpPoint=NULL;
	xpCooldown=NULL;

	switch(this->m_nModId)
	{
	case GAMELINK_MOD_LOCATION:
		xpPoint=&GameObj_XPathConst::HEADER_LOCATION_POINT;
		xpCooldown=&GameObj_XPathConst::HEADER_LOCATION_COOLDOWN;
		break;
	case GAMELINK_MOD_DUNGEON:
		xpPoint=&GameObj_XPathConst::HEADER_DUNGEON_POINT;
		xpCooldown=&GameObj_XPathConst::HEADER_DUNGEON_COOLDOWN;
		break;
	}

	if (xpCooldown && xpPoint)
	{
		BrowserUtility::ParseFromXpath(wb2, xpPoint, TEXT("/"), NULL, 2, &nInitedValue, &this->m_nCurrentPoint, &this->m_nMaxPoint);
		if (BrowserUtility::ParseFromXpath(wb2, xpCooldown, TEXT(":"), NULL, 3, &nInitedValue, &h, &m, &s))
		{
			this->_SynchronizedCooldown();
			if (nInitedValue!=3)
			{
				this->SetCooldown(0);
			}
			else
			{
				this->SetCooldown((h*60+m)*60+s);
			}
		}
	}
}

int GLocationObject_Base::GetCurrentPoint()
{
	return this->m_nCurrentPoint;
}

int GLocationObject_Base::GetMaxPoint()
{
	return this->m_nMaxPoint;
}


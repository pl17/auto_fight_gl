#include "GArenaObject_Base.h"
#include "GameLink.h"
#include "GameObj_XPathConst.h"
#include "BrowserUtility.h"


GArenaObject_Base::GArenaObject_Base( int nModId )
{
	this->m_nModId=nModId;
	this->m_nRank=0;
}

void GArenaObject_Base::Synchronized( IWebBrowser2 *wb2 )
{
	const GAMEOBJ_XPATH *xpathCooldown;
	const GAMEOBJ_XPATH *xpathRank;
	BOOL bFound;
	int nInitedValue;
	BOOL brs;
	int h, m, s;


	xpathRank=NULL;
	xpathCooldown=NULL;

	switch (this->m_nModId)
	{
	case GAMELINK_MOD_ARENA:
		xpathCooldown=&GameObj_XPathConst::HEADER_ARENA_COOLDOWN;
		xpathRank=&GameObj_XPathConst::HEADER_ARENA_RANK;
		bFound=TRUE;
		break;
	case GAMELINK_MOD_TURMA:
		xpathCooldown=&GameObj_XPathConst::HEADER_TURMA_COOLDOWN;
		xpathRank=&GameObj_XPathConst::HEADER_TURMA_RANK;
		break;
	}

	if (xpathRank && xpathCooldown)
	{
		if (BrowserUtility::ParseFromXpath(wb2, xpathCooldown, TEXT(":"), NULL, 3, &nInitedValue, &h, &m, &s))
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

		BrowserUtility::ParseFromXpath(wb2, xpathRank, NULL, NULL, 1, &nInitedValue, &this->m_nRank);
		if (nInitedValue!=1)
			this->m_nRank=0;
	}
}

int GArenaObject_Base::GetRank()
{
	return this->m_nRank;
}

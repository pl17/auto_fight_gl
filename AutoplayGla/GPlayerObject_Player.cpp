#include "GPlayerObject_Player.h"
#include "BrowserUtility.h"

GPlayerObject_Player::GPlayerObject_Player()
{
	this->m_nGold=0;
	this->m_nRubi=0;
	this->m_nLevel=0;
	this->m_nRank=0;
	this->m_nHpCurrent=0;
	this->m_nHpMax=0;
	this->m_nExpCurrent=0;
	this->m_nExpMax=0;
}

void GPlayerObject_Player::Synchronized( IWebBrowser2 *wb2 )
{
	int nInitedValue;

	//Synchronize Gold
	BrowserUtility::ParseFromXpath(wb2, &GameObj_XPathConst::HEADER_GOLD, NULL, TEXT("."), 1, &nInitedValue, &this->m_nGold);

	//Synchronize Rubi
	BrowserUtility::ParseFromXpath(wb2, &GameObj_XPathConst::HEADER_RUBI, NULL, TEXT("."), 1, &nInitedValue, &this->m_nRubi);

	//Synchronize Level
	BrowserUtility::ParseFromXpath(wb2, &GameObj_XPathConst::HEADER_LEVEL, NULL, TEXT("."), 1, &nInitedValue, &this->m_nLevel);

	//Synchronize Rank
	BrowserUtility::ParseFromXpath(wb2, &GameObj_XPathConst::HEADER_RANK, NULL, TEXT("."), 1, &nInitedValue, &this->m_nRank);

	//Synchronize Hp
	BrowserUtility::ParseFromXpath(wb2, &GameObj_XPathConst::HEADER_HP, TEXT("/"), NULL, 2, &nInitedValue, &this->m_nHpCurrent, &this->m_nHpMax);

	//Synchronize Exp
	BrowserUtility::ParseFromXpath(wb2, &GameObj_XPathConst::HEADER_EXP, TEXT("/"), NULL, 2, &nInitedValue, &this->m_nExpCurrent, &this->m_nExpMax);
}

int GPlayerObject_Player::GetLevel()
{
	return this->m_nLevel;
}

int GPlayerObject_Player::GetRank()
{
	return this->m_nRank;
}

int GPlayerObject_Player::GetRubi()
{
	return this->m_nRubi;
}

int GPlayerObject_Player::GetGold()
{
	return this->m_nGold;
}

int GPlayerObject_Player::GetHpCurrent()
{
	return this->m_nHpCurrent;
}

int GPlayerObject_Player::GetHpMax()
{
	return this->m_nHpMax;
}

int GPlayerObject_Player::GetExpCurrent()
{
	return this->m_nExpCurrent;
}

int GPlayerObject_Player::GetExpMax()
{
	return this->m_nExpMax;
}


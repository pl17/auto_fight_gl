#pragma once

#include <ExDisp.h>

enum ITEMTYPE
{
	ITEMTYPE_FOOD_NORMAL,
	ITEMTYPE_FOOD_SPECIAL,

	ITEMTYPE_WEAR_AMOR,
	ITEMTYPE_WEAR_SHOES,
	ITEMTYPE_WEAR_WEAPON,
	ITEMTYPE_WEAR_SHIELD,
	ITEMTYPE_WEAR_PEDANT,
	ITEMTYPE_WEAR_RING,
	ITEMTYPE_WEAR_HEAD,
	ITEMTYPE_WEAR_GLOVES,
	ITEMTYPE_WEAR_UNKNOWN,

	ITEMTYPE_UNKNOWN
};

class GItemObject_Base
{
public:
	
private:
	//Tooltip
	BSTR m_strName;
	int m_nNameColor;
	int m_nValue;
	int m_nLevel;

	ITEMTYPE m_enType;
};
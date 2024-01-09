#pragma once

#include "GItemObject_Inventory.h"

class GEventHandler_Inventory
{
public:
	GEventHandler_Inventory(GItemObject_Inventory *inv);
	~GEventHandler_Inventory();

private:
	GItemObject_Inventory m_inventory;
};
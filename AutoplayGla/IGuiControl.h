#pragma once

#include <Windows.h>

class IGuiControl
{
public:
	virtual void OnDraw(HWND hParent, HDC hdc)=NULL;
};
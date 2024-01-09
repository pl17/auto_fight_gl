#pragma once

#include "IGuiControl.h"

class GTextBox : 
	public IGuiControl
{
public:
	GTextBox();
	GTextBox(TCHAR *lpszText);

	//Implement IGuiControl interface
	void OnDraw(HWND hParent, HDC hdc);

	//Local method
	void SetPosition(int left, int top);
	void SetSize(int width, int height);

	void SetText(const TCHAR *szText);
	const TCHAR* GetText();


private:
	//Boxing
	RECT m_rcBox;
	RECT m_rcPadding;
	RECT m_rcMargin;

	//Border
	RECT m_rcBorder;
	int m_nBorderWidth;
	COLORREF m_clBorderColor;

	//Text
	TCHAR *m_lpszText;
	int m_nTextLen;

	//Color
	COLORREF m_clBackground;
	COLORREF m_clTextColor;
};
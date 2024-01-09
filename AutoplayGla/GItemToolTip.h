#pragma once

#include <ExDisp.h>
#include <MsHTML.h>

class GItemToolTip
{
public:
	GItemToolTip();
	~GItemToolTip();

	void Synchronized(IHTMLDOMNode *tooltip);

	BOOL IsValidated();
private:
	BSTR m_strName;
	int m_nNameColor;
	int m_nLevel;
	int m_nValue;
	BOOL m_bSoulBound;
	BOOL m_bValidated;
};
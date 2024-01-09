#pragma once

#include <MsHTML.h>
#include <ExDisp.h>

class ItemObject
{
public:
	ItemObject();

	void Synchronized(IHTMLDOMNode *node);

//protected:
	BSTR m_bstrName;
	int m_nNameColor;
	int m_nValue;
	BOOL m_bValue;
	int m_nType;
	int m_nLevel;	
	BOOL m_bSouldBound;
	BOOL m_bSpecialUse;
	BOOL m_bNormalUse;
	int m_nHeal;

protected:
	void _ParseAttribute(IHTMLDOMNode *attribute);
	void _ParseName(IHTMLDOMNode *item);
	void _ParseNameColor(IHTMLDOMNode *item);
	void _ParseCost(IHTMLDOMNode *item);
	void _ParseLevel(IHTMLDOMNode *item);
	void _ParseItem(IHTMLDOMNode *item);

	BOOL _IsAttributeCost(IHTMLDOMNode *attribute);
	BOOL _IsAttributeLevel(IHTMLDOMNode *attribute);
	BOOL _IsAttributeName(IHTMLDOMNode *attribute);
	BOOL _IsAttributeSoulBound(IHTMLDOMNode *attribute);
	BOOL _IsAttributeSpecialUse(IHTMLDOMNode *attribute);
	BOOL _IsAttributeNormalUse(IHTMLDOMNode *attribute);
};
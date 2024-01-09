#pragma once

#include <ExDisp.h>
#include <MsHTML.h>

class GameItem
{
public:
	GameItem(IHTMLDocument3 *doc3, const TCHAR *lpszId);
	~GameItem();
//private:
	typedef struct _ITEMATTRIBUTE
	{
		BSTR strAttribute;
		int nType;
		int nColor;
		struct _ITEMATTRIBUTE *next;
	} ITEMATTRIBUTE;

	BOOL m_bValidated;
	int m_nGold;
	BOOL m_bGoldValid;
	TCHAR *m_lpszName;
	int m_nNameColor;

	//ITEMATTRIBUTE m_listAttribute;

	IHTMLDOMNode* _GetAttributeRoot(IHTMLDocument3 *doc3, const TCHAR *lpszId);
	void _GetListAttribute(IHTMLDOMNode *node);
	BOOL _IsAttributeGold(IHTMLDOMNode *parent);
};
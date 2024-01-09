#include "ItemObject.h"
#include "BrowserUtility.h"
#include "PParser.h"
#include "PXPath.h"

ItemObject::ItemObject()
{
	this->m_bstrName=NULL;
	this->m_bSouldBound=FALSE;
	this->m_bSpecialUse=FALSE;
	this->m_bNormalUse=FALSE;
}

void ItemObject::Synchronized( IHTMLDOMNode *node )
{
	this->_ParseItem(node);
}

void ItemObject::_ParseAttribute( IHTMLDOMNode *attribute )
{
	IHTMLDOMNode *nodeTr, *nodeTd, *nodeTmp;
	int nCount;

	nCount=0;
	this->m_bSouldBound=FALSE;
	this->m_bSpecialUse=FALSE;
	this->m_bNormalUse=FALSE;
	if (attribute)
	{
		attribute->get_firstChild(&nodeTr);
		while (nodeTr)
		{
			nodeTr->get_firstChild(&nodeTd);
			if (nodeTd)
			{
				//Parse attribute

				if (nCount==0)//Item's Name
				{
					this->_ParseName(nodeTd);
					this->_ParseNameColor(nodeTd);
				}
				else if (this->_IsAttributeCost(nodeTd))//Gold
				{
					this->_ParseCost(nodeTd);
				}
				else if (this->_IsAttributeSoulBound(nodeTd))//Soulbound
				{
					this->m_bSouldBound=TRUE;
				}
				else if (this->_IsAttributeSpecialUse(nodeTd))//Check special use
				{
					this->m_bSpecialUse=TRUE;
				}
				else if (this->_IsAttributeNormalUse(nodeTd))//Check normal use
				{
					this->m_bNormalUse=TRUE;
				}

				nodeTd->Release();
			}

			nodeTr->get_nextSibling(&nodeTmp);
			nodeTr->Release();
			nodeTr=nodeTmp;
			nCount++;
		}
	}
}

void ItemObject::_ParseName( IHTMLDOMNode *item )
{
	if (this->m_bstrName)
	{
		SysFreeString(this->m_bstrName);
		this->m_bstrName=NULL;
	}

	BrowserUtility::GetNodeInnerText(item, &this->m_bstrName);
}

void ItemObject::_ParseNameColor( IHTMLDOMNode *item )
{
	IHTMLElement *elm;
	IHTMLStyle *style;
	VARIANT vt;

	this->m_nNameColor=0x00FFFFFF;
	
	BrowserUtility::GetTextColor(item, &vt);
	if (vt.vt==VT_INT)
	{
		this->m_nNameColor=vt.intVal;
	}
	else if (vt.vt==VT_BSTR)
	{
		if (vt.bstrVal[0]=='#')
		{
			ppParseToNumber(vt.bstrVal+1, 16, &this->m_nNameColor);
		}
		else if (ppIsEqualIgnoreCase(vt.bstrVal, TEXT("lime"), -1))
		{
			this->m_nNameColor=0x0000FF00;
		}

		SysFreeString(vt.bstrVal);
	}
}

void ItemObject::_ParseCost( IHTMLDOMNode *item )
{
	BSTR str;
	int rs;

	if (item)
	{
		BrowserUtility::GetNodeInnerText(item, &str);
		if (str)
		{
			rs=ppParseToNumberIgnoreText(str, NULL, TEXT("."), 1, &this->m_nValue);
			if (rs==1)
				this->m_bValue=TRUE;

			SysFreeString(str);
		}
	}
}

void ItemObject::_ParseLevel( IHTMLDOMNode *item )
{

}

BOOL ItemObject::_IsAttributeCost( IHTMLDOMNode *attribute )
{
	IHTMLDOMNode *node;
	BOOL brs;
	BSTR str;

	brs=FALSE;
	if (attribute)
	{
		node=pxpGetXPathNode(attribute, TEXT("img"));
		if (node)
		{
			BrowserUtility::GetNodeTitle(node, &str);
			if (ppIsEqualIgnoreCase(str, TEXT("gold"), -1))
				brs=TRUE;
			
			node->Release();
		}
	}

	return brs;
}

BOOL ItemObject::_IsAttributeLevel( IHTMLDOMNode *attribute )
{
	return TRUE;
}

BOOL ItemObject::_IsAttributeName( IHTMLDOMNode *attribute )
{
	return TRUE;
}

void ItemObject::_ParseItem( IHTMLDOMNode *item )
{
	IHTMLDOMNode *attribute, *tmp;

	attribute=pxpGetFirstNode(item, TEXT("class"), TEXT("tooltipBox"));
	if (attribute)
	{
		tmp=pxpGetXPathNode(attribute, TEXT("tbody"));
		attribute->Release();
		attribute=tmp;

		if (attribute)
		{
			this->_ParseAttribute(attribute);
			attribute->Release();
		}
	}
}

BOOL ItemObject::_IsAttributeSoulBound( IHTMLDOMNode *attribute )
{
	BOOL brs;
	BSTR str;

	brs=FALSE;
	if (attribute)
	{
		BrowserUtility::GetNodeInnerText(attribute, &str);
		if (str)
		{
#ifdef _LANG_GERMANY
			brs=ppIsEqualIgnoreCase(str, TEXT("(seelengebunden)"), -1);
#else
			brs=ppIsEqualIgnoreCase(str, TEXT("(soul bound)"), -1);
#endif
			SysFreeString(str);
		}
	}

	return brs;
}

BOOL ItemObject::_IsAttributeSpecialUse( IHTMLDOMNode *attribute )
{
	BOOL brs;
	BSTR str;
	VARIANT vt;

	brs=FALSE;
	if (attribute)
	{
		BrowserUtility::GetNodeInnerText(attribute, &str);
		if (str)
		{
#ifdef _LANG_GERMANY
			if (ppIsContainIgnoreCase(str, TEXT("benutzen:"), -1))
#else
			if (ppIsContainIgnoreCase(str, TEXT("using:"), -1))
#endif
			{
				BrowserUtility::GetTextColor(attribute, &vt);
				if (vt.vt==VT_BSTR && vt.bstrVal)
				{
					brs=ppIsEqualIgnoreCase(vt.bstrVal, TEXT("#00b712"), -1);

					SysFreeString(vt.bstrVal);
				}
			}

			SysFreeString(str);
		}
	}

	return brs;
}

BOOL ItemObject::_IsAttributeNormalUse( IHTMLDOMNode *attribute )
{
	BOOL brs;
	BSTR str;
	VARIANT vt;

	brs=FALSE;
	if (attribute)
	{
		BrowserUtility::GetNodeInnerText(attribute, &str);
		if (str)
		{
#ifdef _LANG_GERMANY
			if (ppIsContainIgnoreCase(str, TEXT("benutzen:"), -1))
#else
			if (ppIsContainIgnoreCase(str, TEXT("using:"), -1))
#endif
			{
				BrowserUtility::GetTextColor(attribute, &vt);
				if (vt.vt==VT_BSTR && vt.bstrVal)
				{
					brs=ppIsEqualIgnoreCase(vt.bstrVal, TEXT("#ddd"), -1);
					if (ppParseToNumberIgnoreText(str, NULL, NULL, 1, &this->m_nHeal)==1)
					{
						brs=TRUE;
					}

					SysFreeString(vt.bstrVal);
				}
			}

			SysFreeString(str);
		}
	}

	return brs;
}

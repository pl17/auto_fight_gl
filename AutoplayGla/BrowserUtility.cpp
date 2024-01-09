#include "BrowserUtility.h"
#include "PParser.h"
#include "PXPath.h"

BOOL BrowserUtility::ParseFromXpath( IWebBrowser2 *wb2, const GAMEOBJ_XPATH *xpath, const TCHAR *lpszListBoundary, const TCHAR *lpszListIgnore, int nValue, int *lpnInitedValue, int *pArg, ... )
{
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *node;
	IDispatch *disDoc;
	VARIANT vt;
	BOOL brs;
	int irs;

	brs=FALSE;
	if (lpnInitedValue)
		*lpnInitedValue=0;
	
	wb2->get_Document(&disDoc);
	if (disDoc)
	{
		disDoc->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
		if (doc3)
		{
			node=pxpGetXPathNode(doc3, xpath);
			if (node)
			{
				irs=0;
				if (pxpGetNodeValue(node, &vt))
				{
					if (vt.vt==VT_BSTR)
					{
						brs=TRUE;

						irs=ppvParseToNumber((TCHAR*)vt.bstrVal, lpszListBoundary, lpszListIgnore, nValue, &pArg);
						if (lpnInitedValue)
						{
							*lpnInitedValue=irs;
						}
						SysFreeString(vt.bstrVal);
					}
				}
				node->Release();
			}

			doc3->Release();
		}
		disDoc->Release();
	}

	return brs;
}

IHTMLDocument3* BrowserUtility::GetDocument3( IWebBrowser2 *wb2 )
{
	IDispatch *dis;
	IHTMLDocument3 *doc3;

	doc3=NULL;
	if (wb2)
	{
		wb2->get_Document(&dis);
		if (dis)
		{
			dis->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
			dis->Release();
		}
	}

	return doc3;
}

BOOL BrowserUtility::Simulator( IWebBrowser2 *wb2, const GAMEOBJ_XPATH *xpath )
{
	IHTMLDocument3 *doc3;
	BOOL brs;

	brs=FALSE;
	doc3=BrowserUtility::GetDocument3(wb2);
	if (doc3)
	{
		brs=psSimulatorClick(doc3, xpath);
		doc3->Release();
	}

	return brs;
}

BOOL BrowserUtility::Simulator( IHTMLDOMNode *node )
{
	return psSimulatorClick(node);
}

BOOL BrowserUtility::IsClass( IHTMLElement *elm, const TCHAR *lpszClassName )
{
	BSTR str;
	BOOL brs;

	brs=FALSE;
	if (elm)
	{
		elm->get_className(&str);
		if (str)
		{
			brs=ppIsContainIgnoreCase((TCHAR*)str, lpszClassName, wcslen(lpszClassName));

			SysFreeString(str);
		}
	}

	return brs;
}

BOOL BrowserUtility::IsClass( IHTMLDOMNode *node, const TCHAR *lpszClassname )
{
	IHTMLElement *elm;
	BOOL brs;

	brs=FALSE;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			brs=BrowserUtility::IsClass(elm, lpszClassname);
			elm->Release();
		}
	}
	return brs;
}

void BrowserUtility::GetClass( IHTMLDOMNode *node, BSTR *str )
{
	IHTMLElement *elm;

	*str=NULL;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_className(str);

			elm->Release();
		}
	}
}

BOOL BrowserUtility::IsId( IHTMLElement *elm, const TCHAR *lpszId )
{
	BSTR str;
	BOOL brs;

	brs=FALSE;
	if (elm)
	{
		elm->get_id(&str);
		if (str)
		{
			brs=ppIsEqualIgnoreCase((TCHAR*)str, lpszId, wcslen(lpszId));
			SysFreeString(str);
		}
	}
	return brs;
}

BOOL BrowserUtility::IsId( IHTMLDOMNode *node, const TCHAR *lpszId )
{
	IHTMLElement *elm;
	BOOL brs;

	brs=FALSE;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			brs=BrowserUtility::IsId(elm, lpszId);

			elm->Release();
		}
	}

	return brs;
}

void BrowserUtility::GetId( IHTMLDOMNode *node, BSTR *str )
{
	IHTMLElement *elm;

	*str=NULL;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_id(str);

			elm->Release();
		}
	}
}

void BrowserUtility::GetBkImage( IHTMLElement *elm, BSTR *str )
{
	IHTMLStyle *style;

	*str=NULL;
	if (elm)
	{
		elm->get_style(&style);
		if (style)
		{
			style->get_backgroundImage(str);
			style->Release();
		}
	}
}

void BrowserUtility::GetBkImage( IHTMLDOMNode *node, BSTR *str )
{
	IHTMLElement *elm;

	*str=NULL;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			BrowserUtility::GetBkImage(elm, str);
			elm->Release();
		}
	}
}

void BrowserUtility::GetNodeInnerText( IHTMLDOMNode *node, BSTR *str )
{
	IHTMLElement *elm;

	*str=NULL;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_innerText(str);
			elm->Release();
		}
	}
}

void BrowserUtility::GetChildNodeInnerText( IHTMLDOMNode *node, BSTR *str )
{
	IHTMLDOMNode *child;

	*str=NULL;

	if (node)
	{
		node->get_firstChild(&child);
		BrowserUtility::GetNodeInnerText(child, str);
		child->Release();
	}
}

BOOL BrowserUtility::IsDisabled( IHTMLElement *elm )
{
	IHTMLElement3 *elm3;
	VARIANT_BOOL vb;

	vb=VARIANT_FALSE;
	if (elm)
	{
		elm->QueryInterface(IID_IHTMLElement3, (void**)&elm3);
		if (elm3)
		{
			elm3->get_disabled(&vb);
			elm3->Release();
		}
	}

	return (BOOL)vb;
}

BOOL BrowserUtility::IsDisabled( IHTMLDOMNode *node )
{
	IHTMLElement3 *elm3;
	VARIANT_BOOL vb;

	vb=VARIANT_FALSE;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement3, (void**)&elm3);
		if (elm3)
		{
			elm3->get_disabled(&vb);
			elm3->Release();
		}
	}

	return (BOOL)vb;
}

void BrowserUtility::GetNodeTitle( IHTMLDOMNode *node, BSTR *str )
{
	IHTMLElement *elm;

	*str=NULL;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_title(str);
			elm->Release();
		}
	}
}

void BrowserUtility::GetTextColor( IHTMLElement *elm, VARIANT *vt )
{
	IHTMLStyle *style;

	vt->vt=VT_UNKNOWN;

	if (elm)
	{
		elm->get_style(&style);
		if (style)
		{
			style->get_color(vt);
			style->Release();
		}
	}
}

void BrowserUtility::GetTextColor( IHTMLDOMNode *node, VARIANT *vt )
{
	IHTMLElement *elm;

	vt->vt=VT_UNKNOWN;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			BrowserUtility::GetTextColor(elm, vt);
			elm->Release();
		}
	}
}

void BrowserUtility::GetScriptOnMouseOver( IHTMLElement *elm, VARIANT *vt )
{
	VARIANT vtDis;

	vt->vt=VT_UNKNOWN;
	if (elm)
	{
		elm->get_onmouseover(&vtDis);
		if (vtDis.vt==VT_DISPATCH)
		{
			BrowserUtility::_GetScript(vtDis.pdispVal, vt);
		}
	}
}

void BrowserUtility::GetScriptOnMouseOver( IHTMLDOMNode *node, VARIANT *vt )
{
	IHTMLElement *elm;

	vt->vt=VT_UNKNOWN;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			BrowserUtility::GetScriptOnMouseOver(elm, vt);
			elm->Release();
		}
	}
}

void BrowserUtility::_GetScript( IDispatch *dis, VARIANT *vt )
{
	DISPID dispid;
	DISPPARAMS params;
	OLECHAR *szMemberName=TEXT("toString");

	vt->vt=VT_UNKNOWN;

	if (dis)
	{
		params.cArgs=0;
		params.cNamedArgs=0;
		params.rgdispidNamedArgs=NULL;
		params.rgvarg=NULL;

		dis->GetIDsOfNames(IID_NULL, &szMemberName, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
		dis->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT
			, DISPATCH_METHOD
			, &params
			, vt
			, NULL
			, NULL);
	}
}

void BrowserUtility::SetNodeStyleSize( IHTMLDOMNode *node, int width, int height )
{
	IHTMLStyle *style;
	VARIANT vt;

	style=BrowserUtility::_GetNodeStyle(node);
	if (style)
	{
		vt.vt=VT_INT;
		vt.intVal=height;
		style->put_height(vt);

		vt.intVal=width;
		style->put_width(vt);

		style->Release();
	}
}

void BrowserUtility::SetNodeStyleBkColorARGB( IHTMLDOMNode *node, int rgb, int alpha )
{
	IHTMLStyle *style;
	TCHAR szTxt[150];
	
	style=BrowserUtility::_GetNodeStyle(node);
	if (style)
	{
		wsprintf(szTxt, TEXT("progid:DXImageTransform.Microsoft.gradient(startColorstr=#%02x%06x, endColorstr=#%02x%06x);")
			, alpha, rgb, alpha, rgb);

		style->put_filter(szTxt);

		style->Release();
	}
}

IHTMLStyle* BrowserUtility::_GetNodeStyle( IHTMLDOMNode *node )
{
	IHTMLElement *elm;
	IHTMLStyle *style;

	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_style(&style);
			elm->Release();
		}
	}

	return style;
}

void BrowserUtility::SetNodeStyleBkColorRGB( IHTMLDOMNode *node, int rgb )
{
	IHTMLElement *elm;
	IHTMLStyle *style;
	VARIANT vt;

	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_style(&style);
			if (style)
			{
				vt.vt=VT_INT;
				vt.intVal=rgb;
				style->put_backgroundColor(vt);
				style->Release();
			}

			elm->Release();
		}
	}
}

void BrowserUtility::SetNodeTextColor( IHTMLDOMNode *node, int rgb )
{
	IHTMLElement *elm;
	IHTMLStyle *style;
	VARIANT vt;

	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			elm->get_style(&style);
			if (style)
			{
				vt.vt=VT_INT;
				vt.intVal=rgb;
				style->put_color(vt);
				style->Release();
			}

			elm->Release();
		}
	}
}

BOOL BrowserUtility::IsName( IHTMLElement *elm, const TCHAR *lpszName )
{
	BOOL brs;
	VARIANT vt;


	brs=FALSE;

	if (elm)
	{
		elm->getAttribute(TEXT("name"), 2, &vt);

		if (vt.vt==VT_BSTR && vt.bstrVal)
		{
			if (ppIsEqualIgnoreCase(vt.bstrVal, lpszName, -1))
				brs=TRUE;

			SysFreeString(vt.bstrVal);
		}
	}

	return brs;
}

BOOL BrowserUtility::IsName( IHTMLDOMNode *node, const TCHAR *lpszName )
{
	IHTMLElement *elm;
	BOOL brs;

	brs=FALSE;

	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			brs=BrowserUtility::IsName(elm, lpszName);
			elm->Release();
		}
	}
	
	return brs;
}

BOOL BrowserUtility::IsTagName( IHTMLDOMNode *node, const TCHAR *lpszTagName )
{
	BOOL brs;
	BSTR str;

	brs=FALSE;
	if (node)
	{
		node->get_nodeName(&str);
		if (str)
		{
			if (ppIsEqualIgnoreCase(str, lpszTagName, -1)) brs=TRUE;

			SysFreeString(str);
		}
	}

	return brs;
}

IHTMLDOMNode* BrowserUtility::GetDomNodeById( IHTMLDocument3 *doc3, const TCHAR *lpszId )
{
	IHTMLElement *elm;
	IHTMLDOMNode *node;

	node=NULL;
	if (doc3)
	{
		doc3->getElementById((BSTR)lpszId, &elm);
		if (elm)
		{
			elm->QueryInterface(IID_IHTMLDOMNode, (void**)&node);
			elm->Release();
		}
	}

	return node;
}

IHTMLDOMNode* BrowserUtility::GetDomNodeById( IWebBrowser2 *wb2, const TCHAR *lpszId )
{
	IHTMLDocument3 *doc3;
	IHTMLDOMNode *node;
	
	doc3=BrowserUtility::GetDocument3(wb2);
	node=NULL;
	if (doc3)
	{
		node=BrowserUtility::GetDomNodeById(doc3, lpszId);
		doc3->Release();
	}

	return node;
}


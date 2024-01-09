#pragma once

#include <ExDisp.h>
#include <MsHTML.h>
#include "GameObj_XPathConst.h"
#include "PSimulator.h"

class BrowserUtility
{
public:
	static BOOL ParseFromXpath(IWebBrowser2 *wb2, const GAMEOBJ_XPATH *xpath, const TCHAR *lpszListBoundary,
		const TCHAR *lpszListIgnore, int nValue, int *lpnInitedValue, int *pArg, ...);
	static IHTMLDocument3* GetDocument3(IWebBrowser2 *wb2);
	static BOOL Simulator(IWebBrowser2 *wb2, const GAMEOBJ_XPATH *xpath);
	static BOOL Simulator(IHTMLDOMNode *node);

	//Element utility
	static BOOL IsDisabled(IHTMLElement *elm);
	static BOOL IsDisabled(IHTMLDOMNode *node);

	static BOOL IsClass(IHTMLElement *elm, const TCHAR *lpszClassName);
	static BOOL IsClass(IHTMLDOMNode *node, const TCHAR *lpszClassname);
	static void GetClass(IHTMLDOMNode *node, BSTR *str);

	static BOOL IsId(IHTMLElement *elm, const TCHAR *lpszId);
	static BOOL IsId(IHTMLDOMNode *node, const TCHAR *lpszId);
	static void GetId(IHTMLDOMNode *node, BSTR *str);

	static BOOL IsName(IHTMLElement *elm, const TCHAR *lpszName);
	static BOOL IsName(IHTMLDOMNode *node, const TCHAR *lpszName);

	static BOOL IsTagName(IHTMLDOMNode *node, const TCHAR *lpszTagName);

	static void GetBkImage(IHTMLElement *elm, BSTR *str);
	static void GetBkImage(IHTMLDOMNode *node, BSTR *str);

	static void GetTextColor(IHTMLElement *elm, VARIANT *vt);
	static void GetTextColor(IHTMLDOMNode *node, VARIANT *vt);

	static void GetNodeInnerText(IHTMLDOMNode *node, BSTR *str);
	static void GetChildNodeInnerText(IHTMLDOMNode *node, BSTR *str);

	static void GetNodeTitle(IHTMLDOMNode *node, BSTR *str);

	static void GetScriptOnMouseOver(IHTMLElement *elm, VARIANT *vt);
	static void GetScriptOnMouseOver(IHTMLDOMNode *node, VARIANT *vt);

	static void SetNodeStyleSize(IHTMLDOMNode *node, int width, int height);
	static void SetNodeStyleBkColorARGB(IHTMLDOMNode *node, int rgb, int alpha);
	static void SetNodeStyleBkColorRGB(IHTMLDOMNode *node, int rgb);
	static void SetNodeTextColor(IHTMLDOMNode *node, int rgb);

	static IHTMLDOMNode* GetDomNodeById(IHTMLDocument3 *doc3, const TCHAR *lpszId);
	static IHTMLDOMNode* GetDomNodeById(IWebBrowser2 *wb2, const TCHAR *lpszId);
private:
	static void _GetScript(IDispatch *dis, VARIANT *vt);
	static IHTMLStyle* _GetNodeStyle(IHTMLDOMNode *node);
};
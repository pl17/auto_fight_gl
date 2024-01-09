#ifndef _PXPATH_H
#define _PXPATH_H

#include <ExDisp.h>
#include <MsHTML.h>
#include <tchar.h>
#include "GameObj_XPathConst.h"

int pxpGetNodeIndex(TCHAR *szNodeName);
IHTMLDOMNode* pxpGetNodeByIndex(IHTMLDOMNode *root, TCHAR *lpszNodeName, int index);
IHTMLDOMNode* pxpGetXPathNode(IHTMLDOMNode *parent, const TCHAR *szXPath);
IHTMLDOMNode* pxpGetXPathNode(IHTMLDocument3 *doc3, const GAMEOBJ_XPATH *lpXPath);
BOOL pxpGetNodeValue(IHTMLDOMNode *node, VARIANT *vt);
IHTMLDOMNode* pxpGetFirstNode(IHTMLDOMNode *parent, const TCHAR *lpszAttributeName, const TCHAR *lpszAttributeValue);
#endif
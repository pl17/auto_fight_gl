#include "PXPath.h"
#include "PParser.h"
#include "BrowserUtility.h"


int pxpGetNodeIndex(TCHAR *szNodeName)
{
	int len, rs, dv;
	TCHAR * cStart;

	len=(int)_tcslen(szNodeName);
	rs=0;
	if (szNodeName[len-1]==']')
	{
		cStart=szNodeName+len-2;
		dv=1;
		while (cStart>=szNodeName)
		{
			if (*cStart=='[')
			{
				*cStart=NULL;
				break;
			}

			if (*cStart>='0' && *cStart<='9')
			{
				rs+=(*cStart-'0')*dv;
				dv*=10;
			}
			else
			{
				rs=0;
				break;
			}
			cStart--;
		}
	}

	if (rs==0) rs=1;
	return rs;
}

IHTMLDOMNode* pxpGetNodeByIndex(IHTMLDOMNode *root, TCHAR *lpszNodeName, int index)
{
	IHTMLDOMNode *node, *tmpNode;
	BSTR str;

	node=root;
	while (node)
	{
		node->get_nodeName(&str);
		if (_tcsicmp((TCHAR*)str, lpszNodeName)==0)
		{
			if (index>1)
				index--;
			else
			{
				break;
			}
		}
		SysFreeString(str);
		node->get_nextSibling(&tmpNode);
		if (node!=root)
			node->Release();
		node=tmpNode;
	}

	return node;
}

/*
IHTMLDOMNode* pxpGetXPathNode(IHTMLDOMNode *parent, const TCHAR *szXPath)
{
	IHTMLDOMNode *rs, *child, *nodeTmp;
	const TCHAR *cStart, *cEnd;
	TCHAR szTmp[50];
	int nIndex;
	IHTMLElement *pElm;
	BSTR str;

	cStart=szXPath;
	cEnd=szXPath-1;
	child=parent;

	if (szXPath==NULL) return parent;
	do
	{
		cEnd++;
		if (*cEnd==NULL || *cEnd=='/')
		{
			CopyMemory(szTmp, cStart, (int)(cEnd-cStart)*sizeof(TCHAR));
			szTmp[cEnd-cStart]=NULL;
			cStart=cEnd+1;
			nIndex=pxpGetNodeIndex(szTmp);
			nodeTmp=NULL;

			//Scan all child node

			if (child)
			{
				child->QueryInterface(IID_IHTMLElement, (void**)&pElm);
				if (pElm)
				{
					pElm->get_outerHTML(&str);
					SysFreeString(str);
					pElm->Release();
				}
				child->get_firstChild(&nodeTmp);

				if (nodeTmp)
				{

					rs=pxpGetNodeByIndex(nodeTmp, szTmp, nIndex);
					if (child!=parent)
						child->Release();
					child=rs;
					if (child!=nodeTmp)
						nodeTmp->Release();
					nodeTmp=NULL;
				}
			}
		}
	}while (*cEnd!=NULL && child);

	return child;
}*/

typedef BOOL (*pxpCheckAttribute)(IHTMLDOMNode *node, const TCHAR *lpszValue);

BOOL pxpIsClass(IHTMLDOMNode *node, const TCHAR *lpszValue)
{
	return BrowserUtility::IsClass(node, lpszValue);
}

BOOL pxpIsId(IHTMLDOMNode *node, const TCHAR *lpszValue)
{
	return BrowserUtility::IsId(node, lpszValue);
}

BOOL pxpIsName(IHTMLDOMNode *node, const TCHAR *lpszValue)
{
	return BrowserUtility::IsName(node, lpszValue);
}

IHTMLDOMNode* pxpGetFirstNode(IHTMLDOMNode *parent, pxpCheckAttribute fnc, const TCHAR *lpszValue)
{
	IHTMLDOMNode *child, *tmp;

	if (parent==NULL || fnc==NULL)
		return NULL;
	
	if (fnc(parent, lpszValue))
		return parent;

	parent->get_firstChild(&child);
	while (child)
	{
		tmp=pxpGetFirstNode(child, fnc, lpszValue);
		if (tmp)
			return tmp;

		child->get_nextSibling(&tmp);
		child->Release();
		child=tmp;
	}

	return NULL;
}

IHTMLDOMNode* pxpGetFirstNode(IHTMLDOMNode *parent, const TCHAR *lpszAttributeName, const TCHAR *lpszAttributeValue)
{
	pxpCheckAttribute fnc;

	if (ppIsEqualIgnoreCase(lpszAttributeName, TEXT("class"), -1))
	{
		fnc=pxpIsClass;
	}
	else if (ppIsEqualIgnoreCase(lpszAttributeName, TEXT("id"), -1))
	{
		fnc=pxpIsId;
	}
	else if (ppIsEqualIgnoreCase(lpszAttributeName, TEXT("name"), -1))
	{
		fnc=pxpIsName;
	}
	else
		fnc=NULL;

	return pxpGetFirstNode(parent, fnc, lpszAttributeValue);
}

IHTMLDOMNode* pxpGetXPathNode(IHTMLDOMNode *parent, const TCHAR *szXPath)
{
	IHTMLDOMNode *rs, *child, *nodeRoot;
	const TCHAR *cStart, *cEnd;
	TCHAR szTmp[50];
	int nIndex;

	cStart=szXPath;
	cEnd=szXPath;

	if (szXPath==NULL) return parent;

	nodeRoot=NULL;
	parent->QueryInterface(IID_IHTMLDOMNode, (void**)&nodeRoot);
	while (*cEnd && nodeRoot)
	{
		cEnd++;
		if (*cEnd==NULL || *cEnd=='/')
		{
			CopyMemory(szTmp, cStart, (int)(cEnd-cStart)*sizeof(TCHAR));
			szTmp[cEnd-cStart]=NULL;
			cStart=cEnd+1;
			nIndex=pxpGetNodeIndex(szTmp);

			//Scan all child node

			nodeRoot->get_firstChild(&child);
			rs=NULL;
			if (child)
			{

				rs=pxpGetNodeByIndex(child, szTmp, nIndex);
				if (child!=rs)
					child->Release();
			}
			nodeRoot->Release();
			nodeRoot=rs;
		}
	}

	return nodeRoot;
}

IHTMLDOMNode* pxpGetXPathNode(IHTMLDocument3 *doc3, const GAMEOBJ_XPATH *lpXPath)
{
	IHTMLDOMNode *parent, *rs;
	IHTMLElement *pElmTarget;

	rs=NULL;
	if (doc3)
	{
		doc3->getElementById((BSTR)lpXPath->lpcszId, &pElmTarget);
		if (pElmTarget)
		{
			pElmTarget->QueryInterface(IID_IHTMLDOMNode, (void**)&parent);
			if (parent)
			{
				rs=pxpGetXPathNode(parent, lpXPath->lpcszXPath);
				if (rs!=parent)
					parent->Release();
			}
			else
			{
				//parent null
			}
			pElmTarget->Release();
		}
	}
	else
	{
		//doc3 null
	}

	return rs;
}

BOOL pxpGetNodeValue(IHTMLDOMNode *node, VARIANT *vt)
{
	BOOL brs;
	IHTMLDOMNode *child;
	BSTR str;

	brs=FALSE;
	if (node)
	{
		child=NULL;
		node->get_nodeName(&str);
		SysFreeString(str);
		node->get_firstChild(&child);
		if (child)
		{
			child->get_nodeValue(vt);
			child->Release();
			brs=TRUE;
		}
	}

	return brs;
}
#include "GameItem.h"
#include "GameObj_XPathConst.h"
#include "PXPath.h"
#include "PParser.h"
#include "BrowserUtility.h"

GameItem::GameItem( IHTMLDocument3 *doc3, const TCHAR *lpszId )
{
	IHTMLDOMNode *node;

	//this->m_listAttribute.strAttribute=NULL;
	//this->m_listAttribute.next=NULL;
	this->m_lpszName=NULL;

	node=this->_GetAttributeRoot(doc3, lpszId);
	if (node)
	{
		this->_GetListAttribute(node);

		node->Release();
	}
}

GameItem::~GameItem()
{

}

void GameItem::_GetListAttribute(IHTMLDOMNode *nodeAttribute)
{
	IHTMLDOMNode *nodeTr;
	IHTMLDOMNode *nodeTmp;
	VARIANT vt;
	ITEMATTRIBUTE *list;
	TCHAR *szTxt=TEXT("td");
	int nCount;
	IHTMLStyle *style;

	IHTMLElement *elm;
	BSTR str;
	int i;

	if (nodeAttribute)
	{
		nodeAttribute->get_firstChild(&nodeTr);
		//list=&this->m_listAttribute;
		nCount=0;
		while (nodeTr)
		{
			nodeTr->get_firstChild(&nodeTmp);
			if (nodeTmp)
			{
				nCount++;
				nodeTmp->QueryInterface(IID_IHTMLElement, (void**)&elm);
				//elm->get_outerHTML(&str);
				pxpGetNodeValue(nodeTmp, &vt);
				/*list->next=(ITEMATTRIBUTE*)LocalAlloc(LMEM_FIXED, sizeof(ITEMATTRIBUTE));
				list=list->next;
				list->next=NULL;
				list->nType=0;
				list->strAttribute=vt.bstrVal;*/

				if (nCount==1)//Item name
				{
					if (this->m_lpszName)
						SysFreeString(this->m_lpszName);
					this->m_lpszName=(TCHAR*)vt.bstrVal;

					elm->get_style(&style);
					style->get_color(&vt);
					//style->get_visibility(&str);
					style->Release();

					this->m_nNameColor=0xffffff;
					if (vt.bstrVal)
					{
						if (ppIsEqualIgnoreCase((TCHAR*)vt.bstrVal, TEXT("lime"), -1))
							this->m_nNameColor=0x00FF00;//vt.intVal;
					}
				}
				else if (this->_IsAttributeGold(nodeTmp))
				{
					pxpGetNodeValue(nodeTmp, &vt);
					if (vt.vt==VT_BSTR && vt.bstrVal)
					{
						i=ppParseToNumberIgnoreText((TCHAR*)vt.bstrVal, NULL, TEXT("."), 1, &this->m_nGold);
						if (i==1)
						{
							this->m_bGoldValid=TRUE;
						}
					}
				}

				nodeTmp->Release();
			}

			nodeTr->get_nextSibling(&nodeTmp);
			nodeTr->Release();
			nodeTr=nodeTmp;
		}
	}
}

IHTMLDOMNode* GameItem::_GetAttributeRoot( IHTMLDocument3 *doc3, const TCHAR *lpszId )
{
	GAMEOBJ_XPATH xpath;
	IHTMLDOMNode *nodeItem, *nodeTmp;
	TCHAR szTxt[100];

	IHTMLElement *elm;
	BSTR str;

	nodeTmp=NULL;
	if (doc3)
	{
		xpath.lpcszId=lpszId;
		xpath.lpcszXPath=TEXT("table");//Root item node
		nodeItem=pxpGetXPathNode(doc3, &xpath);

		if (nodeItem)
		{
			nodeTmp=pxpGetFirstNode(nodeItem, TEXT("classname"), TEXT("tooltipBox"));
			if (nodeTmp)
			{
				nodeItem->Release();
				nodeItem=nodeTmp;

				nodeTmp=pxpGetXPathNode(nodeItem, TEXT("tbody"));
			}

			nodeItem->Release();
			nodeItem=nodeTmp;
		}

		/*if (nodeItem)
		{
			if (BrowserUtility::IsClass(nodeItem, TEXT("tooltipEquiped")))
			{
				wsprintf(szTxt, TEXT("tbody/tr/td[1]/table"));
			}
			else if (BrowserUtility::IsClass(nodeItem, TEXT("tooltipBox")))
			{
				szTxt[0]=NULL;
			}
			else
			{
				wsprintf(szTxt, TEXT("tbody/tr/td/table/tbody/tr/td/table"));
			}

			nodeTmp=pxpGetXPathNode(nodeItem, szTxt);
			if (nodeTmp)
			{
				nodeItem->Release();
				nodeItem=nodeTmp;

				if (BrowserUtility::IsClass(nodeItem, TEXT("tooltipEquiped")))
				{
					wsprintf(szTxt, TEXT("tbody/tr/td[1]/table/tbody"));
				}
				else
				{
					wsprintf(szTxt, TEXT("tbody"));
				}

				nodeTmp=pxpGetXPathNode(nodeItem, szTxt);
				nodeItem->Release();
				nodeItem=nodeTmp;
			}
		}*/
	}

	return nodeTmp;
}

BOOL GameItem::_IsAttributeGold( IHTMLDOMNode *parent )
{
	IHTMLDOMNode *node;
	IHTMLElement *elm;
	TCHAR szTxt[50];
	BOOL brs;
	BSTR str;

	brs=FALSE;
	if (parent)
	{
		wsprintf(szTxt, TEXT("img"));
		node=pxpGetXPathNode(parent, szTxt);
		if (node)
		{
			node->QueryInterface(IID_IHTMLElement, (void**)&elm);
			if (elm)
			{
				elm->get_title(&str);
				if (str)
				{
					if (ppIsEqualIgnoreCase((TCHAR*)str, TEXT("gold"), -1))
					{
						brs=TRUE;
					}
					SysFreeString(str);
				}
				elm->Release();
			}

			node->Release();
		}
	}
	return brs;
}

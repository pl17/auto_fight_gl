#include "ItemMarketObject.h"
#include "PXPath.h"
#include "PParser.h"
#include "BrowserUtility.h"

ItemMarketObject::ItemMarketObject()
{
	this->m_bCost=FALSE;
	this->m_nCost=0;

	this->m_nWidth=0;
	this->m_nHeight=0;
	this->m_fCostPerUnit=0;
}

void ItemMarketObject::Synchronized( IHTMLDocument3 *doc3, IHTMLDOMNode *marketitem )
{
	this->_SynchronizedCost(marketitem);
	this->_SynchronizedCostPerUnit(marketitem);
	this->_SynchronizedItemInfo(doc3, marketitem);
}

void ItemMarketObject::_SynchronizedItemInfo( IHTMLDocument3 *doc3, IHTMLDOMNode *marketitem )
{
	IHTMLDOMNode *info;
	IHTMLElement *elmInfo;
	VARIANT vtScript;
	TCHAR *lpszIdArg, *lpszId;

	info=pxpGetXPathNode(marketitem, TEXT("div[1]/div/div"));
	if (info)
	{
		BrowserUtility::GetScriptOnMouseOver(info, &vtScript);
		info->Release();

		if (vtScript.vt==VT_BSTR && vtScript.bstrVal)
		{
			ppParseFunctionArg(vtScript.bstrVal, 1, &lpszIdArg);
			if (lpszIdArg)
			{
				lpszId=lpszIdArg;
				lpszId[wcslen(lpszIdArg)-1]=NULL;
				lpszId++;
				doc3->getElementById(lpszId, &elmInfo);
				if (elmInfo)
				{
					elmInfo->QueryInterface(IID_IHTMLDOMNode, (void**)&info);
					if (info)
					{
						this->ItemObject::Synchronized(info);
						info->Release();
					}

					elmInfo->Release();
				}

				LocalFree(lpszIdArg);
			}

			SysFreeString(vtScript.bstrVal);
		}
	}
}

void ItemMarketObject::_SynchronizedCost( IHTMLDOMNode *marketitem )
{
	IHTMLDOMNode *nodeBidGold;
	BSTR str;
	int rs;

	nodeBidGold=pxpGetXPathNode(marketitem, TEXT("div[2]/div[2]"));
	if (nodeBidGold)
	{
		if (this->_IsNodeBidGold(nodeBidGold))
		{
			BrowserUtility::GetNodeInnerText(nodeBidGold, &str);
			if (str)
			{
				rs=ppParseToNumberIgnoreText(str, NULL, TEXT("."), 1, &this->m_nCost);
				if (rs==1) this->m_bCost=TRUE;

				SysFreeString(str);
			}
		}

		nodeBidGold->Release();
	}
}

BOOL ItemMarketObject::_IsNodeBidGold( IHTMLDOMNode *node )
{
	BOOL brs;
	IHTMLDOMNode *child;
	BSTR str;

	brs=FALSE;
	child=pxpGetXPathNode(node, TEXT("img"));
	if (child)
	{
		BrowserUtility::GetNodeTitle(child, &str);
		if (str)
		{
			brs=ppIsEqualIgnoreCase(str, TEXT("gold"), -1);

			SysFreeString(str);
		}

		child->Release();
	}

	return brs;
}

void ItemMarketObject::_SynchronizedCostPerUnit( IHTMLDOMNode *marketitem )
{
	IHTMLDOMNode *nodeImg;
	IHTMLImgElement *elm;
	long width, height;
	int rs;

	nodeImg=pxpGetXPathNode(marketitem, TEXT("div/div/div/img"));
	if (nodeImg)
	{
		nodeImg->QueryInterface(IID_IHTMLImgElement, (void**)&elm);
		if (elm)
		{
			if (elm->get_width(&width)==S_OK
				&& elm->get_height(&height)==S_OK
				&& this->m_bCost)
			{
				this->m_nHeight=(height+31)/32;
				this->m_nWidth=(width+31)/32;
				if (this->m_nHeight*this->m_nWidth>0)
					this->m_fCostPerUnit=(float)this->m_nCost/(this->m_nHeight*this->m_nWidth);
			}

			elm->Release();
		}

		nodeImg->Release();
	}
}

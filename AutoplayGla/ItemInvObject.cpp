#include "ItemInvObject.h"
#include "PXPath.h"
#include "PParser.h"
#include "BrowserUtility.h"


ItemInvObject::ItemInvObject()
{
	this->m_nHeight=0;
	this->m_nWidth=0;
	this->m_bActive=FALSE;
}

void ItemInvObject::Synchronized( IHTMLDocument3 *doc3, IHTMLDOMNode *invitem )
{
	this->m_bActive=FALSE;
	if (invitem)
	{
		this->_SynchronizedItemSize(invitem);
		this->_SynchronizedItemInfo(doc3, invitem);
	}
}

void ItemInvObject::_SynchronizedItemInfo( IHTMLDocument3 *doc3, IHTMLDOMNode *invitem )
{
	TCHAR *szIdInfo=NULL, *szId;
	VARIANT vtScript;
	IHTMLDOMNode *nodeInfo;
	GAMEOBJ_XPATH xpath;

	if (invitem)
	{
		BrowserUtility::GetScriptOnMouseOver(invitem, &vtScript);
		if (vtScript.vt==VT_BSTR && vtScript.bstrVal)
		{
			ppParseFunctionArg(vtScript.bstrVal, 1, &szIdInfo);
			if (szIdInfo)
			{
				szId=szIdInfo+1;
				szId[wcslen(szIdInfo)-2]=NULL;
				xpath.lpcszId=szId;
				xpath.lpcszXPath=NULL;
				nodeInfo=pxpGetXPathNode(doc3, &xpath);
				if (nodeInfo)
				{
					this->ItemObject::Synchronized(nodeInfo);

					nodeInfo->Release();
				}
				LocalFree(szIdInfo);
			}

			SysFreeString(vtScript.bstrVal);
		}
	}
}

void ItemInvObject::_SynchronizedItemSize( IHTMLDOMNode *invitem )
{
	long width, height;
	IHTMLDOMNode *nodeImg;
	IHTMLImgElement *elmImg;

	this->m_nHeight=0;
	this->m_nWidth=0;

	if (invitem)
	{
		nodeImg=pxpGetXPathNode(invitem, TEXT("img"));
		if (nodeImg)
		{
			nodeImg->QueryInterface(IID_IHTMLImgElement, (void**)&elmImg);
			if (elmImg)
			{	
				if (elmImg->get_width(&width)==S_OK
					&& elmImg->get_height(&height)==S_OK)
				{
					this->m_bActive=TRUE;
					this->m_nWidth=(width+31)/32;
					this->m_nHeight=(height+31)/32;

					this->_SynchronizedItemType(elmImg);
				}

				elmImg->Release();
			}

			nodeImg->Release();
		}
	}
}

void ItemInvObject::SetActive( BOOL bActive )
{
	this->m_bActive=bActive;
}

BOOL ItemInvObject::GetActive()
{
	return this->m_bActive;
}

void ItemInvObject::_SynchronizedItemType( IHTMLImgElement *item )
{
	BSTR str;
	TCHAR *szItemName;
	int type, id;

	this->m_enType=ITEMTYPE_UNKNOWN;
	if (item)
	{
		item->get_src(&str);
		if (str)
		{
			szItemName=wcsrchr(str, L'/');
			if (szItemName)
			{
				if (ppParseToNumberIgnoreText(szItemName, TEXT("_"), NULL, 2, &type, &id)==2)
				{
					if (type==7)
					{
						this->m_enType=ITEMTYPE_FOOD;
					}
				}
			}

			SysFreeString(str);
		}
	}
}

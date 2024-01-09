#include "GameMod_Base.h"
#include "BrowserUtility.h"

BOOL GameMod_Base::Go(IWebBrowser2 *wb2)
{
	BOOL brs;
	IHTMLDOMNode *node;
	UQueryString *src;
	BSTR url;

	brs=FALSE;
	if (wb2 && this->m_qsTarget)
	{
		wb2->get_LocationURL(&url);
		if (url)
		{
			src=new UQueryString(url);
			src->RemoveKey(TEXT("sh"));
			
			brs=this->_IsTruth(src);
			if (!brs)
			{
				node=this->_GetNextNode(wb2, src);
				if (node)
				{
					BrowserUtility::Simulator(node);
					node->Release();
				}
			}

			delete src;

			SysFreeString(url);
		}
	}

	return brs;
}

void GameMod_Base::SetMod( const TCHAR *szQueryString )
{
	if (this->m_qsTarget)
	{
		delete this->m_qsTarget;
	}
	
	this->m_qsTarget=new UQueryString(szQueryString);
}

BOOL GameMod_Base::_IsTruth( UQueryString *qsSrc )
{
	BOOL brs;

	brs=FALSE;

	if (qsSrc && this->m_qsTarget)
	{
		brs=UQueryString::IsEqualQuery(this->m_qsTarget, qsSrc);
	}

	return brs;
}

GameMod_Base::GameMod_Base()
{
	this->m_qsTarget=NULL;
}

GameMod_Base::GameMod_Base( const TCHAR *szQueryStringTarget )
{
	this->m_qsTarget=NULL;
	this->SetMod(szQueryStringTarget);
}

GameMod_Base::~GameMod_Base()
{
	if (this->m_qsTarget)
		delete this->m_qsTarget;
}

BOOL GameMod_Base::IsTruth( IWebBrowser2 *wb2 )
{
	BOOL brs;
	UQueryString *query;
	BSTR url;

	brs=FALSE;
	if (wb2)
	{
		wb2->get_LocationURL(&url);
		if (url)
		{
			query=new UQueryString(url);

			query->RemoveKey(TEXT("sh"));
			brs=this->_IsTruth(query);

			delete query;
			SysFreeString(url);
		}
	}

	return brs;
}


#pragma once

#include <MsHTML.h>
#include "IGameMod.h"
#include "UQueryString.h"

class GameMod_Base :
	public IGameMod
{
public:
	GameMod_Base();
	GameMod_Base(const TCHAR *szQueryStringTarget);
	~GameMod_Base();

	BOOL Go(IWebBrowser2 *wb2);
	void SetMod(const TCHAR *szQueryString);
	virtual BOOL IsTruth( IWebBrowser2 *wb2 );
	
protected:
	virtual IHTMLDOMNode* _GetNextNode(IWebBrowser2 *wb2, UQueryString *src)=0;
	virtual BOOL _IsTruth(UQueryString *qsSrc);

	UQueryString *m_qsTarget;
};
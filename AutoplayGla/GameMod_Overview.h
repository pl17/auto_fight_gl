#pragma once

#include "GameMod_Base.h"

class GameMod_Overview :
	public GameMod_Base
{
public:
	enum MODOVERVIEW
	{
		MODOVERVIEW_OTHERMOD,
		MODOVERVIEW_UNKNOWN,
		MODOVERVIEW_OVERVIEW,
	};
private:
	IHTMLDOMNode* _GetNextNode( IWebBrowser2 *wb2, UQueryString *src );
	BOOL _IsTruth( UQueryString *qsSrc );
	MODOVERVIEW _GetMod(UQueryString *query);
};
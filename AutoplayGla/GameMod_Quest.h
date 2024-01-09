#pragma once

#include "GameMod_Base.h"

class GameMod_Quest :
	public GameMod_Base
{
public:
	enum ModQuest
	{
		MODQUEST_OTHERMOD,
		MODQUEST_QUEST,
		MODQUEST_UNKNOWN,
	};

private:
	IHTMLDOMNode* _GetNextNode( IWebBrowser2 *wb2, UQueryString *src );
	ModQuest _GetMod(UQueryString *query);
	BOOL _IsTruth( UQueryString *qsSrc );
};
#pragma once

#include "GameMod_Base.h"

class GameMod_Arena :
	public GameMod_Base
{
public:
	enum ModArena
	{
		MODARENA_OTHERMOD,
		MODARENA_ARENALOCAL,
		MODARENA_ARENASERVER,
		MODARENA_TURMALOCAL,
		MODARENA_TURMASERVER,
		MODARENA_UNKNOWN,
	};
//private:
	IHTMLDOMNode* _GetNextNode( IWebBrowser2 *wb2, UQueryString *src );
	ModArena _GetArenaType(UQueryString *query);
};
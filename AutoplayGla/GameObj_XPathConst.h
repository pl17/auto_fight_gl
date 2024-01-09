#ifndef _GAMEOBJ_XPATHCONST_H
#define _GAMEOBJ_XPATHCONST_H

#include <tchar.h>

typedef struct _GAMEOBJ_XPATH
{
	const TCHAR *lpcszId;
	const TCHAR *lpcszXPath;
}GAMEOBJ_XPATH;

class GameObj_XPathConst
{
public:
	//Header information
	static const GAMEOBJ_XPATH HEADER_GOLD;
	static const GAMEOBJ_XPATH HEADER_RUBI;
	static const GAMEOBJ_XPATH HEADER_LEVEL;
	static const GAMEOBJ_XPATH HEADER_RANK;
	static const GAMEOBJ_XPATH HEADER_HP;
	static const GAMEOBJ_XPATH HEADER_EXP;
	static const GAMEOBJ_XPATH HEADER_LOCATION_POINT;
	static const GAMEOBJ_XPATH HEADER_LOCATION_COOLDOWN;
	static const GAMEOBJ_XPATH HEADER_DUNGEON_POINT;
	static const GAMEOBJ_XPATH HEADER_DUNGEON_COOLDOWN;
	static const GAMEOBJ_XPATH HEADER_ARENA_COOLDOWN;
	static const GAMEOBJ_XPATH HEADER_ARENA_RANK;
	static const GAMEOBJ_XPATH HEADER_TURMA_COOLDOWN;
	static const GAMEOBJ_XPATH HEADER_TURMA_RANK;

	static const GAMEOBJ_XPATH MOD_TURMA;
	static const GAMEOBJ_XPATH MOD_ARENA;
	static const GAMEOBJ_XPATH MOD_TURMASERVER;
	static const GAMEOBJ_XPATH MOD_ARENASERVER;
	static const GAMEOBJ_XPATH MOD_LOCATION;
	static const GAMEOBJ_XPATH MOD_DUNGEON;
	static const GAMEOBJ_XPATH MOD_QUEST;
	static const GAMEOBJ_XPATH MOD_OVERVIEW;

	static const GAMEOBJ_XPATH CONT_LISTARENASERVER;
	static const GAMEOBJ_XPATH CONT_LISTARENASERVER_EMAILNOTACTIVE;
	static const GAMEOBJ_XPATH CONT_LISTARENASERVER_BASH;

	static const GAMEOBJ_XPATH CONT_LISTQUEST;
	static const GAMEOBJ_XPATH CONT_QUESTREFRESH;

	static const GAMEOBJ_XPATH CONT_LISTITEMMARKET;
};

#endif
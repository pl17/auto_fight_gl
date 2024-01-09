#pragma once

#define GAP_MAXLEN_PLAYERNAME	50


typedef struct _ARENA_RECORD
{
	int nWin;
	int nLose;
	int nDraw;
} ARENA_RECORD;

typedef struct _ARENA_PLAYER
{
	TCHAR szPlayerName[GAP_MAXLEN_PLAYERNAME];
	int nLevel;
	int nServer;
	ARENA_RECORD arArena;
	ARENA_RECORD arTurma;
	BOOL bEnable;
} ARENA_PLAYER;

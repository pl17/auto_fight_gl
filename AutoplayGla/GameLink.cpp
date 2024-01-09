#include <tchar.h>

#include "GameLink.h"

GameLink::GameLink( IWebBrowser2 *wb2 )
{
	this->m_wb2=NULL;
	this->SetIWeb(wb2);
	this->m_bsUrl=NULL;
}

GameLink::~GameLink()
{
	if (this->m_wb2)
	{
	//	this->m_wb2->Release();
	//	this->m_wb2=NULL;
	}
	if (this->m_bsUrl)
	{
		SysFreeString(this->m_bsUrl);
		this->m_bsUrl=NULL;
	}
}


void GameLink::SetIWeb( IWebBrowser2 *wb2 )
{
	if (this->m_wb2 && this->m_wb2!=wb2)
	{
		//this->m_wb2->Release();
		//this->m_wb2=NULL;
	}

	this->m_wb2=wb2;
}


void GameLink::UpdateValue()
{
	this->_UpdateURL();
}

int GameLink::GetModId()
{
	this->m_nMod=this->_UpdateMod();
	return this->m_nMod;
}


BOOL GameLink::_UpdateURL()
{
	if (this->m_bsUrl)
	{
		SysFreeString(this->m_bsUrl);
		this->m_bsUrl=NULL;
	}

	this->m_wb2->get_LocationURL(&this->m_bsUrl);

	return TRUE;
}

int GameLink::_UpdateMod()
{
	TCHAR szModName[50];

	if (this->_ParseQuery(TEXT("mod"), szModName, 50))
	{
		for (int i=0; i<GameLink::m_nListMod; i++)
		{
			if (this->_IsEqualIgnoreCase(szModName, GameLink::m_ListMod[i].lpszModName, _tcslen(GameLink::m_ListMod[i].lpszModName)))
			{
				if (GameLink::m_ListMod[i].nModId==GAMELINK_MOD_ARENA || GameLink::m_ListMod[i].nModId==GAMELINK_MOD_TURMA)
				{
					//return GAMELINK_MOD_UNKNOWN;
				}
				return GameLink::m_ListMod[i].nModId;
			}
		}

		return GAMELINK_MOD_UNKNOWN;
	}

	return GAMELINK_MOD_NOTFOUND;
}

int GameLink::_ParseSubmod()
{
	return 0;
}

BOOL GameLink::_ParseQuery( const TCHAR *szKey, TCHAR *szValue, int nsize )
{
	int len, size;
	const TCHAR *cTmp;

	if (szKey==NULL || szValue==NULL) return FALSE;

	len=_tcslen(szKey);

	cTmp=this->m_bsUrl;
	while (1)
	{
		cTmp=this->_FindSubString(cTmp, szKey, len);
		if (cTmp==NULL) break;
		cTmp+=len;
		if (*cTmp=='=')
		{
			cTmp++;
			size=0;
			while (cTmp[size]!='&' && cTmp[size]!=NULL)
			{
				size++;
			}
			if (size>nsize-1) size=nsize-1;
			CopyMemory(szValue, cTmp, (size)*sizeof(TCHAR));
			szValue[size]=NULL;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL GameLink::_IsEqualIgnoreCase( const TCHAR *src, const TCHAR *des, int nsize )
{
	if (des==NULL) return TRUE;
	if (src==NULL) return FALSE;

	int len=_tcslen(des);
	for (int i=0; i<nsize; i++)
	{
		if ((src[i]|0x20)!=(des[i]|0x20))
			return FALSE;
	}

	return TRUE;
}


const TCHAR* GameLink::_FindSubString( const TCHAR *src, const TCHAR *des, int nsize )
{
	if (des==NULL) return src;
	if (src==NULL) return NULL;

	int len=_tcslen(src);
	for (int i=0; i<len-nsize; i++)
	{
		if (GameLink::_IsEqualIgnoreCase(src+i, des, nsize))
			return src+i;
	}
	return NULL;
}

const GL_MOD GameLink::m_ListMod[]={
	{GAMELINK_MOD_ARENA, TEXT("Arena")},
	{GAMELINK_MOD_LOCATION, TEXT("location")},
	{GAMELINK_MOD_DUNGEON, TEXT("dungeon")},
	{GAMELINK_MOD_QUEST, TEXT("quest")},
	{GAMELINK_MOD_REPORT, TEXT("report")},
	{GAMELINK_MOD_OVERVIEW, TEXT("overview")},
	{GAMELINK_MOD_PLAYER, TEXT("player")},
	{GAMELINK_MOD_MARKET, TEXT("auction")}
};


const int GameLink::m_nListMod=sizeof(GameLink::m_ListMod)/sizeof(GameLink::m_ListMod[0]);


const TCHAR* GameLink::_FindModName( int nId )
{
	for (int i=0; i<GameLink::m_nListMod; i++)
	{
		if (GameLink::m_ListMod[i].nModId==nId)
			return GameLink::m_ListMod[i].lpszModName;
	}

	return NULL;
}

const int GameLink::_FindModId( const TCHAR *szModName )
{
	for (int i=0; i<GameLink::m_nListMod; i++)
	{
		if (GameLink::_IsEqualIgnoreCase(szModName, GameLink::m_ListMod[i].lpszModName, _tcslen(GameLink::m_ListMod[i].lpszModName)))
			return GameLink::m_ListMod[i].nModId;
	}

	return GAMELINK_MOD_NOTFOUND;
}

BOOL GameLink::ParseQuery( const TCHAR *szKey, TCHAR *szValue, int nsize )
{
	return this->_ParseQuery(szKey, szValue, nsize);
}

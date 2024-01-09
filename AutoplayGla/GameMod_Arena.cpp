#include "GameMod_Arena.h"
#include "PXPath.h"
#include "GameObj_XPathConst.h"
#include "BrowserUtility.h"

IHTMLDOMNode* GameMod_Arena::_GetNextNode( IWebBrowser2 *wb2, UQueryString *src)
{
	IHTMLDOMNode *node;
	ModArena typeSrc, typeDes;
	IHTMLDocument3 *doc3;
	GAMEOBJ_XPATH xpath;
	int nOrder;
	TCHAR szPath[20];

	node=NULL;
	if (wb2 && src && this->m_qsTarget)
	{
		typeSrc=this->_GetArenaType(src);
		typeDes=this->_GetArenaType(this->m_qsTarget);
		doc3=BrowserUtility::GetDocument3(wb2);
		if (doc3)
		{
			if (typeSrc==MODARENA_OTHERMOD)//In other mod
			{
				node=pxpGetXPathNode(doc3, &GameObj_XPathConst::MOD_ARENA);
			}
			else if (typeSrc!=typeDes)//In arena mod
			{
				nOrder=0;
				switch(typeDes)
				{
				case MODARENA_ARENALOCAL://Goto arenalocal
					nOrder=1;
					break;
				case MODARENA_ARENASERVER://Goto arenaserver
					nOrder=2;
					break;
				case MODARENA_TURMALOCAL://Goto turmalocal
					nOrder=3;
					break;
				case MODARENA_TURMASERVER://Goto turmaserver
					nOrder=4;
					break;
				}

				if (nOrder>0)
				{
					xpath.lpcszId=TEXT("mainnav");
					wsprintf(szPath, TEXT("li[%d]/a"), nOrder);
					xpath.lpcszXPath=szPath;
					node=pxpGetXPathNode(doc3, &xpath);//Find link a
				}
			}

			doc3->Release();
		}
	}

	return node;
}

GameMod_Arena::ModArena GameMod_Arena::_GetArenaType( UQueryString *query )
{
	ModArena type;
	BOOL bIsMod;
	TCHAR* szSubMod;
	TCHAR *szAType;


	type=MODARENA_UNKNOWN;

	if (query)
	{
		if (query->IsEqual(TEXT("mod"), TEXT("arena")))//Check arena mod
		{
			szSubMod=query->GetValue(TEXT("submod"));
			if (szSubMod)
			{
				if (wcsicmp(szSubMod, TEXT("grouparena"))==0)//Local arena
				{
					type=MODARENA_TURMALOCAL;
				}
				else if (wcsicmp(szSubMod, TEXT("serverArena"))==0)//Server arena
				{
					szAType=query->GetValue(TEXT("aType"));
					if (szAType)
					{
						if (wcsicmp(szAType, TEXT("2"))==0)//ArenaServer
						{
							type=MODARENA_ARENASERVER;
						}
						else if (wcsicmp(szAType, TEXT("3"))==0)//TurmaServer
						{
							type=MODARENA_TURMASERVER;
						}
					}//EndIf aType
				}//EndIf Submod
			}
			else//Not contain submod
			{
				type=MODARENA_ARENALOCAL;
			}//EndIf check submod
		}
		else//Else checkmod
		{
			type=MODARENA_OTHERMOD;
		}//EndIf check mod
	}

	return type;
}


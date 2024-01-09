#ifdef _PDBG

#define _WIN32_WINNT 0x0501

#include <Windows.h>
#include <stdio.h>
#include <WinCon.h>
#include "MOutputDebug_Console.h"

#pragma warning(disable: 4267)


BOOL MOutputDebug_Console::Init()
{
	BOOL rs;
	HANDLE hStream;

	rs=FALSE;
	hStream=GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStream==NULL || hStream==INVALID_HANDLE_VALUE)
	{
		if (AllocConsole())
		{
			EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);
			hStream=GetStdHandle(STD_OUTPUT_HANDLE);

			if (hStream!=NULL && hStream!=INVALID_HANDLE_VALUE)
			{
				//Success get handle stream
				rs=TRUE;
			}		
		}
		else
		{
			//Error cannot create console
		}
	}
	else
	{
		//Exist console
		rs=TRUE;
	}

	this->SetStream(hStream);
	return rs;
}

void MOutputDebug_Console::Clear()
{
	HANDLE hStream;

	hStream=this->GetStream();
	if (hStream!=NULL && hStream!=INVALID_HANDLE_VALUE)
	{
		FreeConsole();
	}
}

MOutputDebug_Console::MOutputDebug_Console()
{
	this->Init();
}

MOutputDebug_Console::~MOutputDebug_Console()
{
	this->Clear();
}

BOOL MOutputDebug_Console::Reset()
{
	HANDLE hConsole;
	BOOL rs;
	CONSOLE_SCREEN_BUFFER_INFO info;
	COORD topleft;
	DWORD winsz;
	DWORD nchars;

	rs=FALSE;
	
	hConsole=this->GetStream();
	if (hConsole!=NULL && hConsole!=INVALID_HANDLE_VALUE)
	{
		topleft.X=0;
		topleft.Y=0;
		rs=GetConsoleScreenBufferInfo(hConsole, &info);

		winsz=info.dwSize.X*info.dwSize.Y;
		rs|=FillConsoleOutputCharacter(hConsole, ' ', winsz, topleft, &nchars);
		rs|=SetConsoleCursorPosition(hConsole, topleft);
	}

	return rs;
}

BOOL MOutputDebug_Console::WriteStreamW( WCHAR *szMsg, DWORD dwSize, DWORD* lpdwWritten )
{
	WaitForSingleObject(this->GetStream(), INFINITE);
	return WriteConsoleW(this->GetStream(), szMsg, dwSize, lpdwWritten, NULL);
}

#endif

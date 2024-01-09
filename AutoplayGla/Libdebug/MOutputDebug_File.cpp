#ifdef _PDBG

#include "MOutputDebug_File.h"


MOutputDebug_File::MOutputDebug_File(TCHAR *szFileName)
{
	this->m_szFileName=szFileName;
	this->Init();
}

MOutputDebug_File::~MOutputDebug_File()
{

}

BOOL MOutputDebug_File::Init()
{
	BOOL rs;
	DWORD dwError;
	HANDLE hFile;

	rs=FALSE;

	hFile=CreateFile(this->m_szFileName
		, GENERIC_WRITE
		, 0
		, NULL
		, OPEN_ALWAYS
		, FILE_ATTRIBUTE_NORMAL
		, NULL);

	if (hFile!=INVALID_HANDLE_VALUE)
	{
		if (SetFilePointer(hFile, 0, NULL, FILE_END)==INVALID_SET_FILE_POINTER)
		{
			CloseHandle(hFile);
			hFile=INVALID_HANDLE_VALUE;
		}
		else
		{
			rs=TRUE;
		}
	}
	else
	{
		//Error cannot create file
		dwError=GetLastError();
		switch(dwError)
		{
		case ERROR_ACCESS_DENIED:
			break;
		case ERROR_NOT_ENOUGH_MEMORY:
			break;
		}
	}

	this->SetStream(hFile);
	return rs;
}

void MOutputDebug_File::Clear()
{
	HANDLE hFile;

	hFile=this->GetStream();
	if (hFile!=INVALID_HANDLE_VALUE && hFile!=NULL)
		CloseHandle(hFile);
}

BOOL MOutputDebug_File::Reset()
{
	BOOL rs;

	SetFilePointer(this->GetStream(), 0, NULL, FILE_BEGIN);
	rs=SetEndOfFile(this->GetStream());

	return TRUE;
}

#endif
#include "MOutputDebug_Base.h"

class MOutputDebug_View: public MOutputDebug_Base
{
public:
	MOutputDebug_View();
	~MOutputDebug_View();

	virtual BOOL Reset();
protected:
	virtual BOOL Init();
	virtual void Clear();

	BOOL WriteStreamA(char *szMsg, DWORD dwSize, DWORD* lpdwWritten);
	BOOL WriteStreamW(WCHAR *szMsg, DWORD dwSize, DWORD* lpdwWritten);
};
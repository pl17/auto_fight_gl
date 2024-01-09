#include "MOutputDebug_Base.h"

class MOutputDebug_Console : public MOutputDebug_Base
{
public:
	MOutputDebug_Console();
	~MOutputDebug_Console();

	virtual BOOL Reset();

protected:
	BOOL WriteStreamW(WCHAR *szMsg, DWORD dwSize, DWORD* lpdwWritten);
	BOOL Init();
	void Clear();
};
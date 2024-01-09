#include "MOutputDebug_Base.h"

class MOutputDebug_File : public MOutputDebug_Base
{
public:
	MOutputDebug_File(TCHAR *szFileName);
	~MOutputDebug_File();

	virtual BOOL Reset();

protected:
	virtual BOOL Init();
	virtual void Clear();

private:
	TCHAR *m_szFileName;
};
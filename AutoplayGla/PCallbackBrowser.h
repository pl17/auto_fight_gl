#include <ExDisp.h>
#include "IGameEventHandler.h"

typedef HRESULT (WINAPI *AX_CallbackEventHandler)(IGameEventHandler *pthis, IWebBrowser2 *wb, DISPPARAMS*);

class PCallbackBrowser
{
public:
	PCallbackBrowser();
	~PCallbackBrowser();

	BOOL Add(IGameEventHandler *object);
	BOOL Remove(IGameEventHandler *object);
	void ExecuteAll(IWebBrowser2 *wb, DISPPARAMS* param);
private:
	typedef struct _LIST_CALLBACK
	{
		IGameEventHandler *object;
		struct _LIST_CALLBACK *next;
	} LIST_CALLBACK;

	LIST_CALLBACK *m_listFunc;
	BOOL _IsExistFunction(IGameEventHandler *object);
	LIST_CALLBACK* _GetLast();
};

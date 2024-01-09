#include "PCallbackBrowser.h"


PCallbackBrowser::PCallbackBrowser()
{
	this->m_listFunc=(LIST_CALLBACK*)LocalAlloc(LMEM_FIXED, sizeof(LIST_CALLBACK));
	if (this->m_listFunc)
	{
		this->m_listFunc->object=NULL;
		this->m_listFunc->next=NULL;
	}
}

PCallbackBrowser::~PCallbackBrowser()
{
	LIST_CALLBACK *next, *now;

	if (this->m_listFunc)
	{
		now=this->m_listFunc;
		next=this->m_listFunc->next;
		
		while(now)
		{
			LocalFree(now);
			now=next;
			next=now->next;
		}
	}
}

BOOL PCallbackBrowser::Add( IGameEventHandler *pthis )
{
	LIST_CALLBACK *last;

	if (!this->_IsExistFunction(pthis))
	{
		last=this->_GetLast();
		if (last)
		{
			last->next=(LIST_CALLBACK*)LocalAlloc(LMEM_FIXED, sizeof(LIST_CALLBACK));
			last=last->next;
			last->object=pthis;
			last->next=NULL;
		}
	}

	return TRUE;
}

BOOL PCallbackBrowser::Remove( IGameEventHandler *object )
{
	LIST_CALLBACK *p, *pre;

	p=this->m_listFunc;
	pre=p;

	while (p)
	{
		if (p->object==object)
		{
			pre->next=p->next;
			LocalFree(p);
			return TRUE;
		}

		pre=p;
		p=p->next;
	}

	return FALSE;
}

void PCallbackBrowser::ExecuteAll( IWebBrowser2 *wb, DISPPARAMS* param )
{
	LIST_CALLBACK *p;

	p=this->m_listFunc->next;
	while (p)
	{
		if (p->object)
			//p->object->UpdateValue(wb, param);
			p->object->Synchronized(wb);

		p=p->next;
	}
}

BOOL PCallbackBrowser::_IsExistFunction( IGameEventHandler *object )
{
	LIST_CALLBACK *p;

	p=this->m_listFunc->next;
	while (p)
	{
		if (p->object==object)
			return TRUE;
		p=p->next;
	}

	return FALSE;
}

PCallbackBrowser::LIST_CALLBACK* PCallbackBrowser::_GetLast()
{
	LIST_CALLBACK *p;

	p=this->m_listFunc;
	while (p)
	{
		if (p->next==NULL)
			return p;
		p=p->next;
	}

	return NULL;
}

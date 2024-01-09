#include "GEventManager.h"

GEventManager::GEventManager()
{
	this->m_evNow=NULL;	
}

GEventManager::~GEventManager()
{

}

void GEventManager::AddEvent( IGameEventHandler *handler )
{
	this->m_listEvent.Append(handler);
}

void GEventManager::OnCooldown(int nCooldown)
{
	ULinkNode<IGameEventHandler*> *node;

	node=this->m_listEvent.First()->Next();
	while (node!=this->m_listEvent.Last())
	{
		node->GetData()->OnCoolDown(nCooldown);
		node=node->Next();
	}
}

void GEventManager::Run()
{
	ULinkNode<IGameEventHandler*> *node;

	if (this->m_evNow)
	{
		if (!this->m_evNow->RunEvent())
			return;
		else
			this->m_evNow=NULL;
	}

	node=this->m_listEvent.First()->Next();
	while (node!=this->m_listEvent.Last())
	{
		if (!node->GetData()->RunEvent())
		{
			this->m_evNow=node->GetData();
			return;
		}

		node=node->Next();
	}
}

void GEventManager::OnDocumentCompleted( IWebBrowser2 *wb2 )
{
	ULinkNode<IGameEventHandler*> *node;

	node=this->m_listEvent.First()->Next();
	while (node!=this->m_listEvent.Last())
	{
		node->GetData()->Synchronized(wb2);
		node=node->Next();
	}
}

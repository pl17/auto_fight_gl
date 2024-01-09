#include "GameObject_Base.h"


GameObject_Base::GameObject_Base()
{
	this->m_nCooldown=999;
	this->m_esCooldown=STATUS_NOTINIT;
	this->m_wb2=NULL;
}


void GameObject_Base::SetCooldown( int nCooldown )
{
	this->m_nCooldown=nCooldown;
	this->m_esCooldown=STATUS_FORCE;
}

int GameObject_Base::GetCooldown()
{
	return this->m_nCooldown;
}

IGameObject::GO_Status GameObject_Base::OnCooldown( int nCountdown )
{
	GO_Status status;

	if (this->m_esCooldown==STATUS_NOTINIT)
	{
		status=STATUS_NOTINIT;
	}
	else
	{
		status=STATUS_SUCCESS;
		if (this->m_esCooldown==STATUS_FORCE)
		{
			this->m_esCooldown=STATUS_SUCCESS;
			if (this->m_nCooldown==0)
				status=STATUS_ZERO;
		}
		else
		{
			if (this->m_nCooldown>0)
			{
				this->m_nCooldown-=nCountdown;
				if (this->m_nCooldown<=0)
				{
					status=STATUS_ZERO;
				}
			}
		}
	}

	return status;
}

void GameObject_Base::_SetIWeb2( IWebBrowser2 *wb2 )
{
	if (this->m_wb2 && this->m_wb2!=wb2)
	{
		this->m_wb2->Release();
	}

	this->m_wb2=wb2;
}

void GameObject_Base::_SynchronizedCooldown()
{
	this->m_esCooldown=STATUS_FORCE;
}


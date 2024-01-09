#include "GItemToolTip.h"

GItemToolTip::GItemToolTip()
{
	this->m_bValidated=FALSE;

	this->m_strName=NULL;
	this->m_nLevel=0;
	this->m_nValue=0;
	this->m_nNameColor=0;
	this->m_bSoulBound=FALSE;
}



GItemToolTip::~GItemToolTip()
{
	if (this->m_strName)
		SysFreeString(this->m_strName);
}

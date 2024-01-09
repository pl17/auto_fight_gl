#include "TestMouseEvent.h"

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_srcElement( IHTMLElement **p )
{
	*p=NULL;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_altKey( VARIANT_BOOL *p )
{
	*p=VARIANT_FALSE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_ctrlKey( VARIANT_BOOL *p )
{
	*p=VARIANT_FALSE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_shiftKey( VARIANT_BOOL *p )
{
	*p=VARIANT_FALSE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::put_returnValue( VARIANT v )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_returnValue( VARIANT *p )
{
	p=NULL;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::put_cancelBubble( VARIANT_BOOL v )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_cancelBubble( VARIANT_BOOL *p )
{
	*p=VARIANT_FALSE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_fromElement( IHTMLElement **p )
{
	*p=NULL;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_toElement( IHTMLElement **p )
{
	*p=NULL;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::put_keyCode( long v )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_keyCode( long *p )
{
	*p=0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_button( long *p )
{
	*p=0;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_type( BSTR *p )
{
	*p=NULL;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_qualifier( BSTR *p )
{
	*p=NULL;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_reason( long *p )
{
	*p=500;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_x( long *p )
{
	*p=0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_y( long *p )
{
	*p=0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_clientX( long *p )
{
	*p=0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_clientY( long *p )
{
	*p=0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_offsetX( long *p )
{
	*p=500;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_offsetY( long *p )
{
	*p=500;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_screenX( long *p )
{
	*p=500;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_screenY( long *p )
{
	*p=500;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::get_srcFilter( IDispatch **p )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::GetTypeInfoCount( UINT *pctinfo )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::GetTypeInfo( UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::GetIDsOfNames( REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::Invoke( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE TestMouseEvent::QueryInterface( REFIID riid, void **ppvObject )
{
	*ppvObject=NULL;
	if (riid==IID_IHTMLEventObj || riid==IID_IDispatch)
	{
		*ppvObject=this;
		this->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE TestMouseEvent::AddRef( void )
{
	this->m_nRef++;
	return this->m_nRef;
}

ULONG STDMETHODCALLTYPE TestMouseEvent::Release( void )
{
	this->m_nRef--;
	return this->m_nRef;
}

TestMouseEvent::TestMouseEvent()
{
	this->m_nRef=0;
}

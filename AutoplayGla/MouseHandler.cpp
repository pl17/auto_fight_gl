#include <Windows.h>
#include <MsHTML.h>
#include "MouseHandler.h"

extern IWebBrowser2 *gv_wb2;

MouseHandler::MouseHandler()
{
	this->nref=0;
}

HRESULT STDMETHODCALLTYPE MouseHandler::GetTypeInfoCount( UINT *pctinfo )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE MouseHandler::GetTypeInfo( UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE MouseHandler::GetIDsOfNames( REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE MouseHandler::Invoke( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr )
{
	if ((wFlags&DISPATCH_METHOD)&&(dispIdMember==DISPID_VALUE))
	{
		IDispatch *dis;
		IHTMLDocument2 *doc2;
		IHTMLWindow2 *win2;
		IHTMLEventObj *obj;
		IHTMLElement *elm;

		gv_wb2->get_Document(&dis);
		dis->QueryInterface(IID_IHTMLDocument2, (void**)&doc2);
		doc2->get_parentWindow(&win2);
		win2->get_event(&obj);

		VARIANT_BOOL vtAlt;
		long button;
		long offsetx, offsety;
		long cx, cy, x, y;
		IHTMLElement *srcElm, *toElm;
		BSTR type;
		long sx, sy;
		long reseaon;

		obj->get_altKey(&vtAlt);
		obj->get_button(&button);
		obj->get_offsetX(&offsetx);
		obj->get_offsetY(&offsety);
		obj->get_srcElement(&srcElm);
		obj->get_clientX(&cx);
		obj->get_clientY(&cy);
		obj->get_x(&x);
		obj->get_y(&y);
		obj->get_type(&type);
		obj->get_screenX(&sx);
		obj->get_screenY(&sy);
		obj->get_toElement(&toElm);
		BSTR str;
		if (srcElm)
			srcElm->get_outerHTML(&str);
		if (toElm)
			toElm->get_outerHTML(&str);
		obj->get_reason(&reseaon);

		IHTMLEventObj2 *obj2;
		obj->QueryInterface(IID_IHTMLEventObj2, (void**)&obj2);

		IHTMLDocument3 *doc3;
		dis->QueryInterface(IID_IHTMLDocument3, (void**)&doc3);
		doc3->get_documentElement(&elm);
		obj2->putref_srcElement(elm);
		obj2->get_srcElement(&elm);



		return S_OK;
	}

	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE MouseHandler::QueryInterface( REFIID riid, void **ppvObject )
{
	if (riid==IID_IDispatch)
	{
		*ppvObject=this;
		this->AddRef();
		return S_OK;
	}
	*ppvObject=NULL;
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE MouseHandler::AddRef( void )
{
	nref++;
	return nref;
}

ULONG STDMETHODCALLTYPE MouseHandler::Release( void )
{
	nref--;
	return nref;
}

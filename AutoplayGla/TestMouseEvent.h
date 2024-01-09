#include <MsHTML.h>

class TestMouseEvent :
	public IHTMLEventObj
{
public:
	TestMouseEvent();

	virtual HRESULT STDMETHODCALLTYPE get_srcElement( IHTMLElement **p );

	virtual HRESULT STDMETHODCALLTYPE get_altKey( VARIANT_BOOL *p );

	virtual HRESULT STDMETHODCALLTYPE get_ctrlKey( VARIANT_BOOL *p );

	virtual HRESULT STDMETHODCALLTYPE get_shiftKey( VARIANT_BOOL *p );

	virtual HRESULT STDMETHODCALLTYPE put_returnValue( VARIANT v );

	virtual HRESULT STDMETHODCALLTYPE get_returnValue( VARIANT *p );

	virtual HRESULT STDMETHODCALLTYPE put_cancelBubble( VARIANT_BOOL v );

	virtual HRESULT STDMETHODCALLTYPE get_cancelBubble( VARIANT_BOOL *p );

	virtual HRESULT STDMETHODCALLTYPE get_fromElement( IHTMLElement **p );

	virtual HRESULT STDMETHODCALLTYPE get_toElement( IHTMLElement **p );

	virtual HRESULT STDMETHODCALLTYPE put_keyCode( long v );

	virtual HRESULT STDMETHODCALLTYPE get_keyCode( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_button( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_type( BSTR *p );

	virtual HRESULT STDMETHODCALLTYPE get_qualifier( BSTR *p );

	virtual HRESULT STDMETHODCALLTYPE get_reason( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_x( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_y( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_clientX( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_clientY( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_offsetX( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_offsetY( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_screenX( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_screenY( long *p );

	virtual HRESULT STDMETHODCALLTYPE get_srcFilter( IDispatch **p );

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount( UINT *pctinfo );

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo( UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo );

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames( REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId );

	virtual HRESULT STDMETHODCALLTYPE Invoke( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr );

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void **ppvObject );

	virtual ULONG STDMETHODCALLTYPE AddRef( void );

	virtual ULONG STDMETHODCALLTYPE Release( void );
protected:
	int m_nRef;
};
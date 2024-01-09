#include <ExDisp.h>

class MouseHandler :
	public IDispatch
{
public:
	int nref;

 	MouseHandler();

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount( UINT *pctinfo );

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo( UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo );

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames( REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId );

	virtual HRESULT STDMETHODCALLTYPE Invoke( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr );

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void **ppvObject );

	virtual ULONG STDMETHODCALLTYPE AddRef( void );

	virtual ULONG STDMETHODCALLTYPE Release( void );


};
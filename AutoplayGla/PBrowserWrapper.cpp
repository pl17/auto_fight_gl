#include "PBrowserWrapper.h"
#include <ExDispid.h>

PBrowserWrapper::PBrowserWrapper()
{
	this->m_nRefNum=0;
}

PBrowserWrapper::~PBrowserWrapper()
{

}


//IUnknown interface
HRESULT STDMETHODCALLTYPE PBrowserWrapper::QueryInterface( REFIID riid, void **ppvObject )
{
	*ppvObject=NULL;

	if (riid==IID_IUnknown)
	{
		*ppvObject=this;
	}


	if (*ppvObject)
	{
		this->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE PBrowserWrapper::AddRef( void )
{
	this->m_nRefNum++;
	return this->m_nRefNum;
}

ULONG STDMETHODCALLTYPE PBrowserWrapper::Release( void )
{
	this->m_nRefNum--;
	return this->m_nRefNum;
}


//IOleClientSite
HRESULT STDMETHODCALLTYPE PBrowserWrapper::SaveObject( void )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetMoniker( DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk )
{
	*ppmk=NULL;
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetContainer( IOleContainer **ppContainer )
{
	*ppContainer=NULL;
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::ShowObject( void )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::OnShowWindow( BOOL fShow )
{
	InvalidateRect(this->m_hWnd, NULL, TRUE);
	InvalidateRect(this->m_hParent, NULL, TRUE);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::RequestNewObjectLayout( void )
{
	return S_OK;
}

//IOleWindow
HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetWindow( HWND *phwnd )
{
	*phwnd=this->m_hWnd;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::ContextSensitiveHelp( BOOL fEnterMode )
{
	return E_NOTIMPL;
}


//IOleInPlaceSite
HRESULT STDMETHODCALLTYPE PBrowserWrapper::CanInPlaceActivate( void )
{
	if (this->m_bInPlace)
	{
		this->m_bCalledCanInPlace=TRUE;
		return S_OK;
	}
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::OnInPlaceActivate( void )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::OnUIActivate( void )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetWindowContext( IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo )
{
	*ppFrame=(IOleInPlaceFrame*)this;
	this->AddRef();

	*ppDoc=NULL;
	GetClientRect(this->m_hWnd, lprcPosRect);
	GetClientRect(this->m_hWnd, lprcClipRect);

	lpFrameInfo->cb=sizeof(OLEINPLACEFRAMEINFO);
	lpFrameInfo->fMDIApp=FALSE;
	lpFrameInfo->hwndFrame=this->m_hParent;
	lpFrameInfo->haccel=NULL;
	lpFrameInfo->cAccelEntries=0;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::Scroll( SIZE scrollExtant )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::OnUIDeactivate( BOOL fUndoable )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::OnInPlaceDeactivate( void )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::DiscardUndoState( void )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::DeactivateAndUndo( void )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::OnPosRectChange( LPCRECT lprcPosRect )
{
	return S_OK;
}


//IOleInPlaceUIWindow
HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetBorder( LPRECT lprectBorder )
{
	GetClientRect(this->m_hWnd, lprectBorder);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::RequestBorderSpace( LPCBORDERWIDTHS pborderwidths )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::SetBorderSpace( LPCBORDERWIDTHS pborderwidths )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::SetActiveObject( IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName )
{
	return S_OK;
}


//IOleInPlaceFrame
HRESULT STDMETHODCALLTYPE PBrowserWrapper::InsertMenus( HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::SetMenu( HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::RemoveMenus( HMENU hmenuShared )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::SetStatusText( LPCOLESTR pszStatusText )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::EnableModeless( BOOL fEnable )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::TranslateAccelerator( LPMSG lpmsg, WORD wID )
{
	return E_NOTIMPL;
}


//IDocHostUIHandler
HRESULT STDMETHODCALLTYPE PBrowserWrapper::TranslateAccelerator( LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::ShowContextMenu( DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetHostInfo( DOCHOSTUIINFO *pInfo )
{
	pInfo->cbSize=sizeof(DOCHOSTUIINFO);
	pInfo->dwFlags=DOCHOSTUIFLAG_NO3DBORDER;//No border
	pInfo->dwDoubleClick=DOCHOSTUIDBLCLK_DEFAULT;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::ShowUI( DWORD dwID, IOleInPlaceActiveObject *pActiveObject, IOleCommandTarget *pCommandTarget, IOleInPlaceFrame *pFrame, IOleInPlaceUIWindow *pDoc )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::HideUI( void )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::UpdateUI( void )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::OnDocWindowActivate( BOOL fActivate )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::OnFrameWindowActivate( BOOL fActivate )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::ResizeBorder( LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetOptionKeyPath( LPOLESTR *pchKey, DWORD dw )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetDropTarget( IDropTarget *pDropTarget, IDropTarget **ppDropTarget )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetExternal( IDispatch **ppDispatch )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::TranslateUrl( DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut )
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::FilterDataObject( IDataObject *pDO, IDataObject **ppDORet )
{
	return E_NOTIMPL;
}


//IDispatch
HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetTypeInfoCount( UINT *pctinfo )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetTypeInfo( UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo )
{
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::GetIDsOfNames( REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId )
{
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE PBrowserWrapper::Invoke( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr )
{
	HRESULT hrs;

	if (!pDispParams)
		return E_INVALIDARG;

	hrs=E_NOTIMPL;
	switch(dispIdMember)
	{
	case DISPID_NAVIGATEERROR:
		break;
	case DISPID_BEFORENAVIGATE2:
		break;
	case DISPID_NEWWINDOW3:
		break;
	case DISPID_DOCUMENTCOMPLETE:
		break;
	}

	return hrs;
}

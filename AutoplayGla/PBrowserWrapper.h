#pragma once

#include <ExDisp.h>
#include <MsHtmHst.h>

class PBrowserWrapper :
	public IUnknown,
	public IOleClientSite,
	public IOleWindow,
	public IOleInPlaceSite,
	public IOleInPlaceUIWindow,
	public IOleInPlaceFrame,
	public IDocHostUIHandler,
	public IDispatch
{
public:
	PBrowserWrapper();
	~PBrowserWrapper();

	//IUnknown interface
	virtual HRESULT STDMETHODCALLTYPE QueryInterface( REFIID riid, void **ppvObject );
	virtual ULONG STDMETHODCALLTYPE AddRef( void );
	virtual ULONG STDMETHODCALLTYPE Release( void );

	//IOleClientSite
	virtual HRESULT STDMETHODCALLTYPE SaveObject( void );
	virtual HRESULT STDMETHODCALLTYPE GetMoniker( DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk );
	virtual HRESULT STDMETHODCALLTYPE GetContainer( IOleContainer **ppContainer );
	virtual HRESULT STDMETHODCALLTYPE ShowObject( void );
	virtual HRESULT STDMETHODCALLTYPE OnShowWindow( BOOL fShow );
	virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout( void );

	//IOleWindow
	virtual HRESULT STDMETHODCALLTYPE GetWindow( HWND *phwnd );
	virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp( BOOL fEnterMode );

	//IOleInPlaceSite
	virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate( void );
	virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate( void );
	virtual HRESULT STDMETHODCALLTYPE OnUIActivate( void );
	virtual HRESULT STDMETHODCALLTYPE GetWindowContext( IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo );
	virtual HRESULT STDMETHODCALLTYPE Scroll( SIZE scrollExtant );
	virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate( BOOL fUndoable );
	virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate( void );
	virtual HRESULT STDMETHODCALLTYPE DiscardUndoState( void );
	virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo( void );
	virtual HRESULT STDMETHODCALLTYPE OnPosRectChange( LPCRECT lprcPosRect );

	//IOleInPlaceUIWindow
	virtual HRESULT STDMETHODCALLTYPE GetBorder( LPRECT lprectBorder );
	virtual HRESULT STDMETHODCALLTYPE RequestBorderSpace( LPCBORDERWIDTHS pborderwidths );
	virtual HRESULT STDMETHODCALLTYPE SetBorderSpace( LPCBORDERWIDTHS pborderwidths );
	virtual HRESULT STDMETHODCALLTYPE SetActiveObject( IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName );


	//IOleInPlaceFrame
	virtual HRESULT STDMETHODCALLTYPE InsertMenus( HMENU hmenuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths );
	virtual HRESULT STDMETHODCALLTYPE SetMenu( HMENU hmenuShared, HOLEMENU holemenu, HWND hwndActiveObject );
	virtual HRESULT STDMETHODCALLTYPE RemoveMenus( HMENU hmenuShared );
	virtual HRESULT STDMETHODCALLTYPE SetStatusText( LPCOLESTR pszStatusText );
	virtual HRESULT STDMETHODCALLTYPE EnableModeless( BOOL fEnable );
	virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( LPMSG lpmsg, WORD wID );


	//IDocHostUIHandler
	virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID );
	virtual HRESULT STDMETHODCALLTYPE ShowContextMenu( DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved );
	virtual HRESULT STDMETHODCALLTYPE GetHostInfo( DOCHOSTUIINFO *pInfo );
	virtual HRESULT STDMETHODCALLTYPE ShowUI( DWORD dwID, IOleInPlaceActiveObject *pActiveObject, IOleCommandTarget *pCommandTarget, IOleInPlaceFrame *pFrame, IOleInPlaceUIWindow *pDoc );
	virtual HRESULT STDMETHODCALLTYPE HideUI( void );
	virtual HRESULT STDMETHODCALLTYPE UpdateUI( void );
	virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate( BOOL fActivate );
	virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate( BOOL fActivate );
	virtual HRESULT STDMETHODCALLTYPE ResizeBorder( LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow );
	virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath( LPOLESTR *pchKey, DWORD dw );
	virtual HRESULT STDMETHODCALLTYPE GetDropTarget( IDropTarget *pDropTarget, IDropTarget **ppDropTarget );
	virtual HRESULT STDMETHODCALLTYPE GetExternal( IDispatch **ppDispatch );
	virtual HRESULT STDMETHODCALLTYPE TranslateUrl( DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut );
	virtual HRESULT STDMETHODCALLTYPE FilterDataObject( IDataObject *pDO, IDataObject **ppDORet );


	//IDispatch
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount( UINT *pctinfo );
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo( UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo );
	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames( REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId );
	virtual HRESULT STDMETHODCALLTYPE Invoke( DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr );


protected:
	int m_nRefNum;
	HWND m_hWnd;
	HWND m_hParent;

private:
	BOOL m_bInPlace;
	BOOL m_bExternalPlace;
	BOOL m_bCalledCanInPlace;
};
// AX.H
// messages
#define AX_QUERYINTERFACE (WM_USER + 1)
#define AX_INPLACE (WM_USER + 2)
#define AX_GETAXINTERFACE (WM_USER + 3)
#define AX_CONNECTOBJECT (WM_USER + 4)
#define AX_DISCONNECTOBJECT (WM_USER + 5)
#define AX_SETDATAADVISE (WM_USER + 6)
#define AX_DOVERB (WM_USER + 7)
#define AX_ENABLE_MENUCONTEXT	(WM_USER+8)
#define AX_SETCALLBACK_EVENTHANDLER	(WM_USER+9)

#define AX_EVENT_NEWWINDOW	0
#define AX_EVENT_DOCUMENTCOMPLETE	1
#define AX_EVENT_BEFORENAVIGATE		2
#define AX_EVENT_WINDOWCLOSING		3
#define AX_EVENT_NAVIGATEERROR		4

#include <ExDisp.h>
#include <Mshtmhst.h>
#include "PCallbackBrowser.h"

// Registration function
ATOM AXRegister();
LRESULT CALLBACK AXWndProc(HWND hh,UINT mm,WPARAM ww,LPARAM ll);
LRESULT CALLBACK AXWndProcV2(class AX *ax, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


// Class AXClientSide
class AXClientSite :
   public IOleClientSite,
   public IDispatch,
   public IAdviseSink,
   public IOleInPlaceSite,
   public IOleInPlaceFrame,
   public IDocHostUIHandler
   {
   protected:

		int refNum;
		int m_nNavigate;
		int m_nDownload;

   public:


		HWND Window;
		HWND Parent;
		HMENU Menu;
		bool InPlace;
		bool ExternalPlace;
		bool CalledCanInPlace;

		class AX* ax;

	   // MyClientSite Methods
		AXClientSite();
		virtual ~AXClientSite();
		STDMETHODIMP_(void) OnDataChange2(FORMATETC*);

		// IUnknown methods
		STDMETHODIMP QueryInterface(REFIID iid,void**ppvObject);
		STDMETHODIMP_(ULONG) AddRef();
		STDMETHODIMP_(ULONG) Release();

		// IOleClientSite methods
		STDMETHODIMP SaveObject();
		STDMETHODIMP GetMoniker(DWORD dwA,DWORD dwW,IMoniker**pm);
		STDMETHODIMP GetContainer(IOleContainer**pc);
		STDMETHODIMP ShowObject();
		STDMETHODIMP OnShowWindow(BOOL f);
		STDMETHODIMP RequestNewObjectLayout();
	
		// IAdviseSink methods
		STDMETHODIMP_(void) OnDataChange(FORMATETC *pFormatEtc,STGMEDIUM *pStgmed);
	
	   STDMETHODIMP_(void) OnViewChange(DWORD dwAspect,LONG lIndex);
	   STDMETHODIMP_(void) OnRename(IMoniker * pmk);
	   STDMETHODIMP_(void) OnSave();
	   STDMETHODIMP_(void) OnClose();
	
	   // IOleInPlaceSite methods
	   STDMETHODIMP GetWindow(HWND *p);
	   STDMETHODIMP ContextSensitiveHelp(BOOL);
	   STDMETHODIMP CanInPlaceActivate();
	   STDMETHODIMP OnInPlaceActivate();
	   STDMETHODIMP OnUIActivate();
	   STDMETHODIMP GetWindowContext(IOleInPlaceFrame** ppFrame,IOleInPlaceUIWindow **ppDoc,LPRECT r1,LPRECT r2,LPOLEINPLACEFRAMEINFO o);
	   STDMETHODIMP Scroll(SIZE s);
	   STDMETHODIMP OnUIDeactivate(int);
	   STDMETHODIMP OnInPlaceDeactivate();
	   STDMETHODIMP DiscardUndoState();
	   STDMETHODIMP DeactivateAndUndo();
	   STDMETHODIMP OnPosRectChange(LPCRECT);
	
	   // IOleInPlaceFrame methods
	   STDMETHODIMP GetBorder(LPRECT l);
	   STDMETHODIMP RequestBorderSpace(LPCBORDERWIDTHS);
	   STDMETHODIMP SetBorderSpace(LPCBORDERWIDTHS w);
	   STDMETHODIMP SetActiveObject(IOleInPlaceActiveObject*pV,LPCOLESTR s);
	   STDMETHODIMP InsertMenus(HMENU h,LPOLEMENUGROUPWIDTHS x);
	   STDMETHODIMP SetMenu(HMENU h,HOLEMENU hO,HWND hw);
	   STDMETHODIMP RemoveMenus(HMENU h);
	   STDMETHODIMP SetStatusText(LPCOLESTR t);
	   STDMETHODIMP EnableModeless(BOOL f);
	   STDMETHODIMP TranslateAccelerator(LPMSG,WORD);

	   virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID );


	
	   // IDispatch Methods
	   HRESULT _stdcall GetTypeInfoCount(unsigned int * pctinfo);

	   HRESULT _stdcall GetTypeInfo(unsigned int iTInfo,LCID lcid,ITypeInfo FAR* FAR* ppTInfo);

	   HRESULT _stdcall GetIDsOfNames(REFIID riid,OLECHAR FAR* FAR*,unsigned int cNames,LCID lcid,DISPID FAR* );

	   HRESULT _stdcall Invoke(DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS FAR* pDispParams,VARIANT FAR* pVarResult,EXCEPINFO FAR* pExcepInfo,unsigned int FAR* puArgErr);

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

		// IOleControlSite Methods
   };



// Class AX
class AX
	{
	public:

		AX(char* clsid);
	   CLSID GetCLSID();
		~AX();


		void Init(char* clsid);
		void Clean();

		AXClientSite Site;
		IID* iid;
	   IOleObject* OleObject;
	   IStorage* Storage;
	   IViewObject* View;
	   IDataObject* Data;
	   IUnknown* Unk;
	   IOleInPlaceActiveObject* Pao;
	   HANDLE hevFree;
	   //AX_CONNECTSTRUCT* tcs;
	   bool AddMenu;
	   DWORD AdviseToken;
		DWORD DAdviseToken[100];

		bool bEnableMenuContext;

		AX_CallbackEventHandler ehOnDocumentComplete;
		AX_CallbackEventHandler ehOnNewWindow;
		AX_CallbackEventHandler ehOnWindowClosing;
		AX_CallbackEventHandler ehOnBeforeNavigate;
		AX_CallbackEventHandler ehOnNavigateError;

		class PCallbackBrowser *pcbOnDocumentComplete;


	private:

		CLSID clsid;


	};
	


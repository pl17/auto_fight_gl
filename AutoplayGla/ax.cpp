
// AX.CPP

#include <windows.h>
#include <comdef.h>
#include <exdisp.h>
#include <oledlg.h>
#include <exdispid.h>
#include <MsHTML.h>
#include <WinInet.h>
#include <atltypes.h>
#include <atlbase.h>
#pragma comment(lib, "wininet.lib")
#include "ax.h"
#include "Logs.h"

#pragma warning (disable: 4311)
#pragma warning (disable: 4312)
#pragma warning (disable: 4244)
#pragma warning (disable: 4800)

extern IOutputDebug *gv_dbgConsole;

// AXClientSite class
// ------- Implement member functions
AXClientSite :: AXClientSite()
{
	refNum = 0;
	CalledCanInPlace = 0;
	InPlace = 0;

	this->m_nDownload=0;
	this->m_nNavigate=0;
}

AXClientSite :: ~AXClientSite()
{
}


// IUnknown methods
STDMETHODIMP AXClientSite :: QueryInterface(REFIID iid,void**ppvObject)
{
	*ppvObject = 0;
	if (iid == IID_IOleClientSite)
		*ppvObject = (IOleClientSite*)this;
	if (iid == IID_IUnknown)
		*ppvObject = this;
	if (iid == IID_IAdviseSink)
		*ppvObject = (IAdviseSink*)this;
	if (iid == IID_IDispatch)
		*ppvObject = (IDispatch*)this;
	if (iid==IID_IDocHostUIHandler)
		*ppvObject=(IDocHostUIHandler*)this;
	if (ExternalPlace == false)
	{
		if (iid == IID_IOleInPlaceSite)
			*ppvObject = (IOleInPlaceSite*)this;
		if (iid == IID_IOleInPlaceFrame)
			*ppvObject = (IOleInPlaceFrame*)this;
		if (iid == IID_IOleInPlaceUIWindow)
			*ppvObject = (IOleInPlaceUIWindow*)this;
	}
	
	//* Log Call
	if (*ppvObject)
	{
		AddRef();
		return S_OK;
	}
	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG)  AXClientSite :: AddRef()
{
	refNum++;
	return refNum;
}

STDMETHODIMP_(ULONG)  AXClientSite :: Release()
{
	refNum--;
	return refNum;
}


// IOleClientSite methods
STDMETHODIMP AXClientSite :: SaveObject()
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: GetMoniker(DWORD dwA,DWORD dwW,IMoniker**pm)
{
	*pm = 0;
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: GetContainer(IOleContainer**pc)
{
	*pc = 0;
	return E_NOINTERFACE;
}

STDMETHODIMP AXClientSite :: ShowObject()
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: OnShowWindow(BOOL f)
{
	InvalidateRect(Window, 0, TRUE);
	InvalidateRect(Parent, 0, TRUE);
	return S_OK;
}

STDMETHODIMP AXClientSite :: RequestNewObjectLayout()
{
	return S_OK;
}

STDMETHODIMP_(void) AXClientSite :: OnViewChange(DWORD dwAspect,LONG lIndex)
{
}

STDMETHODIMP_(void) AXClientSite :: OnRename(IMoniker * pmk)
{
}

STDMETHODIMP_(void) AXClientSite :: OnSave()
{
}

STDMETHODIMP_(void) AXClientSite :: OnClose()
{
}


// IOleInPlaceSite methods
STDMETHODIMP AXClientSite :: GetWindow(HWND *p)
{
	*p = Window;
	return S_OK;
}

STDMETHODIMP AXClientSite :: ContextSensitiveHelp(BOOL)
{
	return E_NOTIMPL;
}


STDMETHODIMP AXClientSite :: CanInPlaceActivate()
{
	if (InPlace)
	{
		CalledCanInPlace = true;
		return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP AXClientSite :: OnInPlaceActivate()
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: OnUIActivate()
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: GetWindowContext(IOleInPlaceFrame** ppFrame,IOleInPlaceUIWindow **ppDoc,LPRECT r1,LPRECT r2,LPOLEINPLACEFRAMEINFO o)
{
	*ppFrame = (IOleInPlaceFrame*)this;
	AddRef();

	*ppDoc = NULL;
	GetClientRect(Window,r1);
	GetClientRect(Window,r2);
	r1->left=0;
	r1->top=0;
	r1->bottom=800;
	r1->right=1000;

	r2->left=0;
	r2->top=0;
	r2->bottom=600;
	r2->right=1024;
	o->cb = sizeof(OLEINPLACEFRAMEINFO);
	o->fMDIApp = false;
	o->hwndFrame = Parent;
	o->haccel = 0;
	o->cAccelEntries = 0;

	return S_OK;
}

STDMETHODIMP AXClientSite :: Scroll(SIZE s)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: OnUIDeactivate(int)
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: OnInPlaceDeactivate()
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: DiscardUndoState()
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: DeactivateAndUndo()
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: OnPosRectChange(LPCRECT)
{
	return S_OK;
}


// IOleInPlaceFrame methods
STDMETHODIMP AXClientSite :: GetBorder(LPRECT l)
{
	GetClientRect(Window,l);
	return S_OK;
}

STDMETHODIMP AXClientSite :: RequestBorderSpace(LPCBORDERWIDTHS b)
{
	//return S_OK;
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: SetBorderSpace(LPCBORDERWIDTHS b)
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: SetActiveObject(IOleInPlaceActiveObject*pV,LPCOLESTR s)
{
	ax->Pao = pV;
	return S_OK;
}


STDMETHODIMP AXClientSite :: SetStatusText(LPCOLESTR t)
{
	if (t) *(WCHAR*)t=NULL;
	return S_OK;
}

STDMETHODIMP AXClientSite :: EnableModeless(BOOL f)
{
	return S_OK;
}

STDMETHODIMP AXClientSite :: TranslateAccelerator(LPMSG lpMsg,WORD abc)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE AXClientSite::TranslateAccelerator( LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID )
{
	return E_NOTIMPL;
}


// IDispatch Methods
HRESULT _stdcall AXClientSite :: GetTypeInfoCount(
	unsigned int * pctinfo) {*pctinfo=NULL; return S_OK;}


HRESULT _stdcall AXClientSite :: GetTypeInfo(
	unsigned int iTInfo,
	LCID lcid,
	ITypeInfo FAR* FAR* ppTInfo) {return E_FAIL;}


HRESULT _stdcall AXClientSite :: GetIDsOfNames(
	REFIID riid,
	OLECHAR FAR* FAR*,
	unsigned int cNames,
	LCID lcid,
	DISPID FAR* ) {return E_FAIL;}



// Other Methods
void AX :: Init(char* cls)
{
	wchar_t x[1000] = {0};
	MultiByteToWideChar(CP_ACP,0,cls,-1,x,1000);
	CLSIDFromString(x,&clsid);
	iid = (IID*)&IID_IOleObject;
	OleObject = 0;
	Storage = 0;
	View = 0;
	Data = 0;
	Unk = 0;
	Pao = 0;
	AdviseToken = 0;
	memset(DAdviseToken,0,sizeof(DAdviseToken));
	Site.ax = this;

	this->bEnableMenuContext=true;

	this->ehOnBeforeNavigate=NULL;
	this->ehOnDocumentComplete=NULL;
	this->ehOnNewWindow=NULL;
	this->ehOnWindowClosing=NULL;
	this->ehOnNavigateError=NULL;
	this->pcbOnDocumentComplete=NULL;
	this->hevFree=CreateEvent(NULL, FALSE, FALSE, NULL);

	//   this->OleObject->Advise()
	// DISP_FUNCTION_ID(this, TEXT("DocumentComplete"), DISPID_DOCUMENTCOMPLETE, NULL, NULL, NULL, NULL);
}

AX :: AX(char* cls)
{
	Init(cls);
}



void AX :: Clean()
{
	if (Site.InPlace == true)
	{
		Site.InPlace = false;
		IOleInPlaceObject* iib = 0;
		if (OleObject)
			OleObject->QueryInterface(IID_IOleInPlaceObject,(void**)&iib);
		if (iib)
		{
			iib->UIDeactivate();
			iib->InPlaceDeactivate();
			iib->Release();
		}
	}

	if (AdviseToken && OleObject)
	{
		OleObject->Unadvise(AdviseToken);
		AdviseToken = 0;
	}
	if (Data)
	{
		for(int i = 0 ; i < 100 ; i++)
			if (DAdviseToken[i])
				Data->DUnadvise(DAdviseToken[i]);
		memset(DAdviseToken,0,sizeof(DAdviseToken));
	}


	if (Pao) Pao->Release();
	if (Unk) Unk->Release();
	if (Data) Data->Release();
	if (View) View->Release();
	if (Storage) Storage->Release();
	if (OleObject) OleObject->Release();
	Unk = 0;
	Data = 0;
	View = 0;
	Storage = 0;
	OleObject = 0;

}

AX :: ~AX()
{
	Clean();
}

CLSID AX :: GetCLSID()
{
	CloseHandle(this->hevFree);
	return clsid;
}

HRESULT _stdcall AXClientSite :: InsertMenus(HMENU h,LPOLEMENUGROUPWIDTHS x)
{
	/*      AX * t = (AX*)ax;
	if (t->AddMenu)
	{
	x->width[0] = 0;
	x->width[2] = 0;
	x->width[4] = 0;
	//InsertMenu(h,0,MF_BYPOSITION | MF_POPUP,(int)Menu,"test");
	return S_OK;
	}
	*/
	return E_NOTIMPL;
}
HRESULT _stdcall AXClientSite :: SetMenu(HMENU h,HOLEMENU hO,HWND hw)
{
	AX * t = (AX*)ax;
	/*      if (t->AddMenu)
	{
	if (!h && !hO)
	{
	//::SetMenu(Window,Menu);
	//DrawMenuBar(Window);
	::SetMenu(Parent,Menu);
	DrawMenuBar(Parent);
	return S_OK;
	}

	//::SetMenu(Window,h);
	//DrawMenuBar(Window);

	//HMENU hm = GetMenu(Parent);
	//AppendMenu(hm,MF_POPUP | MF_MENUBREAK,(int)h,0);
	//::SetMenu(Parent,hm);
	::SetMenu(Parent,h);
	DrawMenuBar(Parent);

	//hOleWindow = hw;
	//OleSetMenuDescriptor(hO,Window,hw,0,0);
	OleSetMenuDescriptor(hO,Parent,hw,0,0);

	return S_OK;
	}
	*/
	return E_NOTIMPL;
}

HRESULT _stdcall AXClientSite :: RemoveMenus(HMENU h)
{
	AX * t = (AX*)ax;
	if (t->AddMenu)
	{
		if (!h)
			return S_OK;

		int c = GetMenuItemCount(h);
		for (int i = c ; i >= 0 ; i--)
		{
			HMENU hh = GetSubMenu(h,i);
			if (hh == Menu)
				RemoveMenu(h,i,MF_BYPOSITION);
		}
		if (h == Menu)
			DestroyMenu(h);

		//DrawMenuBar(Window);
		DrawMenuBar(Parent);
		return S_OK;
	}
	return E_NOTIMPL;
}

bool finish=false;

void ResizeIe1(HWND hParent, HWND hChild, int height, int width)
{
	HWND hIe;

	hIe=GetDlgItem(hParent, 10011);
	if (hIe==NULL) return;

	RECT rcParent;
	GetWindowRect(hParent, &rcParent);
	if (height==0 || width==0) return;
	//SetWindowPos(hParent, hParent, rcParent.left, rcParent.top, rcParent.left+width+5, rcParent.top+height+5, SWP_SHOWWINDOW);
	MoveWindow(hParent, rcParent.left, rcParent.top, width, height, TRUE);

	RECT rc;

	GetClientRect(hParent, &rc);
	//SetWindowPos(hChild, 0, 0, 0, rcParent.right, rcParent.bottom, SWP_SHOWWINDOW);
	MoveWindow(hChild, 0, 0, rc.right, rc.bottom, TRUE);
}

HRESULT _stdcall AXClientSite :: Invoke(
										DISPID dispIdMember,
										REFIID riid,
										LCID lcid,
										WORD wFlags,
										DISPPARAMS FAR* pDispParams,
										VARIANT FAR* pVarResult,
										EXCEPINFO FAR* pExcepInfo,
										unsigned int FAR* puArgErr)

{
	if (!pDispParams) return E_INVALIDARG;

	IWebBrowser2 *wb;
	HRESULT rs;
	AX_CallbackEventHandler pFunc;

	pFunc=NULL;

	if (dispIdMember==DISPID_NAVIGATEERROR)
	{
		pFunc=this->ax->ehOnNavigateError;
		
		this->ax->OleObject->QueryInterface(IID_IWebBrowser2, (void**)&wb);
		if (wb)
		{
			wb->Refresh();
			wb->Release();
		}
	}
	if (dispIdMember==DISPID_WINDOWCLOSING)
	{
		pFunc=this->ax->ehOnWindowClosing;
	}
	if (dispIdMember==DISPID_BEFORENAVIGATE)
	{

	}
	if (dispIdMember==DISPID_BEFORENAVIGATE2)
	{
		pFunc=this->ax->ehOnBeforeNavigate;
		this->ax->OleObject->QueryInterface(IID_IWebBrowser2, (void**)&wb);
		if (wb)
		{
			VARIANT_BOOL vb;
			wb->get_Busy(&vb);
			if (vb==VARIANT_TRUE)
			{
				pDispParams->rgvarg[0].boolVal=VARIANT_TRUE;
				OutputDebugString(TEXT("Browser: Waitting hehe\n"));
			}
			wb->Release();
		}
	}
	if (dispIdMember==DISPID_NAVIGATECOMPLETE2)
	{
		
	}

	if (dispIdMember==DISPID_NEWWINDOW3)
	{
		pFunc=this->ax->ehOnNewWindow;
		/*
		this->ax->OleObject->QueryInterface(IID_IWebBrowser2, (void**)&wb);
		//wb->Quit();
		wb->Navigate((TCHAR*)pDispParams->rgvarg[0].bstrVal, NULL, NULL, NULL, NULL);
		*pDispParams->rgvarg[3].pboolVal=VARIANT_TRUE;
		*/
	}
	if (dispIdMember==DISPID_DOCUMENTCOMPLETE)
	{
		if (wcsstr((TCHAR*)pDispParams->rgvarg[0].pvarVal->bstrVal, TEXT("gladiatus"))==NULL)
			return S_OK;
		//pFunc=this->ax->ehOnDocumentComplete;
		this->ax->OleObject->QueryInterface(IID_IWebBrowser2, (void**)&wb);
		this->ax->pcbOnDocumentComplete->ExecuteAll(wb, pDispParams);
		wb->Release();
		/*
		VARIANT *vt;
		vt=(VARIANT*)pDispParams->rgvarg[0].byref;

		IHTMLDocument2 *doc2;
		HRESULT hr;
		doc2=NULL;

		if (wb)
		{

		IDispatch *dis;
		hr=wb->get_Document(&dis);
		dis->QueryInterface(&doc2);

		if (doc2)
		{
		IHTMLElement *lpBodyElm, *lpParentElm;
		long offsetX, offsetY;

		doc2->get_body(&lpBodyElm);
		lpBodyElm->get_offsetWidth(&offsetX);
		lpBodyElm->get_offsetHeight(&offsetY);

		//BSTR str;
		//doc2->get_cookie(&str);
		//OutputDebugString((TCHAR*)str);

		//ResizeIe1(this->Parent, this->Window, offsetY, offsetX);

		lpBodyElm->get_parentElement(&lpParentElm);
		BSTR str;
		lpParentElm->get_innerText(&str);
		OutputDebugString((TCHAR*)str);
		*/
	}

	if (pFunc!=NULL)
	{
		this->ax->OleObject->QueryInterface(IID_IWebBrowser2, (void**)&wb);
		//rs=pFunc(wb, pDispParams);
		//rs=pFunc(wb, pDispParams);
		if (dispIdMember==DISPID_DOCUMENTCOMPLETE)
		{
			if (rs==S_OK)
			{
				wb->Quit();
				//PostMessage(this->Parent, WM_CLOSE, 0, 0);
			}
			else if (rs==S_FALSE)
				rs=S_OK;
		}
		wb->Release();
	}
	else
		rs=DISP_E_MEMBERNOTFOUND;

	return rs;
}


void _stdcall AXClientSite :: OnDataChange(FORMATETC *pFormatEtc,STGMEDIUM *pStgmed)
{
	// Notify our app that a change is being requested
	return;
}

HRESULT STDMETHODCALLTYPE AXClientSite::ShowContextMenu( DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved )
{
	if (this->ax->bEnableMenuContext)
		return E_NOTIMPL;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::GetHostInfo( DOCHOSTUIINFO *pInfo )
{
	pInfo->cbSize=sizeof(DOCHOSTUIINFO);
	pInfo->dwFlags=DOCHOSTUIFLAG_NO3DBORDER;
	pInfo->dwDoubleClick=DOCHOSTUIDBLCLK_DEFAULT;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::ShowUI( DWORD dwID, IOleInPlaceActiveObject *pActiveObject, IOleCommandTarget *pCommandTarget, IOleInPlaceFrame *pFrame, IOleInPlaceUIWindow *pDoc )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::HideUI( void )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::UpdateUI( void )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::OnDocWindowActivate( BOOL fActivate )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::OnFrameWindowActivate( BOOL fActivate )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::ResizeBorder( LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE AXClientSite::GetOptionKeyPath( LPOLESTR *pchKey, DWORD dw )
{
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE AXClientSite::GetDropTarget( IDropTarget *pDropTarget, IDropTarget **ppDropTarget )
{
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE AXClientSite::GetExternal( IDispatch **ppDispatch )
{
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE AXClientSite::TranslateUrl( DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut )
{
	*ppchURLOut=NULL;
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE AXClientSite::FilterDataObject( IDataObject *pDO, IDataObject **ppDORet )
{
	return S_FALSE;
}

// Window Procedure for AX control
LRESULT CALLBACK AXWndProc(HWND hh,UINT mm,WPARAM ww,LPARAM ll)
{
	if (mm==AX_SETCALLBACK_EVENTHANDLER)
	{
		AX* ax;
		ax=(AX*)GetWindowLong(hh, GWL_USERDATA);
		switch(ww)
		{
		case AX_EVENT_DOCUMENTCOMPLETE:
			//ax->ehOnDocumentComplete=(AX_CallbackEventHandler)ll;
			ax->pcbOnDocumentComplete=(PCallbackBrowser*)ll;
			break;
		case AX_EVENT_NEWWINDOW:
			ax->ehOnNewWindow=(AX_CallbackEventHandler)ll;
			break;
		case AX_EVENT_NAVIGATEERROR:
			ax->ehOnNavigateError=(AX_CallbackEventHandler)ll;
			break;
		case AX_EVENT_BEFORENAVIGATE:
			ax->ehOnBeforeNavigate=(AX_CallbackEventHandler)ll;
			break;
		}

		return 0;
	}

	if (mm == WM_CREATE)
	{
		char tit[1000] = {0};
		HRESULT hr;

		GetWindowTextA(hh,tit,1000);

		AX* ax;
		ax = new AX(tit);

		SetWindowLong(hh,GWL_USERDATA,(LONG)ax);
		ax->Site.Window = hh;
		ax->Site.Parent = GetParent(hh);

		hr = StgCreateDocfile(0,STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE,0,&ax->Storage);
		ax->Site.Window = hh;

		REFIID rid = *ax->iid;
		hr = OleCreate(ax->GetCLSID(),rid,OLERENDER_DRAW,0,&ax->Site,ax->Storage,(void**)&ax->OleObject);



		if (!ax->OleObject)
		{
			delete ax;
			SetWindowLong(hh,GWL_USERDATA,0);
			return -1;
		}

		hr = OleSetContainedObject(ax->OleObject, TRUE);
		hr = ax->OleObject->Advise(&ax->Site,&ax->AdviseToken);
		hr = ax->OleObject->QueryInterface(IID_IViewObject,(void**)&ax->View);
		hr = ax->OleObject->QueryInterface(IID_IDataObject,(void**)&ax->Data);
		if (ax->View)
			hr = ax->View->SetAdvise(DVASPECT_CONTENT,0,&ax->Site);



		return 0;
	}



	if (mm == WM_DESTROY)
	{
		AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
		if (!ax)
			return 0;
		ax->Clean();
		
		return true;
	}

	if (mm==AX_ENABLE_MENUCONTEXT)
	{
		AX* ax=(AX*)GetWindowLong(hh, GWL_USERDATA);
		if (ww==0)
		{
			ax->bEnableMenuContext=false;
		}
		else
			ax->bEnableMenuContext=true;

		return 0;
	}

	if (mm == AX_SETDATAADVISE)
	{
		AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
		if (!ax)
			return 0;

		// 1.Enum available FORMATETC structures
		// 2.Set Data Advise specified to index ww
		if (!ax->Data)
			return 0;

		IEnumFORMATETC* ief = 0;
		int i = 0;

		FORMATETC fe;
		ax->Data->EnumFormatEtc((LPARAM)ll,&ief);
		if (!ief)
			return 0;
		for(;;)
		{
			HRESULT hr = ief->Next(1,&fe,0);
			if (hr != S_OK)
				break;
			if (ww == i)
				break;
			i++;
		}
		ief->Release();
		if (ww == -1)
			return i;

		if (ax->Data)
			ax->Data->DAdvise(&fe,0,&ax->Site,&ax->DAdviseToken[ww]);

		return true;
	}

	if (mm == AX_GETAXINTERFACE)
	{
		AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
		return (LONG)ax;
	}

	if (mm == AX_QUERYINTERFACE)
	{
		char* p = (char*)ww;
		AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
		if (!ax)
			return 0;
		return ax->OleObject->QueryInterface((REFIID)*p,(void**)ll);
	}

	if (mm == WM_LBUTTONDBLCLK)
	{
		PostMessage(hh,AX_INPLACE,1,0);
		return 0;
	}


	if (mm == AX_INPLACE)
	{
		AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
		if (!ax)
			return 0;
		if (!ax->OleObject)
			return 0;
		RECT rect;
		HRESULT hr;
		::GetClientRect(hh,&rect);

		if (ax->Site.InPlace == false && ww == 1) // Activate In Place
		{
			ax->Site.InPlace = true;
			ax->Site.ExternalPlace = ll;
			hr = ax->OleObject->DoVerb(OLEIVERB_INPLACEACTIVATE,0,&ax->Site,0,hh,&rect);
			InvalidateRect(hh,0,true);
			return 1;
		}

		if (ax->Site.InPlace == true && ww == 0) // Deactivate
		{
			ax->Site.InPlace = false;

			IOleInPlaceObject* iib;
			ax->OleObject->QueryInterface(IID_IOleInPlaceObject,(void**)&iib);
			if (iib)
			{
				iib->UIDeactivate();
				iib->InPlaceDeactivate();
				iib->Release();
				InvalidateRect(hh,0,true);
				return 1;
			}
		}
		return 0;
	}

	if (mm == WM_SIZE)
	{
		return 0;
		AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
		if (!ax)
			return 0;
		if (!ax->OleObject)
			return 0;

		DefWindowProc(hh,mm,ww,ll);

		if (ax->Site.InPlace == true)
		{
			SendMessage(hh,AX_INPLACE,0,0);
			InvalidateRect(hh,0,true);
			SendMessage(hh,AX_INPLACE,1,0);
		}

		IOleInPlaceObject* pl;
		ax->OleObject->QueryInterface(IID_IOleInPlaceObject,(void**)&pl);
		if (!pl)
			return 0;
		RECT r;
		GetClientRect(ax->Site.Window,&r);
		pl->SetObjectRects(&r,&r);
		pl->Release();
		return 0;
	}

	return DefWindowProc(hh,mm,ww,ll);
}

// Registration function
ATOM AXRegister()
{
	WNDCLASSEXA wC = {0};

	wC.cbSize = sizeof(wC);
	wC.style = CS_GLOBALCLASS | CS_DBLCLKS;
	wC.lpfnWndProc = AXWndProc;
	wC.cbWndExtra = 4;
	wC.hInstance = GetModuleHandle(0);
	wC.lpszClassName = "AX";
	return RegisterClassExA(&wC);
}

LRESULT CALLBACK AXWndProcV2(AX *ax, HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HRESULT hr;

	switch(msg)
	{
	case WM_CREATE:
		IUnknown *iu;


		ax->Site.Window = hWnd;
		ax->Site.Parent = GetParent(hWnd);

		hr = StgCreateDocfile(0,STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE,0,&ax->Storage);
		ax->Site.Window = hWnd;

		hr = OleCreate(ax->GetCLSID(),(REFIID)(*ax->iid),OLERENDER_DRAW,0,&ax->Site,ax->Storage,(void**)&ax->OleObject);
		hr = OleSetContainedObject(ax->OleObject, TRUE);
		hr = ax->OleObject->Advise(&ax->Site,&ax->AdviseToken);
		hr = ax->OleObject->QueryInterface(IID_IViewObject,(void**)&ax->View);
		hr = ax->OleObject->QueryInterface(IID_IDataObject,(void**)&ax->Data);
		if (ax->View)
			hr = ax->View->SetAdvise(DVASPECT_CONTENT,0,&ax->Site);
		
		ax->OleObject->QueryInterface(IID_IUnknown, (void**)&iu);
		DWORD dwCookie;
		AtlAdvise((IUnknown*)ax, iu, DIID_DWebBrowserEvents2, &dwCookie);
		iu->Release();

		return 0;

	case AX_SETCALLBACK_EVENTHANDLER:
		switch(wParam)
		{
		case AX_EVENT_DOCUMENTCOMPLETE:
			ax->pcbOnDocumentComplete=(PCallbackBrowser*)lParam;
			break;
		}
		return 0;

	case WM_DESTROY:
		ax->Clean();
		return 1;

	case AX_ENABLE_MENUCONTEXT:
		ax->bEnableMenuContext=(bool)wParam;
		break;
	case AX_SETDATAADVISE:
		IEnumFORMATETC* ief;
		int i;
		FORMATETC fe;

		i=0;
		ief=0;
		ax->Data->EnumFormatEtc((LPARAM)lParam,&ief);
		if (!ief)
			return 0;
		for(;;)
		{
			HRESULT hr = ief->Next(1,&fe,0);
			if (hr != S_OK)
				break;
			if (wParam == i)
				break;
			i++;
		}
		ief->Release();
		if (wParam == -1)
			return i;

		if (ax->Data)
			ax->Data->DAdvise(&fe,0,&ax->Site,&ax->DAdviseToken[wParam]);

		return 1;

	case WM_LBUTTONDBLCLK:
		PostMessage(hWnd, AX_INPLACE, 1, 0);
		return 0;

	case AX_INPLACE:
		RECT rect;
		GetClientRect(hWnd,&rect);

		if (ax->Site.InPlace == false && wParam == 1) // Activate In Place
		{
			ax->Site.InPlace = true;
			ax->Site.ExternalPlace = lParam;
			hr = ax->OleObject->DoVerb(OLEIVERB_INPLACEACTIVATE,0,&ax->Site,0,hWnd,&rect);
			InvalidateRect(hWnd,0,true);
			return 1;
		}

		if (ax->Site.InPlace == true && wParam == 0) // Deactivate
		{
			ax->Site.InPlace = false;

			IOleInPlaceObject* iib;
			ax->OleObject->QueryInterface(IID_IOleInPlaceObject,(void**)&iib);
			if (iib)
			{
				iib->UIDeactivate();
				iib->InPlaceDeactivate();
				iib->Release();
				InvalidateRect(hWnd,0,true);
				return 1;
			}
		}
		return 0;

	case WM_SIZE:
		DefWindowProc(hWnd,msg,wParam,lParam);

		if (ax->Site.InPlace == true)
		{
			SendMessage(hWnd,AX_INPLACE,0,0);
			InvalidateRect(hWnd,0,true);
			SendMessage(hWnd,AX_INPLACE,1,0);
		}

		IOleInPlaceObject* pl;
		ax->OleObject->QueryInterface(IID_IOleInPlaceObject,(void**)&pl);
		if (!pl)
			return 0;
		RECT r;
		GetClientRect(ax->Site.Window,&r);
		pl->SetObjectRects(&r,&r);
		pl->Release();
		return 0;
	}


	return DefWindowProc(hWnd,msg,wParam,lParam);
}

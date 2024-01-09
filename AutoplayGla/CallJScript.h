bool GetJScript(IHTMLDocument2 *m_spDoc, IDispatch** spDisp)
{
	HRESULT hr = m_spDoc->get_Script(spDisp);
	
	//ATLASSERT(SUCCEEDED(hr));
	return SUCCEEDED(hr);
}

VARIANT CallJScript(IHTMLDocument2 *m_spDoc, const TCHAR *strFunc,
								  const TCHAR **paramArray, int nParamCount)
{
	//Getting IDispatch for Java Script objects
	IDispatch *spScript;
	VARIANT vaResult;
	
	if(!GetJScript(m_spDoc, &spScript))
	{
		vaResult.boolVal=TRUE;
		vaResult.vt=VT_BOOL;
		return vaResult;
	}
	//Find dispid for given function in the object
	BSTR bstrMember((BSTR)strFunc);
	DISPID dispid = NULL;
	HRESULT hr = spScript->GetIDsOfNames(IID_NULL,&bstrMember,1,
		LOCALE_SYSTEM_DEFAULT,&dispid);
	if(FAILED(hr))
	{
		vaResult.boolVal=FALSE;
		vaResult.vt=VT_BOOL;
		return vaResult;
	}

	const int arraySize = nParamCount;
	//Putting parameters  
	DISPPARAMS dispparams;
	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs      = arraySize;
	dispparams.rgvarg     = new VARIANT[dispparams.cArgs];
	dispparams.cNamedArgs = 0;

	for( int i = 0; i < arraySize; i++)
	{
		BSTR bstr = (BSTR)paramArray[arraySize - 1 - i]; // back reading
		//bstrCopyTo(&dispparams.rgvarg[i].bstrVal);
		//CopyMemory(dispparams.rgvarg[i].bstrVal, bstr, _tcslen((TCHAR*)bstr));
		dispparams.rgvarg[i].bstrVal=bstr;
		
		dispparams.rgvarg[i].vt = VT_BSTR;
	}
	EXCEPINFO excepInfo;
	memset(&excepInfo, 0, sizeof excepInfo);
	
	UINT nArgErr = (UINT)-1;  // initialize to invalid arg
	//Call JavaScript function         
	hr = spScript->Invoke(dispid,IID_NULL,0,
		DISPATCH_METHOD,&dispparams,
		&vaResult,&excepInfo,&nArgErr);
	delete [] dispparams.rgvarg;
	if(FAILED(hr))
	{
		vaResult.boolVal=FALSE;
		vaResult.vt=VT_BOOL;
		return vaResult;
	}
	return vaResult;
}

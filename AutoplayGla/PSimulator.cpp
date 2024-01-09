#include <MsHTML.h>
#include <excpt.h>
#include "PSimulator.h"
#include "PXPath.h"

int psSimulatorClick(IHTMLDocument3 *doc3, const GAMEOBJ_XPATH *xpath)
{
	IHTMLDOMNode *node;
	int irs;

	irs=0;

	if (doc3)
	{
		node=pxpGetXPathNode(doc3, xpath);
		if (node)
		{
			irs=psSimulatorClick(node);
			node->Release();
		}
	}

	return irs;
}

int psSimulatorClick(IHTMLDOMNode *node)
{
	IHTMLElement *pElm;
	int nrs;
	HRESULT hr;

	nrs=0;

	if (node)
	{
		hr=node->QueryInterface(IID_IHTMLElement, (void**)&pElm);
		if (hr==S_OK)
		{
			OutputDebugString(TEXT("Day la click\n"));
			if (pElm->click()==S_OK)
				nrs=1;
			//pElm->Release();
		}
	}

	return nrs;
}

#include "ActionSimulator.h"

BOOL ActionSimulator::Click( IHTMLElement *elm, long offsetX, long offsetY )
{
	return ActionSimulator::_Action(elm, TEXT("onclick"), offsetX, offsetY);
}

BOOL ActionSimulator::Click( IHTMLElement *elm )
{
	return ActionSimulator::_Action(elm, TEXT("onclick"));
}

BOOL ActionSimulator::Click( IHTMLDOMNode *node, long offsetX, long offsetY )
{
	return ActionSimulator::_Action(node, TEXT("onclick"), offsetX, offsetY);
}

BOOL ActionSimulator::Click( IHTMLDOMNode *node )
{
	return ActionSimulator::_Action(node, TEXT("onclick"));
}

BOOL ActionSimulator::MouseDown( IHTMLElement *elm, long offsetX, long offsetY )
{
	return ActionSimulator::_Action(elm, TEXT("onmousedown"), offsetX, offsetY);
}

BOOL ActionSimulator::MouseDown( IHTMLElement *elm )
{
	return ActionSimulator::_Action(elm, TEXT("onmousedown"));
}

BOOL ActionSimulator::MouseDown( IHTMLDOMNode *node, long offsetX, long offsetY )
{
	return ActionSimulator::_Action(node, TEXT("onmousedown"), offsetX, offsetY);
}

BOOL ActionSimulator::MouseDown( IHTMLDOMNode *node )
{
	return ActionSimulator::_Action(node, TEXT("onmousedown"));
}

BOOL ActionSimulator::MouseMove( IHTMLElement *elm, long offsetX, long offsetY )
{
	return ActionSimulator::_Action(elm, TEXT("onmousemove"), offsetX, offsetY);
}

BOOL ActionSimulator::MouseMove( IHTMLElement *elm )
{
	return ActionSimulator::_Action(elm, TEXT("onmousemove"));
}

BOOL ActionSimulator::MouseMove( IHTMLDOMNode *node, long offsetX, long offsetY )
{
	return ActionSimulator::_Action(node, TEXT("onmousemove"), offsetX, offsetY);
}

BOOL ActionSimulator::MouseMove( IHTMLDOMNode *node )
{
	return ActionSimulator::_Action(node, TEXT("onmousemove"));
}

BOOL ActionSimulator::MouseUp( IHTMLElement *elm, long offsetX, long offsetY )
{
	return ActionSimulator::_Action(elm, TEXT("onmouseup"), offsetX, offsetY);
}

BOOL ActionSimulator::MouseUp( IHTMLElement *elm )
{
	return ActionSimulator::_Action(elm, TEXT("onmouseup"));
}

BOOL ActionSimulator::MouseUp( IHTMLDOMNode *node, long offsetX, long offsetY )
{
	return ActionSimulator::_Action(node, TEXT("onmouseup"), offsetX, offsetY);
}

BOOL ActionSimulator::MouseUp( IHTMLDOMNode *node )
{
	return ActionSimulator::_Action(node, TEXT("onmouseup"));
}

void ActionSimulator::_GetBoxCenterOffset( IHTMLElement *elm, long *cx, long *cy )
{
	long top, left, height, width;

	if (cx && cy)
	{
		*cx=0;
		*cy=0;
		
		if (elm)
		{
			elm->get_offsetTop(&top);
			elm->get_offsetLeft(&left);
			elm->get_offsetHeight(&height);
			elm->get_offsetWidth(&width);

			*cx=(top+height)/2;
			*cy=(left+width)/2;
		}
	}
}

BOOL ActionSimulator::_Action( IHTMLElement *elm, const BSTR actionName, long offsetX, long offsetY )
{
	IDispatch *disDoc;
	IHTMLDocument4 *doc4;
	VARIANT_BOOL brs;
	IHTMLEventObj *evt;
	IHTMLEventObj2 *evt2;
	VARIANT empty;
	VARIANT refevt;
	IHTMLElement3 *elm3;
	
	brs=VARIANT_FALSE;
	if (elm)
	{
		elm->get_document(&disDoc);

		//Get document4
		doc4=NULL;;
		if (disDoc)
		{
			disDoc->QueryInterface(IID_IHTMLDocument4, (void**)&doc4);
			disDoc->Release();
		}

		//Create Event object
		evt=NULL;
		if (doc4)
		{
			VariantInit(&empty);
			doc4->createEventObject(&empty, &evt);
			doc4->Release();
		}

		//Simulator event
		if (evt)
		{
			//Set event input
			evt->QueryInterface(IID_IHTMLEventObj2, (void**)&evt2);
			if (evt2)
			{
				evt2->put_offsetX(offsetX);
				evt2->put_offsetY(offsetY);
				evt2->put_button(1);
				evt2->Release();
			}

			//Simulator
			elm->QueryInterface(IID_IHTMLElement3, (void**)&elm3);
			if (elm3)
			{
				refevt.vt=VT_DISPATCH;
				refevt.pdispVal=evt;

				elm3->fireEvent(actionName, &refevt, &brs);

				elm3->Release();
			}

			evt->Release();
		}
	}

	return brs;
}

BOOL ActionSimulator::_Action( IHTMLDOMNode *node, const BSTR actionName, long offsetX, long offsetY )
{
	IHTMLElement *elm;
	BOOL brs;

	brs=FALSE;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			brs=ActionSimulator::_Action(elm, actionName, offsetX, offsetY);
			elm->Release();
		}
	}
	return brs;
}

BOOL ActionSimulator::_Action( IHTMLElement *elm, const BSTR actionName )
{
	BOOL brs;
	long ox, oy;

	brs=FALSE;
	if (elm)
	{
		ActionSimulator::_GetBoxCenterOffset(elm, &ox, &oy);
		brs=ActionSimulator::_Action(elm, actionName, ox, oy);
	}

	return brs;
}

BOOL ActionSimulator::_Action( IHTMLDOMNode *node, const BSTR actionName )
{
	BOOL brs;
	IHTMLElement *elm;

	brs=FALSE;
	if (node)
	{
		node->QueryInterface(IID_IHTMLElement, (void**)&elm);
		if (elm)
		{
			brs=ActionSimulator::_Action(elm, actionName);
			elm->Release();
		}
	}

	return brs;
}

BOOL ActionSimulator::MouseFromTo( IHTMLElement *elmSrc, long offsetSrcX, long offsetSrcY, IHTMLElement *elmDes, long offsetDesX, long offsetDesY )
{
	BOOL brs;

	brs=ActionSimulator::MouseDown(elmSrc, offsetSrcX, offsetSrcY);
	brs&=ActionSimulator::MouseMove(elmDes, offsetDesX, offsetDesY);
	brs&=ActionSimulator::MouseUp(elmDes, offsetDesX, offsetDesY);

	return brs;
}

BOOL ActionSimulator::MouseFromTo( IHTMLElement *elmSrc, IHTMLElement *elmDes )
{
	BOOL brs;

	brs=ActionSimulator::MouseDown(elmSrc);
	brs&=ActionSimulator::MouseMove(elmDes);
	brs&=ActionSimulator::MouseUp(elmDes);

	return brs;
}

BOOL ActionSimulator::MouseFromTo( IHTMLDOMNode *nodeSrc, long offsetSrcX, long offsetSrcY, IHTMLDOMNode *nodeDes, long offsetDesX, long offsetDesY )
{
	BOOL brs;

	brs=ActionSimulator::MouseDown(nodeSrc, offsetSrcX, offsetSrcY);
	brs&=ActionSimulator::MouseMove(nodeDes, offsetDesX, offsetDesY);
	brs&=ActionSimulator::MouseUp(nodeDes, offsetDesX, offsetDesY);

	return brs;
}

BOOL ActionSimulator::MouseFromTo( IHTMLDOMNode *nodeSrc, IHTMLDOMNode *nodeDes )
{
	BOOL brs;

	brs=ActionSimulator::MouseDown(nodeSrc);
	brs&=ActionSimulator::MouseMove(nodeDes);
	brs&=ActionSimulator::MouseUp(nodeDes);

	return brs;
}

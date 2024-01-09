#pragma once

#include <Windows.h>
#include <MsHTML.h>

class ActionSimulator
{
public:
	static BOOL Click(IHTMLElement *elm, long offsetX, long offsetY);
	static BOOL Click(IHTMLElement *elm);
	static BOOL Click(IHTMLDOMNode *node, long offsetX, long offsetY);
	static BOOL Click(IHTMLDOMNode *node);

	static BOOL MouseDown(IHTMLElement *elm, long offsetX, long offsetY);
	static BOOL MouseDown(IHTMLElement *elm);
	static BOOL MouseDown(IHTMLDOMNode *node, long offsetX, long offsetY);
	static BOOL MouseDown(IHTMLDOMNode *node);

	static BOOL MouseMove(IHTMLElement *elm, long offsetX, long offsetY);
	static BOOL MouseMove(IHTMLElement *elm);
	static BOOL MouseMove(IHTMLDOMNode *node, long offsetX, long offsetY);
	static BOOL MouseMove(IHTMLDOMNode *node);

	static BOOL MouseUp(IHTMLElement *elm, long offsetX, long offsetY);
	static BOOL MouseUp(IHTMLElement *elm);
	static BOOL MouseUp(IHTMLDOMNode *node, long offsetX, long offsetY);
	static BOOL MouseUp(IHTMLDOMNode *node);

	static BOOL MouseFromTo(IHTMLElement *elmSrc, long offsetSrcX, long offseSrctY, IHTMLElement *elmDes, long offsetDesX, long offsetDesY);
	static BOOL MouseFromTo(IHTMLElement *elmSrc, IHTMLElement *elmDes);
	static BOOL MouseFromTo(IHTMLDOMNode *nodeSrc, long offsetSrcX, long offsetSrcY, IHTMLDOMNode *nodeDes, long offsetDesX, long offsetDesY);
	static BOOL MouseFromTo(IHTMLDOMNode *nodeSrc, IHTMLDOMNode *nodeDes);
private:
	static void _GetBoxCenterOffset(IHTMLElement *elm, long *cx, long *cy);
	static BOOL _Action(IHTMLElement *elm, const BSTR actionName, long offsetX, long offsetY);
	static BOOL _Action(IHTMLElement *elm, const BSTR actionName);
	static BOOL _Action(IHTMLDOMNode *node, const BSTR actionName, long offsetX, long offsetY);
	static BOOL _Action(IHTMLDOMNode *node, const BSTR actionName);
};
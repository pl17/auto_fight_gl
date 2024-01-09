#ifndef _PSIMULATOR_H
#define _PSIMULATOR_H

#include <MsHTML.h>
#include "GameObj_XPathConst.h"

int psSimulatorClick(IHTMLDocument3 *doc3, const GAMEOBJ_XPATH *xpath);
int psSimulatorClick(IHTMLDOMNode *node);

#endif
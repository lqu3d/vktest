#pragma once

#include "XObjectMgr.h"

#define X_OBJ_RELEASE(x){ delete x; x = NULL;}
#define X_ARR_RELEASE(x){ delete[] x; x = NULL;}

class XObject
{
public:
	virtual void OnStart();

	virtual void OnUpdate();

	virtual void OnDestroy();

};

extern XObjectMgr objMgr;
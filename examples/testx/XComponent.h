#pragma once
#include "XGameObject.h"
class XComponent :
	public XGameObject
{
public:
	XComponent(XGameObject* gameObject);
public:
	XGameObject* gameObject = NULL;
};


#pragma once
#include "XComponent.h"
class XMaterial :
	public XComponent
{
	friend class XObjectMgr;
	XMaterial(XGameObject* gameObject);

public:

	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnDestroy() override;
};


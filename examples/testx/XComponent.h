#pragma once
#include "XObject.h"

class XComponent :
	public XObject
{
	friend class XGameObject;
public:
	XComponent(XGameObject* gameObject);
public:
	XGameObject* gameObject;

protected:
	// ͨ�� XObject �̳�
	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnDestroy() override;

};


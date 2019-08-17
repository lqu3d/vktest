#pragma once
#include "XObject.h"
#include "XTransform.h"

class XComponent :
	public XObject
{
	friend class XGameObject;
public:
	XComponent(XGameObject* gameObject);
public:
	XGameObject* const gameObject; //指针不可更改，仅在构造函数的列表中确定其值
	XTransform* const transform;

protected:
	// 通过 XObject 继承
	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnDestroy() override;

};


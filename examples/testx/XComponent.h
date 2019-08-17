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
	XGameObject* const gameObject; //ָ�벻�ɸ��ģ����ڹ��캯�����б���ȷ����ֵ
	XTransform* const transform;

protected:
	// ͨ�� XObject �̳�
	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnDestroy() override;

};


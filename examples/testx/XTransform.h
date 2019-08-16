#pragma once
#include<vector>
#include "XComponent.h"

class XTransform : public XComponent
{
	friend class XGameObject;
private:
	//ֻ����GameObject���죬����̳У��������ⲿ˽������
	XTransform(XGameObject* gameObject);

public:
	XTransform* parent;
	std::vector<XTransform*> childs;

};


#pragma once
#include<vector>
#include "XComponent.h"

class XTransform : public XComponent
{
	friend class XGameObject;
private:
	//只能由GameObject构造，允许继承，不允许外部私自生成
	XTransform(XGameObject* gameObject);

public:
	XTransform* parent;
	std::vector<XTransform*> childs;

};


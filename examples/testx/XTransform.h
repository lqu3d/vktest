#pragma once
#include<vector>
#include <glm/glm.hpp>

using glm::vec3;
using std::vector;

class XTransform
{
	friend class XGameObject;
	friend class XComponent;
private:
	vec3 position;
	vec3 rotation;
	vec3 scale;

	vec3 loacalPosition;
	vec3 localRotation;
	vec3 localScale;

	XTransform* parent;
	std::vector<XTransform*> childrens;

private:
	//只能由GameObject和XComponent构造，不允许继承，不允许外部私自生成
	XTransform(XGameObject* gameObject);

	void Refresh();
public:

	XGameObject* const gameObject;
	/***
	* 使用函数式设置的目的，数据变化得到监视，数据变化时才重新计算整个父子层级
	*/
	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3& pos);
	void SetX(float x); void SetY(float y); void SetZ(float z);
	const glm::vec3* GetPosition();

	void SetParent(XTransform* parent);
	XTransform* GetParent();

};


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
	//ֻ����GameObject��XComponent���죬������̳У��������ⲿ˽������
	XTransform(XGameObject* gameObject);

	void Refresh();
public:

	XGameObject* const gameObject;
	/***
	* ʹ�ú���ʽ���õ�Ŀ�ģ����ݱ仯�õ����ӣ����ݱ仯ʱ�����¼����������Ӳ㼶
	*/
	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3& pos);
	void SetX(float x); void SetY(float y); void SetZ(float z);
	const glm::vec3* GetPosition();

	void SetParent(XTransform* parent);
	XTransform* GetParent();

};


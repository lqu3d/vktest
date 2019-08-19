
#pragma once
#include<vector>
#include <glm/glm.hpp>

using glm::vec3;
using glm::mat4;
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

	vec3 up;
	vec3 right;
	vec3 forward;

	mat4 tmView;
	mat4 tmProj;
	XTransform* parent;
	std::vector<XTransform*> childrens;

	bool posChanged = false;
	bool rotChanged = false;
	bool scaleChanged = false;
	bool parentChanged = false;

private:
	//ֻ����GameObject��XComponent���죬������̳У��������ⲿ˽������
	XTransform(XGameObject* gameObject);

	void RefreshHierachy();
public:

	XGameObject* const gameObject;
	/***
	* ʹ�ú���ʽ���õ�Ŀ�ģ����ݱ仯�õ����ӣ����ݱ仯ʱ�����¼����������Ӳ㼶
	*/
	void SetPos(float x, float y, float z);
	void SetPos(const vec3& pos);
	void SetX(float x); 
	void SetY(float y); 
	void SetZ(float z);
	const vec3* GetPosition();

	void SetScale(float x, float y, float z);
	void SetScale(const vec3& scale);
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);
	const vec3* GetScale();

	void SetRot(float x, float y, float z);
	void SetRot(const vec3& rot);
	void SetRotX(float x);
	void SetRotY(float y);
	void SetRotZ(float z);
	const vec3* GetRot();

	void SetParent(XTransform* parent);
	XTransform* GetParent();

	void LookAt(const vec3 & eye, const vec3 & center, const vec3& up);

	const glm::mat4* GetMatrix();

};


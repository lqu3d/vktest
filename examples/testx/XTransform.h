
#pragma once
#include<vector>
#include <glm/glm.hpp>

using glm::vec3;
using glm::mat4;
using std::vector;

enum eXSpace
{
	xsBegin,

	xsWorld,
	xsLocal,
	
	xsEnd
};
class XTransform
{
	friend class XGameObject;
	friend class XComponent;
private:
	vec3 position;
	vec3 rotation;
	vec3 scale;

	vec3 localPosition;
	vec3 localRot;
	vec3 localScale;

	vec3 up;
	vec3 right;
	vec3 forward;

	mat4 tmView;
	mat4 tmProj;
	XTransform* parent;
	std::vector<XTransform*> childrens;

private:
	//ֻ����GameObject��XComponent���죬������̳У��������ⲿ˽������
	XTransform(XGameObject* gameObject);

public:

	XGameObject* const gameObject;
	/***
	* ʹ�ú���ʽ���õ�Ŀ�ģ����ݱ仯�õ����ӣ����ݱ仯ʱ�����¼����������Ӳ㼶
	*/
	void SetPos(float x, float y, float z, eXSpace s = xsWorld);
	void SetPos(const vec3& pos, eXSpace s = xsWorld);
	void SetX(float x, eXSpace s = xsWorld);
	void SetY(float y, eXSpace s = xsWorld);
	void SetZ(float z, eXSpace s = xsWorld);
	const vec3* GetPosition(eXSpace s = xsWorld);

	void SetScale(float x, float y, float z, eXSpace s = xsWorld);
	void SetScale(const vec3& scale, eXSpace s = xsWorld);
	void SetScaleX(float x, eXSpace s = xsWorld);
	void SetScaleY(float y, eXSpace s = xsWorld);
	void SetScaleZ(float z, eXSpace s = xsWorld);
	const vec3* GetScale(eXSpace s = xsWorld);

	void SetRot(float x, float y, float z, eXSpace s = xsWorld);
	void SetRot(const vec3& rot, eXSpace s = xsWorld);
	void SetRotX(float x, eXSpace s = xsWorld);
	void SetRotY(float y, eXSpace s = xsWorld);
	void SetRotZ(float z, eXSpace s = xsWorld);
	const vec3* GetRot(eXSpace s = xsWorld);

	void SetParent(XTransform* parent);
	XTransform* GetParent();

	void LookAt(const vec3 & eye, const vec3 & center, const vec3& up);

	const mat4* GetMatrix();
	const mat4* GetViewMatrix();

};


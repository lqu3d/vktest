
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
	vec3 lastScale; //上一次缩放，用于还原综合矩阵中的缩放值

	vec3 localPosition;
	vec3 localRot;
	vec3 localScale;

	vec3 up;
	vec3 right;
	vec3 forward;

	mat4 tmView;
	mat4 tmCombined; //平移旋转缩放综合矩阵: 

	XTransform* parent;
	std::vector<XTransform*> childrens;

private:
	//只能由GameObject和XComponent构造，不允许继承，不允许外部私自生成
	XTransform(XGameObject* gameObject);

public:

	XGameObject* const gameObject;
	/***
	* 使用函数式设置的目的，数据变化得到监视，数据变化时才重新计算整个父子层级
	*/
	void SetPos(float x, float y, float z, eXSpace s = xsWorld);
	void SetPos(const vec3& pos, eXSpace s = xsWorld);
	void SetX(float x, eXSpace s = xsWorld);
	void SetY(float y, eXSpace s = xsWorld);
	void SetZ(float z, eXSpace s = xsWorld);
	void SetPosChanel(int i, float v, eXSpace s = xsWorld); //设置x,y,z中的某个分量，分别对应0，1，2三个通道
	const vec3* GetPosition(eXSpace s = xsWorld);

	void SetScale(float x, float y, float z, eXSpace s = xsWorld);
	void SetScale(const vec3& scale, eXSpace s = xsWorld);
	void SetScaleX(float x, eXSpace s = xsWorld);
	void SetScaleY(float y, eXSpace s = xsWorld);
	void SetScaleZ(float z, eXSpace s = xsWorld);
	void SetScaleChanel(int i, float v, eXSpace s = xsWorld); //设置x,y,z中的某个分量，分别对应0，1，2三个通道
	const vec3* GetScale(eXSpace s = xsWorld);

	void SetRot(float x, float y, float z, eXSpace s = xsWorld);
	void SetRot(const vec3& rot, eXSpace s = xsWorld);
	void SetRotX(float x, eXSpace s = xsWorld);
	void SetRotY(float y, eXSpace s = xsWorld);
	void SetRotZ(float z, eXSpace s = xsWorld);
	void SetRotChanel(int i, float v, eXSpace s = xsWorld); //设置x,y,z中的某个分量，分别对应0，1，2三个通道
	const vec3* GetRot(eXSpace s = xsWorld);

	//增量变换
	void Translate(float x, float y, float z, eXSpace s = xsWorld);
	void Rotate(float x, float y, float z, eXSpace s = xsWorld);


	void SetParent(XTransform* parent);
	XTransform* GetParent();

	void LookAt(const vec3 & eye, const vec3 & center, const vec3& up);

	const mat4* GetMatrix();
	const mat4* GetViewMatrix();

};


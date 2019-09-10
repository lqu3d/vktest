#include "XTransform.h"
#include "XGameObject.h"

XTransform::XTransform(XGameObject* gameObject)
	: gameObject(gameObject)
	
{
	SetPos(0, 0, 0);
	SetRot(0, 0, 0);
	SetScale(1, 1, 1);

}

void XTransform::SetParent(XTransform* parent)
{
	this->parent = parent;
}

XTransform* XTransform::GetParent()
{
	return parent;
}

void XTransform::LookAt(const vec3 & eye, const vec3 & center, const vec3& up)
{
	//tmView = glm::lookAt(eye, center, up);
}

const glm::mat4* XTransform::GetMatrix()
{
	return &tmView;
}

const mat4* XTransform::GetViewMatrix()
{
	return nullptr;
}

void XTransform::SetPosChanel(int i, float v, eXSpace s)
{
	if (s == xsWorld) {
		position[i] = v;
		if (parent) {
			localPosition[i] = v - parent->position[i];
		}
	}
	else {
		localPosition[i] = v;
		position[i] = parent->position[i] + v;
	}

	//更新综合矩阵
	tmCombined[3][i] = position[i];
}

void XTransform::SetPos(float x, float y, float z, eXSpace s)
{
	SetPosChanel(0, x, s);
	SetPosChanel(1, y, s);
	SetPosChanel(2, z, s);
}

void XTransform::SetPos(const vec3& pos, eXSpace s)
{
	SetPosChanel(0, pos.x, s);
	SetPosChanel(1, pos.y, s);
	SetPosChanel(2, pos.z, s);
}

void XTransform::SetX(float x, eXSpace s)
{
	SetPosChanel(0, x, s);
}

void XTransform::SetY(float y, eXSpace s)
{
	SetPosChanel(1, y, s);
}

void XTransform::SetZ(float z, eXSpace s)
{
	SetPosChanel(2, z, s);
}

const vec3* XTransform::GetPosition(eXSpace s)
{
	if (s == xsWorld)
		return &position;
	return &localPosition;
}

void XTransform::SetScaleChanel(int i, float v, eXSpace s)
{
	if (s == xsWorld) {
		scale[i] = v;
		if (parent) {
			localScale[i] = v / parent->scale[i]; //todo: 除0检测
		}
	}
	else {
		localScale[i] = v;
		if (parent) {
			scale[i] = parent->scale[i] * v;
		}
	}
	lastScale[i] = scale[i];
	
	//更新综合矩阵
	tmCombined[i][i] *= v / lastScale[i];
}

void XTransform::SetScale(float x, float y, float z, eXSpace s)
{
	SetScaleChanel(0, x, s);
	SetScaleChanel(1, y, s);
	SetScaleChanel(2, z, s);
}

void XTransform::SetScale(const vec3& scale, eXSpace s)
{
	SetScale(scale.x, scale.y, scale.z, s);
}

void XTransform::SetScaleX(float x, eXSpace s)
{
	SetScaleChanel(0, x, s);
}

void XTransform::SetScaleY(float y, eXSpace s)
{
	SetScaleChanel(1, y, s);
}

void XTransform::SetScaleZ(float z, eXSpace s)
{
	SetScaleChanel(2, z, s);
}


const vec3* XTransform::GetScale(eXSpace s)
{
	if(s == xsWorld)
		return &scale;
	return &localScale;
}

void XTransform::SetRotChanel(int i, float v, eXSpace s)
{
	if (s == xsWorld) {
		rotation[i] = v;

		//todo: local rot

	}
	else {
		localPosition[i] = v;
		//todo: rotation

	}

	//更新综合矩阵

}

void XTransform::SetRot(float x, float y, float z, eXSpace s)
{
	SetRotChanel(0, x, s);
	SetRotChanel(1, y, s);
	SetRotChanel(2, z, s);
}

void XTransform::SetRot(const vec3& rot, eXSpace s)
{
	SetRotChanel(0, rot.x, s);
	SetRotChanel(1, rot.y, s);
	SetRotChanel(2, rot.z, s);
}

void XTransform::SetRotX(float x, eXSpace s)
{
	SetRotChanel(0, x, s);
}

void XTransform::SetRotY(float y, eXSpace s)
{
	SetRotChanel(1, y, s);
}

void XTransform::SetRotZ(float z, eXSpace s)
{
	SetRotChanel(2, z, s);
}


const vec3* XTransform::GetRot(eXSpace s)
{
	if(s == xsWorld)
		return &rotation;
	return &localRot;
}

void XTransform::Translate(float x, float y, float z, eXSpace s)
{
	if (s == xsWorld) {
		position.x += x;
		position.y += y;
		position.z += z;
		if (parent) {
			localPosition = position - parent->position;
		}
	}
	else {
		localPosition.x += x;
		localPosition.y += y;
		localPosition.z += z;
		if (parent) {
			position = parent->position + localPosition;
		}
	}

	//=================================================================
	//【可以证明】平移只改变矩阵的最后一行 ，不管这个矩阵有无旋转，缩放 
	//=================================================================
	tmCombined[3].x += position.x;
	tmCombined[3].y += position.y;
	tmCombined[3].z += position.z;
}

void XTransform::Rotate(float x, float y, float z, eXSpace s)
{

}

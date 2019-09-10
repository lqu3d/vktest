#include "XTransform.h"
#include "XGameObject.h"
#include "XUtils.h"

vec3 XTransform::Up = vec3(0, 1, 0);
vec3 XTransform::Right = vec3(1, 0, 0);
vec3 XTransform::Forward = vec3(0, 0, 1);

XTransform::XTransform(XGameObject* gameObject)
	: gameObject(gameObject)
	
{
	tmCombined = mat4(1.0f);

	up = vec3(0, 1, 0);
	right = vec3(1, 0, 0);
	forward = vec3(0, 0, 1);

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
		if (parent) {
			position[i] = parent->position[i] + v;
		}
	}

	//更新综合矩阵
	tmCombined[3][i] = position[i];
	isTmCombinedChged = true;
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
	float oldScale = 1.0f;
	if (s == xsWorld) {
		oldScale = scale[i];
		scale[i] = v;
		if (parent) {
			localScale[i] = v / parent->scale[i]; //todo: 除0检测
		}
	}
	else {
		oldScale = localScale[i];
		localScale[i] = v;
		if (parent) {
			scale[i] = parent->scale[i] * v;
		}
	}
	
	//更新综合矩阵
	tmCombined[i][i] *= v / oldScale;
	isTmCombinedChged = true;

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
	//cos sin
	//-sin cos
	auto rad = glm::radians(v);

	auto cn = cosf(rad);
	auto sn = sinf(rad);

	auto& zoom = s == xsWorld ? scale : localScale;
	auto& tm = s == xsWorld ? tmCombined : __tmCombinedLocal;
	
	if (i == 2) {//z-x,y
		tm[0][0] = cn * zoom.x;		tm[0][1] = sn;
		tm[1][0] = -sn;				tm[1][1] = cn * zoom.y;
	}
	else if (i == 0) {//x-y,z
		tm[1][1] = cn * zoom.y;		tm[1][2] = sn;
		tm[2][1] = -sn;				tm[2][2] = cn * zoom.z;
	}
	else if (i == 1) {//y-x,z
		tm[0][0] = cn * zoom.x;		tm[0][2] = sn;
		tm[2][0] = -sn;				tm[2][2] = cn * zoom.z;
	}

	if (s == xsLocal) {
		tmCombined = tmCombined * __tmCombinedLocal;
	}
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
	
}

void XTransform::SetRotY(float y, eXSpace s)
{
	
}

void XTransform::SetRotZ(float z, eXSpace s)
{
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

	isTmCombinedChged = true;

}

void XTransform::Rotate(float x, float y, float z, eXSpace s)
{
	vec3 vx, vy, vz;
	if (s == xsWorld) { vx = Right; vy = Up; vz = Forward; }
	else { vx = right; vy = up; vz = forward; }

	if (!XUtils::XIsZero(x)) {
		tmCombined = glm::rotate(tmCombined, glm::radians(x), vx);
		isTmCombinedChged = true;
	}
	if (!XUtils::XIsZero(y)) {
		tmCombined = glm::rotate(tmCombined, glm::radians(y), vy);
		isTmCombinedChged = true;
	}
	if (!XUtils::XIsZero(z)) {
		tmCombined = glm::rotate(tmCombined, glm::radians(z), vz);
		isTmCombinedChged = true;
	}
}

mat4* XTransform::GetTmCombinedLocal()
{
	if (!parent) {
		return &tmCombined;
	}

	if (isTmCombinedChged) {
		// parent.tmCombined * tmCombinedLocal = tmCombined
		// tmCombinedLocal = reverse(parent.tmcombined) * tmCombined 

		__tmCombinedLocal = glm::inverse(parent->tmCombined) * tmCombined;
		isTmCombinedChged = false;
	}
	return &__tmCombinedLocal;
}
#include "XTransform.h"
#include <glm/ext.hpp>

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
	tmView = glm::lookAt(eye, center, up);
}

const glm::mat4* XTransform::GetMatrix()
{
	return &tmView;
}

const mat4* XTransform::GetViewMatrix()
{
	return nullptr;
}

void XTransform::SetPos(float x, float y, float z, eXSpace s)
{
	if (s == xsWorld) {
		position.x = x;
		position.y = y;
		position.z = z;
	}
	else {
		localPosition.x = x;
		localPosition.y = y;
		localPosition.z = z;
	}
}

void XTransform::SetPos(const vec3& pos, eXSpace s)
{
	if (s == xsWorld) {
		position = pos;
	}
	else {
		localPosition = position;
	}
}

void XTransform::SetX(float x, eXSpace s)
{
	if (s == xsWorld) {
		position.x = x;
	}
	else {
		localPosition.x = x;
	}
}

void XTransform::SetY(float y, eXSpace s)
{
	if (s == xsWorld) {
		position.y = y;
	}
	else {
		localPosition.y = y;
	}
}

void XTransform::SetZ(float z, eXSpace s)
{
	if (s == xsWorld) {
		position.z = z;
	}
	else {
		localPosition.z = z;
	}
}

const vec3* XTransform::GetPosition(eXSpace s)
{
	if (s == xsWorld)
		return &position;
	return &localPosition;
}

void XTransform::SetScale(float x, float y, float z, eXSpace s)
{
	if (s == xsWorld) {
		scale.x = x;
	}
	else {
		scale.x = x;
	}
}

void XTransform::SetScale(const vec3& scale, eXSpace s)
{
	if (s == xsWorld) {
		this->scale = scale;
	}
	else {
		localScale = scale;
	}
}

void XTransform::SetScaleX(float x, eXSpace s)
{
	if (s == xsWorld) {
		scale.x = x;
	}
	else {
		scale.x = x;
	}
}

void XTransform::SetScaleY(float y, eXSpace s)
{
	if (s == xsWorld) {
		scale.y = y;
	}
	else {
		scale.y = y;
	}
}

void XTransform::SetScaleZ(float z, eXSpace s)
{
	if (s == xsWorld) {
		scale.z = z;
	}
	else {
		scale.z = z;
	}
}

const vec3* XTransform::GetScale(eXSpace s)
{
	if(s == xsWorld)
		return &scale;
	return &localScale;
}

void XTransform::SetRot(float x, float y, float z, eXSpace s)
{
	if (s == xsWorld) {
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}
	else {
		localRot.x = x;
		localRot.y = y;
		localRot.z = z;
	}
}

void XTransform::SetRot(const vec3& rot, eXSpace s)
{
	if (s == xsWorld) {
		rotation = rot;
	}
	else {
		localRot = rot;
	}
}

void XTransform::SetRotX(float x, eXSpace s)
{
	if (s == xsWorld) {
		rotation.x = x;
	}
	else {
		localRot.x = x;
	}
}

void XTransform::SetRotY(float y, eXSpace s)
{
	if (s == xsWorld) {
		rotation.y = y;
	}
	else {
		localRot.y = y;
	}
}

void XTransform::SetRotZ(float z, eXSpace s)
{
	if (s == xsWorld) {
		rotation.z = z;
	}
	else {
		localRot.z = z;
	}
}

const vec3* XTransform::GetRot(eXSpace s)
{
	if(s == xsWorld)
		return &rotation;
	return &localRot;
}

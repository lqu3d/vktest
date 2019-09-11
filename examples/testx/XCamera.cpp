#include <glm/ext.hpp>

#include "XCamera.h"
#include "XWindow.h"

XCamera::XCamera(XGameObject* gameObject):XComponent(gameObject)
{
	width = xWnd.width;
	height = xWnd.height;
	__tmProj = mat4(1);
}

void XCamera::SetFov(float fov)
{
	this->fov = fov;
	isProjChged = true;
}

float XCamera::GetFov()
{
	return fov;
}

void XCamera::SetNearPlane(float fNear)
{
	this->fNear = fNear;
	isProjChged = true;
}

float XCamera::GetNearPlane()
{
	return fNear;
}

void XCamera::SetFarPlane(float fFar)
{
	this->fFar = fFar;
	isProjChged = true;
}

float XCamera::GetFarPlane()
{
	return fFar;
}

const glm::mat4* XCamera::GetViewMatrix()
{
	return transform->GetMatrix();
}

const glm::mat4* XCamera::GetProjectionMatrix()
{
	if (isProjChged) {//量子观察设计法，只有用到数据时才去计算它
		__tmProj = glm::perspective(fov, width * 1.0f / height, fNear, fFar);
		isProjChged = false;
	}

	return &__tmProj;
}

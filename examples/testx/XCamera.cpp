#include "XCamera.h"
#include <glm/ext.hpp>

XCamera::XCamera(XGameObject* gameObject):XComponent(gameObject)
{
}

void XCamera::SetFov(float fov)
{
	this->fov = fov;
	tmProj = glm::perspective(fov, width*1.0f/height, fNear, fFar);
}

float XCamera::GetFov()
{
	return fov;
}

void XCamera::SetNearPlane(float near)
{
	this->fNear = near;
	tmProj = glm::perspective(fov, width * 1.0f / height, fNear, fFar);

}

float XCamera::GetNearPlane()
{
	return fNear;
}

void XCamera::SetFarPlane(float far)
{
	this->fFar = far;
	tmProj = glm::perspective(fov, width * 1.0f / height, fNear, fFar);
}

float XCamera::GetFarPlane()
{
	return 0.0f;
}

const glm::mat4* XCamera::GetViewMatrix()
{
	return transform->GetMatrix();
}

const glm::mat4* XCamera::GetProjectionMatrix()
{
	return &tmProj;
}

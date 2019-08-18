#include <glm/ext.hpp>

#include "XCamera.h"
#include "XVulkan.h"

XCamera::XCamera(XGameObject* gameObject):XComponent(gameObject)
{
	width = xvk.xWnd.width;
	height = xvk.xWnd.height;
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

void XCamera::SetNearPlane(float fNear)
{
	this->fNear = fNear;
	tmProj = glm::perspective(fov, width * 1.0f / height, fNear, fFar);

}

float XCamera::GetNearPlane()
{
	return fNear;
}

void XCamera::SetFarPlane(float fFar)
{
	this->fFar = fFar;
	tmProj = glm::perspective(fov, width * 1.0f / height, fNear, fFar);
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
	return &tmProj;
}

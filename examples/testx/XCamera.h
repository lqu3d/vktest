#pragma once
#include "XComponent.h"
class XCamera :
	public XComponent
{
private:
	glm::mat4 __tmProj; //¡¾Âã±äÁ¿¡¿
	bool isProjChged = false;

	float fNear = 1;
	float fFar = 1000;
	float fov = 45;
	float width = 100	;
	float height = 100;

public:
	XCamera(XGameObject* gameObject);

	void SetFov(float fov);
	float GetFov();

	void SetNearPlane(float near);
	float GetNearPlane();

	void SetFarPlane(float far);
	float GetFarPlane();

	const glm::mat4* GetViewMatrix();
	const glm::mat4* GetProjectionMatrix();
	
};


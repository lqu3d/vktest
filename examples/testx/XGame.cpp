#include "XGame.h"
#include "XObjectMgr.h"
#include "XUtils.h"

#include "DrawCube.h"
#include "XCamera.h"
#include <glm/ext.hpp>
#include "XTransform.h"
#include "GLMTest.h"

void XGame::Start()
{
	XGameObject* go = xobjMgr.AddObject<XGameObject>();
	XCamera* cam = go->AddComponent<XCamera>();
	//cam->gameObject.
	auto trans = cam->gameObject->transform;
	auto pos = trans->GetPosition();
	trans->SetPos(glm::vec3(0, 1, 0));
	cam->SetNearPlane(1.0f);
	cam->SetFarPlane(1000.0f);
	cam->SetFov(45);
	//GLMTest glmtest;
	//glmtest.Test();



}

void XGame::Update()
{
}

void XGame::Destroy()
{
}

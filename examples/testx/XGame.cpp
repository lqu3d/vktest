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
	XGameObject* go = objMgr.AddObject<XGameObject>();
	XCamera* cam = go->AddComponent<XCamera>();
	//cam->gameObject.
	auto trans = cam->gameObject->transform;
	auto pos = trans->GetPosition();
	trans->SetPos(glm::vec3(0, 1, 0));

	GLMTest glmtest;
	glmtest.Test();

}

void XGame::Update()
{
}

void XGame::OnDestroy()
{
}

void XGame::SetupCamera()
{
	//float fov = glm::radians(45.0f);
	//float wdh = xvk.xWnd.width * 1.0f / xvk.xWnd.height;
	//float hdw = xvk.xWnd.height * 1.0f / xvk.xWnd.width;
	//fov *= wdh;

}
#include "XGame.h"
#include "XObjectMgr.h"
#include "XUtils.h"

#include "DrawCube.h"
#include "XCamera.h"

void XGame::Start()
{
	auto go = new XGameObject();
	XCamera* cam = go->AddComponent<XCamera>();
	//cam->gameObject.

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
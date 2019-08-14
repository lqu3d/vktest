#include "XGame.h"
#include "XObjectMgr.h"
#include "XUtils.h"

#include "DrawCube.h"
#include "XComponent.h"
#include "XTransform.h"

void XGame::Start()
{
	SetupCamera();

	auto po = new XObject();
	bool has = objMgr.HasObject(po);

	auto obj = objMgr.AddObject<DrawCube>();
	has = objMgr.HasObject(obj);

	
	objMgr.DestroyObject(obj);
	has = objMgr.HasObject(obj);

	int x = 20;
	bool same = XSameType<int, char>();
	bool same2 = XSameType<int, decltype(x)>();

	XLogToFile();

	auto go = new XGameObject();
	go->AddComponent<XTransform>();

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
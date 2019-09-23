#include "XMesh.h"
#include "XVulkan.h"

void XMesh::OnStart()
{
	vertSize = sizeof(XVKVert);

	//for test
	InitData(NULL);
}

// 设计思想，组件和GO的销毁都会触发OnDestroy，因此不再需要析构函数来做清理工作
void XMesh::OnDestroy()
{

}

void XMesh::InitData(const char* fileName)
{
	vertCnt = 3;
	pData = new XVKVert[vertCnt];

	pData[0] = {
		1, 0, 0,
		0, 0, 0,
		1, 1
	};

	pData[1] = {
		0, 1, 0,
		0, 0, 0,
		0.5, 0,
	};

	pData[2] = {
		-1, 0, 0,
		0, 0, 0,
		1, 0,
	};
	
}

XVKVert* XMesh::GetVertBuff()
{
	return pData;
}

uint XMesh::GetVertCount()
{
	return vertCnt;
}

uint XMesh::GetVertSize()
{
	return vertSize;
}

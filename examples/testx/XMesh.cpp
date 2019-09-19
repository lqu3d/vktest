#include "XMesh.h"
#include "XVulkan.h"
void XMesh::InitData(const char* fileName)
{
	vertSize = sizeof(XVKVert);

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

#pragma once
#include "XComponent.h"
class XMesh :
	public XComponent
{
	UINT vertCnt;
	UINT* pData;

public:
	void InitData(const char* fileName);

	void GetVertBuff(UINT* pBuff, UINT* length);

	uint32_t GetVertCount();

	uint32_t GetVertSize();
};


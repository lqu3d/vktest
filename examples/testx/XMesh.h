#pragma once
#include "XComponent.h"

struct XVKVert;

class XMesh :
	public XComponent
{
	uint vertSize;
	uint vertCnt;
	XVKVert* pData;
public:
	virtual void OnStart() override;

	virtual void OnDestroy() override;

public:
	void InitData(const char* fileName);

	XVKVert* GetVertBuff();

	uint GetVertCount();

	uint GetVertSize();
};


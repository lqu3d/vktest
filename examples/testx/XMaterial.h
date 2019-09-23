#pragma once
#include "XComponent.h"
class XMaterial :
	public XComponent
{
	friend class XObjectMgr;
	XMaterial(XGameObject* gameObject);

	std::string vsFilename;
	std::string psFilename;

	char* pVsCode = NULL;
	uint vsCodeLength;
	char* pPsCode = NULL;
	uint psCodeLength;
private:
	void LoadShader(const char* file, char** ppCode, uint* pLen);
public:

	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnDestroy() override;

public:
	void SetShaderVs(const char* file);

	void SetShaderPs(const char* file);

	uint* GetVsShaderSpirv();

	uint GetVsShaderSpirvLength();

	uint* GetPsShaderSpirv();

	uint GetPsShaderSpirvLength();

};



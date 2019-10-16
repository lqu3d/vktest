#pragma once
#include "XComponent.h"
#include "XImage.h"

class XMaterial :
	public XComponent
{
	friend class XGameObject;
	XMaterial(XGameObject* gameObject);

private:

	std::string vsFilename;
	std::string psFilename;

	char* pVsCode = NULL;
	uint vsCodeLength;
	char* pPsCode = NULL;
	uint psCodeLength;

	XImage* baseMap = NULL;
	XImage* normalMap = NULL;
	
	const char* imageFilePath;
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

	void SetBaseMap(const char* file);
	XImage* GetBaseMap();

	void SetNormalMap(const char* file);
	XImage* GetNormalMap();
};



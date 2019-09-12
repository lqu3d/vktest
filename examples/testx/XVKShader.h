#pragma once
#include <map>
#include <glslang/Include/ShHandle.h>
#include "XVulkan.h"

class XShaderLimits : public TBuiltInResource{
public:
	XShaderLimits();
};

struct XShaderStage {
	const char* text; //文本
	std::vector<UINT> spirv;  //二进制
	glslang::TShader* tshader;
	
	XShaderStage(VkShaderStageFlagBits shaderType, const char* shaderStr);
};

class XVKShader
{
	friend class XVulkan;
private:
	XVKShader();
	void AddStage(VkShaderStageFlagBits shaderType, const char* shaderStr);

	bool Build(); //compile and link

	const std::vector<UINT>& GetSpirv(VkShaderStageFlagBits shaderType);

private:
	static XShaderLimits settings;

private:
	glslang::TProgram program;

	std::vector<UINT> spirv;
	
	std::map<VkShaderStageFlagBits, XShaderStage> stages;

	EShLanguage FindLanguage(VkShaderStageFlagBits shaderType);
};


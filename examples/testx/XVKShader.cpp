#include <SPIRV/GlslangToSpv.h>
#include "XVKShader.h"

XShaderLimits XVKShader::settings;

XVKShader::XVKShader()
{

}

void XVKShader::AddStage(VkShaderStageFlagBits shaderType, const char* shaderStr)
{
	auto iter = stages.find(shaderType);
	if (iter != stages.end()) return;

	iter->second = XShaderStage(shaderType, shaderStr);

}

bool XVKShader::Build()
{
	glslang::TShader* pShader = NULL;
	auto msg = EShMessages(EShMsgSpvRules | EShMsgVulkanRules);

	//编译
	for (auto iter = stages.begin(); iter != stages.end(); ++iter) {
		auto stage = FindLanguage(iter->first);
		glslang::TShader shader(stage);
		iter->second.tshader = &shader;

		const char* shaderStrs[1] = { iter->second.text };
		shader.setStrings(shaderStrs, 1);

		if (!shader.parse(&settings, 100, false, msg)) {
			printf("Shader编译出错，信息如下: %s, %s \n", shader.getInfoLog(), shader.getInfoDebugLog());
			continue;
		}

		program.addShader(&shader);
	}

	//链接
	if (!program.link(msg)) {
		printf("Shader链接出错，信息如下: %s, %s \n", program.getInfoLog(), program.getInfoDebugLog());
		return false;
	}

	//得到字节码
	for (auto iter = stages.begin(); iter != stages.end(); ++iter) {
		auto stage = iter->second.tshader->getStage();
		//glslang::GlslangToSpv(*program.getIntermediate(stage), iter->second.spirv);

	}

	return true;
}

const std::vector<UINT>& XVKShader::GetSpirv(VkShaderStageFlagBits shaderType)
{
	auto iter = stages.find(shaderType);
	if (iter != stages.end()) {
		return iter->second.spirv;
	}

	printf("ShaderStage不存在: %d", (int)shaderType);
	
	return std::vector<UINT>();
}

EShLanguage XVKShader::FindLanguage(VkShaderStageFlagBits shaderType)
{
	switch (shaderType) {
	case VK_SHADER_STAGE_VERTEX_BIT:return EShLangVertex;
	case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:return EShLangTessControl;
	case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:return EShLangTessEvaluation;
	case VK_SHADER_STAGE_GEOMETRY_BIT:return EShLangGeometry;
	case VK_SHADER_STAGE_FRAGMENT_BIT:return EShLangFragment;
	case VK_SHADER_STAGE_COMPUTE_BIT:return EShLangCompute;
	default:return EShLangVertex;
	}
}

XShaderLimits::XShaderLimits()
{
	maxLights = 32;
	maxClipPlanes = 6;
	maxTextureUnits = 32;
	maxTextureCoords = 32;
	maxVertexAttribs = 64;
	maxVertexUniformComponents = 4096;
	maxVaryingFloats = 64;
	maxVertexTextureImageUnits = 32;
	maxCombinedTextureImageUnits = 80;
	maxTextureImageUnits = 32;
	maxFragmentUniformComponents = 4096;
	maxDrawBuffers = 32;
	maxVertexUniformVectors = 128;
	maxVaryingVectors = 8;
	maxFragmentUniformVectors = 16;
	maxVertexOutputVectors = 16;
	maxFragmentInputVectors = 15;
	minProgramTexelOffset = -8;
	maxProgramTexelOffset = 7;
	maxClipDistances = 8;
	maxComputeWorkGroupCountX = 65535;
	maxComputeWorkGroupCountY = 65535;
	maxComputeWorkGroupCountZ = 65535;
	maxComputeWorkGroupSizeX = 1024;
	maxComputeWorkGroupSizeY = 1024;
	maxComputeWorkGroupSizeZ = 64;
	maxComputeUniformComponents = 1024;
	maxComputeTextureImageUnits = 16;
	maxComputeImageUniforms = 8;
	maxComputeAtomicCounters = 8;
	maxComputeAtomicCounterBuffers = 1;
	maxVaryingComponents = 60;
	maxVertexOutputComponents = 64;
	maxGeometryInputComponents = 64;
	maxGeometryOutputComponents = 128;
	maxFragmentInputComponents = 128;
	maxImageUnits = 8;
	maxCombinedImageUnitsAndFragmentOutputs = 8;
	maxCombinedShaderOutputResources = 8;
	maxImageSamples = 0;
	maxVertexImageUniforms = 0;
	maxTessControlImageUniforms = 0;
	maxTessEvaluationImageUniforms = 0;
	maxGeometryImageUniforms = 0;
	maxFragmentImageUniforms = 8;
	maxCombinedImageUniforms = 8;
	maxGeometryTextureImageUnits = 16;
	maxGeometryOutputVertices = 256;
	maxGeometryTotalOutputComponents = 1024;
	maxGeometryUniformComponents = 1024;
	maxGeometryVaryingComponents = 64;
	maxTessControlInputComponents = 128;
	maxTessControlOutputComponents = 128;
	maxTessControlTextureImageUnits = 16;
	maxTessControlUniformComponents = 1024;
	maxTessControlTotalOutputComponents = 4096;
	maxTessEvaluationInputComponents = 128;
	maxTessEvaluationOutputComponents = 128;
	maxTessEvaluationTextureImageUnits = 16;
	maxTessEvaluationUniformComponents = 1024;
	maxTessPatchComponents = 120;
	maxPatchVertices = 32;
	maxTessGenLevel = 64;
	maxViewports = 16;
	maxVertexAtomicCounters = 0;
	maxTessControlAtomicCounters = 0;
	maxTessEvaluationAtomicCounters = 0;
	maxGeometryAtomicCounters = 0;
	maxFragmentAtomicCounters = 8;
	maxCombinedAtomicCounters = 8;
	maxAtomicCounterBindings = 1;
	maxVertexAtomicCounterBuffers = 0;
	maxTessControlAtomicCounterBuffers = 0;
	maxTessEvaluationAtomicCounterBuffers = 0;
	maxGeometryAtomicCounterBuffers = 0;
	maxFragmentAtomicCounterBuffers = 1;
	maxCombinedAtomicCounterBuffers = 1;
	maxAtomicCounterBufferSize = 16384;
	maxTransformFeedbackBuffers = 4;
	maxTransformFeedbackInterleavedComponents = 64;
	maxCullDistances = 8;
	maxCombinedClipAndCullDistances = 8;
	maxSamples = 4;
	maxMeshOutputVerticesNV = 256;
	maxMeshOutputPrimitivesNV = 512;
	maxMeshWorkGroupSizeX_NV = 32;
	maxMeshWorkGroupSizeY_NV = 1;
	maxMeshWorkGroupSizeZ_NV = 1;
	maxTaskWorkGroupSizeX_NV = 32;
	maxTaskWorkGroupSizeY_NV = 1;
	maxTaskWorkGroupSizeZ_NV = 1;
	maxMeshViewCountNV = 4;
	limits.nonInductiveForLoops = 1;
	limits.whileLoops = 1;
	limits.doWhileLoops = 1;
	limits.generalUniformIndexing = 1;
	limits.generalAttributeMatrixVectorIndexing = 1;
	limits.generalVaryingIndexing = 1;
	limits.generalSamplerIndexing = 1;
	limits.generalVariableIndexing = 1;
	limits.generalConstantMatrixVectorIndexing = 1;
}

XShaderStage::XShaderStage(VkShaderStageFlagBits shaderType, const char* shaderStr): tshader(NULL)
{
}

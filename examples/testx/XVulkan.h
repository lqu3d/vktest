#pragma once

//必须有这个宏，通知VULKAN包含WIN32平台的东西
#define VK_USE_PLATFORM_WIN32_KHR

#include<vulkan/vulkan.h>	
#include <vector>
//#include <glm/glm.hpp>

#include "XWindow.h"

#pragma region struct
struct XVkDepth {
	VkFormat format;
	VkImage image;
	VkDeviceMemory mem;
	VkImageView imgView;
};

struct XVkBuffer {
	VkDescriptorBufferInfo info;
	VkDeviceMemory mem;
	UINT* pIdxs;
	UINT idxCnt;
};

#pragma endregion

class XVulkan
{
public:

	VkSurfaceKHR vkSurface;
	VkInstance vkInst;
	VkPhysicalDevice vkPhyDevice;
	VkDevice vkDevice;
	VkQueue vkQueue;
	VkCommandPool vkCmdPool;
	VkCommandBuffer vkCmdBuffer;

	VkSwapchainKHR vkSwapchain;
	VkFormat vkSurfaceFmt;

	VkFormat vkDepthFmt;

	XVkDepth vkDepth;

	VkClearValue clearValue;
	
	VkViewport viewport;
	VkRect2D scissor;

	VkRenderPass vkRenderPass; //未赋值
	VkPipelineLayout vkPipelineLayout;

	VkPipeline vkPipeline; 
	VkPipelineShaderStageCreateInfo vkShaderStages[2]; //只有vs, ps

	VkFramebuffer* pFrameBuffers = NULL;

	VkPhysicalDeviceMemoryProperties vkPhyDevMemProps;

	int vkQueueFamilyIdx;

	std::vector <const char*> vkInstExtens;
	std::vector<const char*> vkDevExtens;
	std::vector<VkPhysicalDevice> gpus;

private:

	void InitInstance();
	void InitWindow();
	void InitSurface();

	void SelectPhyDevices();
	void SelectQueueFamily();

	void InitDevice();
	void InitCmdBuffer();

	void InitSwapChain();
	void InitDepthBuffer();

	void InitPiplineLayout();

	void InitRenderpass();

	void InitShaderStages(std::vector<UINT> vsCode, std::vector<UINT> psCode);


#pragma region 工具函数

	bool memory_type_from_properties(uint32_t typeBits, VkFlags requirements_mask, uint32_t* typeIndex);

	void AcquireNextImage(VkSwapchainKHR swapChain, UINT* imgIdx);

#pragma endregion


public:

	void Setup();

	void CreateBuffer(UINT size, VkBufferUsageFlagBits usage, VkMemoryPropertyFlagBits memMask, OUT XVkBuffer& xvkBuffer);
	void WriteBuffer(XVkBuffer xvkBuffer, void* pdata, UINT size, UINT offset);

	void SetViewPort(int x, int y, int width, int height);

	void ClearColorDepthStencil(float r, float g, float b, float a, float depth, float s);
	void ClearColor(float r, float g, float b, float a);
	void ClearDepth(float f);
	void ClearStencil(float f);
	
	void BeginCmdBuffer();

	void BeginRenderPass();
	void Draw(XVkBuffer* pBuff);
	void EndRenderPass();

	void EndCmdBuffer();


	bool ShouldClose();
	void CheckResult(VkResult err);
	void Destroy();

private:


};

extern XVulkan xvk;


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
};

#pragma endregion

class XVulkan
{
public:
	XWindow xWnd;
	VkSurfaceKHR vkSurface;
	VkInstance vkInst;
	VkPhysicalDevice vkPhyDevice;
	VkDevice vkDevice;
	VkQueue vkQueue;
	VkCommandPool vkCmdPool;
	VkCommandBuffer vkCmdBuffer;

	VkSwapchainKHR vkSwapchain;

	XVkDepth vkDepth;

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

	bool memory_type_from_properties(uint32_t typeBits, VkFlags requirements_mask, uint32_t* typeIndex);


public:

	void Setup();

	void CreateBuffer(UINT size, VkBufferUsageFlagBits usage, VkMemoryPropertyFlagBits memMask, OUT XVkBuffer& xvkBuffer);

	void WriteBuffer(XVkBuffer xvkBuffer, void* pdata, UINT size, UINT offset);

	
	void BeginCmdBuffer();
	void EndCmdBuffer();

	bool ShouldClose();

	void CheckResult(VkResult err);

	void Destroy();

private:


};

extern XVulkan xvk;


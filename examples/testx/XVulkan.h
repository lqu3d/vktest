#pragma once

//����������֪꣬ͨVULKAN����WIN32ƽ̨�Ķ���
#define VK_USE_PLATFORM_WIN32_KHR

#include<vulkan/vulkan.h>	
#include <vector>
//#include <glm/glm.hpp>

#include "XWindow.h"

#pragma region struct
typedef unsigned int uint;

struct XVkImage {
	VkFormat format;
	VkImage image;
	VkImageView view;
	VkDeviceMemory mem;
};

struct XVkBuffer {
	VkDescriptorBufferInfo info;
	VkDeviceMemory mem;
};

struct XVKFrameBuffer {
	VkFramebuffer frameBuffer;
	VkImage image;
	VkImageView view;
};

struct XVKVert {
	float x, y, z;
	float nx, ny, nz;
	float u, v, w;
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

	XVkImage vkDepth;

	VkClearValue clearValue;
	
	VkViewport viewport;
	VkRect2D scissor;

	VkRenderPass vkRenderPass; //δ��ֵ

	VkPipeline vkPipeline; 
	VkPipelineCache vkPipelineCache;

	std::vector<XVKFrameBuffer> xvkFrameBuffers;

	VkFramebuffer* pFrameBuffers = NULL;

	VkPhysicalDeviceMemoryProperties vkPhyDevMemProps;

	VkDescriptorPool vkDescriptorPool; //���й��߹��õġ�����������ء�

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

	void InitRenderpass();

	void InitFrameBuffers();

	void InitPipelineCache(); //Ŀǰûʲô�ã��յ�����


#pragma region ���ߺ���

	bool memory_type_from_properties(uint32_t typeBits, VkFlags requirements_mask, uint32_t* typeIndex);

	void AcquireNextImage(VkSwapchainKHR swapChain, UINT* imgIdx);

	void CreateDescriptorPool(VkDescriptorPool& pool);

	void CreateDescriptorSet(VkDescriptorSetLayout setLayout, VkDescriptorSet& descSet);

	void CreatePiplineLayout(int vsDescriptorCnt, int psDescriptorCnt, VkPipelineLayout& pipLayout, VkDescriptorSet& descSet);

	void CreateShaderStages(char* vsCode, uint vsLen, char* psCode, uint psLen, VkPipelineShaderStageCreateInfo* pStagesInfo);

#pragma endregion


public:

	void Setup();

	void CreateBuffer(UINT size, VkBufferUsageFlagBits usage, VkMemoryPropertyFlagBits memMask, OUT XVkBuffer& xvkBuffer);
	void WriteBuffer(XVkBuffer xvkBuffer, void* pdata, UINT size, UINT offset);
	void FreeBuffer(XVkBuffer xvkBuffer);

	void CreateDiffusePipeline(char* vsCode, uint vsLen, char* psCode, uint psLen, VkPipeline& pipeline, VkDescriptorSet& descSet); 

	void SetViewPort(int x, int y, int width, int height);

	void ClearColorDepthStencil(float r, float g, float b, float a, float depth, float s);
	void ClearColor(float r, float g, float b, float a);
	void ClearDepth(float f);
	void ClearStencil(float f);
	
	void BeginCmdBuffer();

	void BeginRenderPass();
	void Draw(XVkBuffer* pBuff, int vertCnt);
	void EndRenderPass();

	void EndCmdBuffer();


	bool ShouldClose();
	void CheckResult(VkResult err);
	void Destroy();

private:


};

extern XVulkan xvk;


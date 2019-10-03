#pragma once

//����������֪꣬ͨVULKAN����WIN32ƽ̨�Ķ���
#define VK_USE_PLATFORM_WIN32_KHR

#include<vulkan/vulkan.h>	
#include <vector>
#include <glm/glm.hpp>

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
	VkBuffer buffer;
	VkDeviceSize offset;
	VkDeviceSize range;
	VkDeviceMemory mem;
	void* pMaped = NULL;
};

struct XVKFrameBuffer {
	VkFramebuffer frameBuffer;
	VkImage image;
	VkImageView view;
};

struct XVKVert {
	float x, y, z;
	float nx, ny, nz;
	float u, v;
};

//diffuse���߶�Ӧ��descriptorset���������ܣ�1������任��2����ͼ
struct XVKDescriptorSetBase {
	
	XVKDescriptorSetBase();
	~XVKDescriptorSetBase();

	VkDescriptorSetLayoutCreateInfo layoutInfo;
	VkDescriptorSet descSet;

	void SetMvp(glm::mat4* mvp);

	void SetImage(int binding, VkImageView imageView);

private:
	//1,uniform buffer
	XVkBuffer uniformBuffer;
	
	glm::mat4 mvp;

	//2,image
	VkDescriptorImageInfo imageInfo;

};

struct XVKPipelineBase {
	VkPipeline pipeline;
	
	XVKDescriptorSetBase xvkDescSet;
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

	bool FindMemoryType(uint32_t typeBits, VkFlags requirements_mask, uint32_t* typeIndex);

	void AcquireNextImage(VkSwapchainKHR swapChain, UINT* imgIdx);

	void CreateDescriptorPool(VkDescriptorPool& pool);

	void CreateDescriptorSet(VkDescriptorSetLayout setLayout, VkDescriptorSet& descSet);

	void CreatePiplineLayout(VkPipelineLayout& pipLayout, XVKDescriptorSetBase& xvkDescriptorSet);

	void CreateShaderStages(char* vsCode, uint vsLen, char* psCode, uint psLen, VkPipelineShaderStageCreateInfo* pStagesInfo);

	bool IsDepthFormat(VkFormat fmt);
#pragma endregion


public:

	void Setup();

	void CreateBuffer(UINT size, VkBufferUsageFlagBits usage, VkFlags memMask, OUT XVkBuffer& xvkBuffer);
	void WriteBuffer(XVkBuffer xvkBuffer, void* pdata, UINT size, UINT offset);
	void FreeBuffer(XVkBuffer xvkBuffer);

	bool CreateImage(uint w, uint h, VkFormat fmt, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags props, XVkImage& img);

	void CreateDiffusePipeline(char* vsCode, uint vsLen, char* psCode, uint psLen, XVKPipelineBase& pipelineBase);

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


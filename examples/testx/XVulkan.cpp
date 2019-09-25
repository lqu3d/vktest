#include <iostream>
#include <fstream>

#include "XVulkan.h"
#include"XWindow.h"
#include "XModel.h"


XVulkan xvk;
void XVulkan::InitInstance()
{
	//surface��չ��������ģ�û�д���չ���޷�����surface��Ҳ���޷������κεĺ�������
	vkInstExtens.clear();
	vkInstExtens.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
	vkInstExtens.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.enabledExtensionCount = vkInstExtens.size();
	info.ppEnabledExtensionNames = vkInstExtens.data(); //(const char**)vkInstExtensions.data()->c_str();
	auto ret = vkCreateInstance(&info, NULL, &vkInst);
	CheckResult(ret);

}

void XVulkan::InitWindow()
{
	xWnd.Init();
}

void XVulkan::InitSurface()
{
	/***
	*ע�������sType����ʡ������VKResult�����أ�1000011001����VK_ERROR_VALIDATION_FAILED_EXT
	*/
	VkWin32SurfaceCreateInfoKHR wscinfo = {}; //�������͸�ֵΪ0��ָ��Ϊnull
	wscinfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	wscinfo.hwnd = xWnd.hWnd;
	wscinfo.hinstance = xWnd.hInst;

	auto res = vkCreateWin32SurfaceKHR(vkInst, &wscinfo, NULL, &vkSurface);
	CheckResult(res);
}

void XVulkan::SelectPhyDevices()
{
	UINT32 cnt;
	auto res = vkEnumeratePhysicalDevices(vkInst, &cnt, NULL);
	CheckResult(res);

	gpus.resize(cnt);
	res = vkEnumeratePhysicalDevices(vkInst, &cnt, gpus.data());
	CheckResult(res);

	vkPhyDevice = gpus[0];
}

void XVulkan::SelectQueueFamily()
{
	UINT32 cnt;
	vkGetPhysicalDeviceQueueFamilyProperties(vkPhyDevice, &cnt, NULL);
	auto props = (VkQueueFamilyProperties*)malloc(cnt * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(vkPhyDevice, &cnt, props);

	for (size_t i = 0; i < cnt; i++)
	{
		if (props[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			vkQueueFamilyIdx = i;
			break;
		}
	}

	free(props);

}

void XVulkan::InitDevice()
{
	vkDevExtens.clear();
	vkDevExtens.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

	const float queuePriorties[] = { 1.0f };
	VkDeviceQueueCreateInfo dqinfo[1] = {};
	dqinfo[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	dqinfo[0].queueFamilyIndex = vkQueueFamilyIdx;
	dqinfo[0].queueCount = 1;
	dqinfo[0].pQueuePriorities = queuePriorties;

	VkDeviceCreateInfo dcinfo = {};
	dcinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	dcinfo.queueCreateInfoCount = 1;
	dcinfo.pQueueCreateInfos = dqinfo;
	dcinfo.enabledExtensionCount = vkDevExtens.size();
	dcinfo.ppEnabledExtensionNames = vkDevExtens.data();

	CheckResult(vkCreateDevice(vkPhyDevice, &dcinfo, NULL, &vkDevice));

	vkGetDeviceQueue(vkDevice, vkQueueFamilyIdx, 0, &vkQueue);
}

void XVulkan::InitCmdBuffer()
{
	VkCommandPoolCreateInfo pinfo = {};
	pinfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pinfo.queueFamilyIndex = vkQueueFamilyIdx;
	pinfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	auto ret = vkCreateCommandPool(vkDevice, &pinfo, NULL, &vkCmdPool);
	CheckResult(ret);

	VkCommandBufferAllocateInfo cbinfo = {};
	cbinfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	cbinfo.commandPool = vkCmdPool;
	cbinfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	cbinfo.commandBufferCount = 1;
	ret = vkAllocateCommandBuffers(vkDevice, &cbinfo, &vkCmdBuffer);
	CheckResult(ret);
}

void XVulkan::BeginCmdBuffer()
{
	VkCommandBufferBeginInfo begin = {};
	begin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	auto ret = vkBeginCommandBuffer(vkCmdBuffer, &begin);
	CheckResult(ret);
}

void XVulkan::EndCmdBuffer()
{
	auto ret = vkEndCommandBuffer(vkCmdBuffer);
	CheckResult(ret);
}

void XVulkan::BeginRenderPass()
{
	UINT imgIdx = 0;
	AcquireNextImage(vkSwapchain, &imgIdx);
	if (!pFrameBuffers) {
		printf("pFrameBuffers == NULL");
		return;
	}

	VkRenderPassBeginInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	info.renderPass = vkRenderPass;
	info.framebuffer = pFrameBuffers[imgIdx];
	
	info.renderArea.extent.width = viewport.width;
	info.renderArea.extent.height = viewport.height;
	info.renderArea.offset.x = 0;
	info.renderArea.offset.y = 0;

	info.clearValueCount = 1;  // == 2 ????
	info.pClearValues = &clearValue;

	vkCmdBeginRenderPass(vkCmdBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(vkCmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vkPipeline);

	//todo:
	//vkCmdBindDescriptorSets(vkCmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, sets, 0, NULL);

}

void XVulkan::Draw(XVkBuffer* pBuff, int vertCnt)
{
	vkCmdBindVertexBuffers(vkCmdBuffer, 0, 1, &(pBuff->info.buffer), &(pBuff->info.offset));
	vkCmdDraw(vkCmdBuffer, vertCnt, 1, 0, 0);
}

void XVulkan::EndRenderPass()
{
	vkCmdEndRenderPass(vkCmdBuffer);
}

void XVulkan::InitSwapChain()
{
	VkSurfaceCapabilitiesKHR scaps;
	auto ret = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkPhyDevice, vkSurface, &scaps);
	CheckResult(ret);

	UINT32 fmtCnt;
	ret = vkGetPhysicalDeviceSurfaceFormatsKHR(vkPhyDevice, vkSurface, &fmtCnt, NULL);
	CheckResult(ret);

	std::vector<VkSurfaceFormatKHR> fmts(fmtCnt);
	ret = vkGetPhysicalDeviceSurfaceFormatsKHR(vkPhyDevice, vkSurface, &fmtCnt, fmts.data());
	CheckResult(ret);

	vkSurfaceFmt = VK_FORMAT_B8G8R8A8_UNORM;
	for (size_t i = 0; i < fmts.size(); i++)
	{
		if (fmts[i].format != VK_FORMAT_UNDEFINED) {
			vkSurfaceFmt = fmts[i].format;
			break;
		}
	}


	VkExtent2D swapChainExtent;
	if (scaps.currentExtent.width == 0xffffffff) {
		swapChainExtent.width = xWnd.width;
		swapChainExtent.height = xWnd.height;
	}
	else {
		swapChainExtent = scaps.currentExtent;
	}

	auto presentMode = VK_PRESENT_MODE_FIFO_KHR;
	auto swapMinImages = scaps.minImageCount;

	VkSwapchainCreateInfoKHR scinfo = {};
	scinfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	scinfo.surface = vkSurface;
	scinfo.minImageCount = swapMinImages;
	scinfo.imageExtent = swapChainExtent;
	scinfo.imageFormat = vkSurfaceFmt;
	scinfo.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
	scinfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
	scinfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	scinfo.imageArrayLayers = 1; //????

	scinfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	scinfo.preTransform = scaps.currentTransform;
	scinfo.presentMode = presentMode;
	scinfo.oldSwapchain = VK_NULL_HANDLE;

	ret = vkCreateSwapchainKHR(vkDevice, &scinfo, NULL, &vkSwapchain);
	CheckResult(ret);

}

void XVulkan::InitDepthBuffer()
{
	//step1������image
	VkImageCreateInfo imgInfo = {};

	vkDepth.format = VK_FORMAT_D16_UNORM;

	VkFormatProperties fmtProps;
	vkGetPhysicalDeviceFormatProperties(vkPhyDevice, vkDepth.format, &fmtProps);

	if (fmtProps.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
		imgInfo.tiling = VK_IMAGE_TILING_LINEAR;
	}
	else if (fmtProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) {
		imgInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	}
	else {
		std::cout << "unsuported depth format " << vkDepth.format << std::endl;
	}

	imgInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imgInfo.imageType = VK_IMAGE_TYPE_2D;
	imgInfo.format = vkDepth.format;
	imgInfo.extent.width = xWnd.width;
	imgInfo.extent.height = xWnd.height;
	imgInfo.extent.depth = 1;
	imgInfo.arrayLayers = 1;
	imgInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imgInfo.mipLevels = 1;
	imgInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imgInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imgInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

	auto ret = vkCreateImage(vkDevice, &imgInfo, NULL, &vkDepth.image);
	CheckResult(ret);

	//step2�������ڴ�
	VkMemoryRequirements memreqs;
	vkGetImageMemoryRequirements(vkDevice, vkDepth.image, &memreqs);

	VkMemoryAllocateInfo allocinfo = {};
	allocinfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocinfo.allocationSize = memreqs.size;


	bool pass = memory_type_from_properties(memreqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &allocinfo.memoryTypeIndex);

	if (!pass) {
		std::cout << "error-memory_type_from_properties" << std::endl;
		return;
	}

	ret = vkAllocateMemory(vkDevice, &allocinfo, NULL, &vkDepth.mem);
	CheckResult(ret);

	ret = vkBindImageMemory(vkDevice, vkDepth.image, vkDepth.mem, 0);
	CheckResult(ret);


	//step3������image view��ע�⣬�������������ڴ�֮�󣬷�������ʱ����
	VkImageViewCreateInfo viewinfo = {};
	viewinfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewinfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewinfo.image = vkDepth.image;
	viewinfo.format = vkDepth.format;
	viewinfo.components.a = VK_COMPONENT_SWIZZLE_A;
	viewinfo.components.r = VK_COMPONENT_SWIZZLE_R;
	viewinfo.components.g = VK_COMPONENT_SWIZZLE_G;
	viewinfo.components.b = VK_COMPONENT_SWIZZLE_B;
	viewinfo.subresourceRange.baseMipLevel = 0;
	viewinfo.subresourceRange.levelCount = 1;
	viewinfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
	viewinfo.subresourceRange.layerCount = 1;
	viewinfo.subresourceRange.baseArrayLayer = 0;

	ret = vkCreateImageView(vkDevice, &viewinfo, NULL, &vkDepth.view);
	CheckResult(ret);

}

bool XVulkan::memory_type_from_properties(uint32_t typeBits, VkFlags requirements_mask, uint32_t* typeIndex) {
	vkGetPhysicalDeviceMemoryProperties(vkPhyDevice, &vkPhyDevMemProps);

	// Search memtypes to find first index with those properties
	for (uint32_t i = 0; i < vkPhyDevMemProps.memoryTypeCount; i++) {
		if ((typeBits & 1) == 1) {
			// Type is available, does it match user properties?
			if ((vkPhyDevMemProps.memoryTypes[i].propertyFlags & requirements_mask) == requirements_mask) {
				*typeIndex = i;
				return true;
			}
		}
		typeBits >>= 1;
	}
	// No memory types matched, return failure
	return false;
}

void XVulkan::Destroy()
{
	vkDestroyCommandPool(vkDevice, vkCmdPool, NULL);
	vkDestroySwapchainKHR(vkDevice, vkSwapchain, NULL);
	vkDestroyDevice(vkDevice, NULL);
	vkDestroySurfaceKHR(vkInst, vkSurface, NULL);
	vkDestroyInstance(vkInst, NULL);
}

void XVulkan::Setup()
{
	InitInstance();
	InitWindow();
	InitSurface();

	SelectPhyDevices();
	SelectQueueFamily();

	InitDevice();
	
	InitSwapChain();

	InitDepthBuffer();

	InitCmdBuffer();

	InitRenderpass();

	InitFrameBuffers();

	InitPipelineCache();

	//����������������ء������й��߹���
	CreateDescriptorPool(vkDescriptorPool);
}

/***
*xvkBuffer��Ϊ������дΪ����ֵ�ĺô��ǣ�
*1��xvkBuffer�����Ƕѱ�����ջ��������дΪ����ֵ��ֻ���Ƕ������룬��Ϊ���뱣֤����������
*2��xvkBuffer����Ϊջ����������Ȼ�ǲ��еģ���Ϊ�����־�
*/
void XVulkan::CreateBuffer(UINT size, VkBufferUsageFlagBits usage, VkMemoryPropertyFlagBits memMask, OUT XVkBuffer& xvkBuffer)
{
	VkBufferCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	info.usage = usage;
	info.size = size;
	info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	auto ret = vkCreateBuffer(vkDevice, &info, NULL, &xvkBuffer.info.buffer);
	CheckResult(ret);

	VkMemoryRequirements memreqs = {};
	vkGetBufferMemoryRequirements(vkDevice, xvkBuffer.info.buffer, &memreqs);

	VkMemoryAllocateInfo alloc = {};
	alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	alloc.allocationSize = memreqs.size;

	if (!memory_type_from_properties(memreqs.memoryTypeBits, memMask, &alloc.memoryTypeIndex)) {
		std::cout << "memory_type not found" << std::endl;
		exit(-1);
	}

	ret = vkAllocateMemory(vkDevice, &alloc, NULL, &xvkBuffer.mem);
	CheckResult(ret);

	ret = vkBindBufferMemory(vkDevice, xvkBuffer.info.buffer, xvkBuffer.mem, 0);
	CheckResult(ret);


}

void XVulkan::WriteBuffer(XVkBuffer xvkBuffer, void* pdata, UINT size, UINT offset) {

	UINT64* pdat;
	auto ret = vkMapMemory(vkDevice, xvkBuffer.mem, offset, size, 0, (void**)&pdat);
	CheckResult(ret);

	memcpy(pdat, pdata, size);

	vkUnmapMemory(vkDevice, xvkBuffer.mem);

}

void XVulkan::FreeBuffer(XVkBuffer xvkBuffer)
{
	vkFreeMemory(vkDevice, xvkBuffer.mem, NULL);
	
}

void XVulkan::CreateDescriptorSet(VkDescriptorSetLayout setLayout, VkDescriptorSet& descSet)
{
	VkDescriptorSetAllocateInfo descSetInfo = {};
	descSetInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	descSetInfo.descriptorPool = vkDescriptorPool;
	descSetInfo.descriptorSetCount = 1;
	descSetInfo.pSetLayouts = &setLayout;
	auto ret = vkAllocateDescriptorSets(vkDevice, &descSetInfo, &descSet);
	CheckResult(ret);
}

//����һ��ֻ��VS,PS�����׶εĹ���
void XVulkan::CreatePiplineLayout(int vsDescriptorCnt, int psDescriptorCnt, VkPipelineLayout& pipLayout, VkDescriptorSet& descSet)
{
	/*** descriptorCount ��˵��
	* �����Ϊ1����bind����һ�����飬���磺
	* layout (set=M, binding=N) uniform sampler2D variableNameArray[I];
	*/
	VkDescriptorSetLayoutBinding bindings[2] = {};
	bindings[0].binding = 0; //��Ӧshader�е�binding = 0
	bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; //uniform buffer
	bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT; //vertext shader
	bindings[0].descriptorCount = vsDescriptorCnt; //��Ϊ1���Ӧһ������

	bindings[1].binding = 1;//��Ӧshader�е�binding = 1
	bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER; //ͼƬ������
	bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT; //pixel shader
	bindings[1].descriptorCount = psDescriptorCnt; //��Ϊ1���Ӧһ������

	VkDescriptorSetLayoutCreateInfo layinfo = {};
	layinfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layinfo.bindingCount = 2;
	layinfo.pBindings = bindings;

	//1������DescriptorSet Layout
	VkDescriptorSetLayout descSetLayout;
	VkResult res = vkCreateDescriptorSetLayout(vkDevice, &layinfo, NULL, &descSetLayout);
	CheckResult(res);

	//2������DescriptorSet
	CreateDescriptorSet(descSetLayout, descSet);

	//3������PipelineLayout
	VkPipelineLayoutCreateInfo pipinfo = {};
	pipinfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipinfo.setLayoutCount = 1;
	pipinfo.pSetLayouts = &descSetLayout; //���ײ��֣���shader���� layout(set=m,binding=n)��ָ��
	res = vkCreatePipelineLayout(vkDevice, &pipinfo, NULL, &pipLayout);
	CheckResult(res);

}

//���������
void XVulkan::CreateDiffusePipeline(char* vsCode, uint vsLen, char* psCode, uint psLen, VkPipeline& pipeline, VkDescriptorSet& descSet)
{
	/*** ����binding
	* �����ʽ���������������ף���ʹ��vkCmdBindVertexBuffer(cmdbuff, firstbinding, bindingcount,pbuffers, offsets)ʱָ��ʹ����һ�׻����
	* ���� descriptor set layout�е�binding��shader��ָ��������ͬ
	*/

	//�����ʽ
	VkVertexInputBindingDescription bindDesc = {};
	bindDesc.binding = 0;
	bindDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; //��ʾÿ��stride��һ������(XVKVert)�Ŀ��
	bindDesc.stride = sizeof(XVKVert);

	VkVertexInputAttributeDescription attrDesc[3] = {
		/*{location, binding, format, offset}*/
		{0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0}, //x,y,z
		{1, 0, VK_FORMAT_R32G32B32_SFLOAT, 12}, //nx, ny, nz
		{2, 0, VK_FORMAT_R32G32_SFLOAT, 24}, //u, v
	};

	//״̬һ����������
	VkPipelineVertexInputStateCreateInfo vertexInfo = {};
	vertexInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInfo.vertexBindingDescriptionCount = 1;
	vertexInfo.pVertexBindingDescriptions = &bindDesc;
	vertexInfo.vertexAttributeDescriptionCount = 3;
	vertexInfo.pVertexAttributeDescriptions = attrDesc;

	//״̬����ͼԪװ��
	VkPipelineInputAssemblyStateCreateInfo assemblyInfo = {};
	assemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	assemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	//״̬������դ��
	VkPipelineRasterizationStateCreateInfo rasterInfo = {};
	rasterInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterInfo.polygonMode = VK_POLYGON_MODE_FILL;
	rasterInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterInfo.lineWidth = 1.0f;

	//״̬�ģ���Ȳ���
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo = {};
	depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencilInfo.depthTestEnable = VK_TRUE;
	depthStencilInfo.depthWriteEnable = VK_TRUE;
	depthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;

	//״̬�壬��̬�ӿڣ����ڳߴ�ı�ʱ�Ͳ������´������ߣ������豸��ʧ�й�ϵ�𣿣�
	VkDynamicState dynamicStates[2] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
	VkPipelineDynamicStateCreateInfo dynamicInfo = {};
	dynamicInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicInfo.dynamicStateCount = 2;
	dynamicInfo.pDynamicStates = dynamicStates;

	VkPipelineViewportStateCreateInfo viewportInfo = {};
	viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportInfo.viewportCount = 1;
	viewportInfo.scissorCount = 1;
	viewportInfo.pViewports = NULL; //��Ϊ�գ���Ϊ����ʹ�õ��Ƕ�̬�ӿ�
	viewportInfo.pScissors = NULL; //��Ϊ�գ���Ϊ����ʹ�õ��Ƕ�̬�ӿ�

	//��������
	VkPipelineLayout pipLayout;
	CreatePiplineLayout(1, 1, pipLayout, descSet);

	VkPipelineShaderStageCreateInfo stages[2];
	CreateShaderStages(vsCode,vsLen, psCode,psLen, stages);

	VkGraphicsPipelineCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	info.layout = pipLayout;
	info.pVertexInputState = &vertexInfo;
	info.pInputAssemblyState = &assemblyInfo;
	info.pRasterizationState = &rasterInfo;
	info.pDepthStencilState = &depthStencilInfo;
	info.renderPass = vkRenderPass;
	info.stageCount = 2;
	info.pStages = stages;
	info.pDynamicState = &dynamicInfo;
	info.pViewportState = &viewportInfo;
	
	auto ret = vkCreateGraphicsPipelines(vkDevice, vkPipelineCache, 1, &info, NULL, &pipeline);
	CheckResult(ret);

}

//����vs,psģ��
void XVulkan::CreateShaderStages(char* vsCode, uint vsLen, char* psCode, uint psLen, VkPipelineShaderStageCreateInfo* pStagesInfo)
{
	if (vsLen == 0 || psLen == 0) {
		printf("InitShaderʧ��");
		return;
	}

	UINT isize = sizeof(UINT);
	VkShaderModule vsModule, psModule;

	VkShaderModuleCreateInfo minfo = {};
	minfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

	minfo.codeSize = vsLen;
	minfo.pCode = (uint*)vsCode;
	auto ret = vkCreateShaderModule(vkDevice, &minfo, NULL, &vsModule);
	CheckResult(ret);

	minfo.codeSize = psLen;
	minfo.pCode = (uint*)psCode;
	ret = vkCreateShaderModule(vkDevice, &minfo, NULL, &psModule);
	CheckResult(ret);

	pStagesInfo[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	pStagesInfo[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	pStagesInfo[0].pName = "vsMain";
	pStagesInfo[0].module = vsModule;

	pStagesInfo[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	pStagesInfo[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	pStagesInfo[1].pName = "psMain";
	pStagesInfo[1].module = psModule;
}

void XVulkan::AcquireNextImage(VkSwapchainKHR swapChain, UINT* imgIdx)
{
	VkSemaphore imgAccSemaphore;
	VkSemaphoreCreateInfo info = {};
	info.flags = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	
	auto res = vkCreateSemaphore(vkDevice, &info, NULL, &imgAccSemaphore);
	CheckResult(res);

	res = vkAcquireNextImageKHR(vkDevice, vkSwapchain, UINT64_MAX, imgAccSemaphore, NULL, imgIdx);
	CheckResult(res);

}

void XVulkan::CreateDescriptorPool(VkDescriptorPool& pool)
{
	/***
	* ����������ص���⣺һ��DescriptorPool��һ��map�ṹ��key=DescriptorType, value=DescriptorCount
	* �����Ϊ���й��߹��ã�һ�ֲ��ʶ�Ӧһ�ֹ��ߣ�ͬʱ������ֹ��ߣ���˶������Ҫ�㹻��
	* uniform���ͱ������ݶ�30��
	* ����������������ݶ�8����Ҳ����ͬһshader ���֧��8����ͼ
	* todo: �������ͱ����أ���������type_count�����С
	*/

	VkDescriptorPoolSize type_count[2];
	type_count[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	type_count[0].descriptorCount = 30;
	type_count[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	type_count[1].descriptorCount = 8;

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.maxSets = 1;
	poolInfo.poolSizeCount = 2;
	poolInfo.pPoolSizes = type_count;

	auto ret = vkCreateDescriptorPool(vkDevice, &poolInfo, NULL, &pool);
	CheckResult(ret);
}

//ͨ�õ�renderpass ����ʱ�ģ��������й���
void XVulkan::InitRenderpass()
{
	bool clear = true;

	VkAttachmentDescription attachments[2];

	attachments[0].format = vkSurfaceFmt;
	attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
	attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	attachments[0].loadOp = clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_LOAD;
	attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

	attachments[1].format = vkDepth.format;
	attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
	attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	attachments[1].loadOp = clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_LOAD;
	attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

	VkAttachmentReference colorRef = {};
	colorRef.attachment = 0;
	colorRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthRef = {};
	depthRef.attachment = 1;
	depthRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subPassInfo = {};
	subPassInfo.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subPassInfo.colorAttachmentCount = 1;
	subPassInfo.pColorAttachments = &colorRef;
	subPassInfo.pDepthStencilAttachment = &depthRef;

	VkRenderPassCreateInfo rpInfo = {};
	rpInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	rpInfo.attachmentCount = 2;
	rpInfo.pAttachments = attachments;
	rpInfo.subpassCount = 1;
	rpInfo.pSubpasses = &subPassInfo;

	VkResult res = vkCreateRenderPass(vkDevice, &rpInfo, NULL, &vkRenderPass);
	CheckResult(res);
}


void XVulkan::InitFrameBuffers()
{
	UINT swapChainCnt = 0;
	auto ret = vkGetSwapchainImagesKHR(vkDevice, vkSwapchain, &swapChainCnt, NULL);
	CheckResult(ret);

	std::vector<VkImage> images(swapChainCnt);

	ret = vkGetSwapchainImagesKHR(vkDevice, vkSwapchain, &swapChainCnt, images.data());
	CheckResult(ret);

	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = vkSurfaceFmt;
	viewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
	viewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
	viewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
	viewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView attachments[2];
	VkFramebufferCreateInfo fbInfo = {};
	fbInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	fbInfo.renderPass = vkRenderPass;
	fbInfo.attachmentCount = 2;
	fbInfo.pAttachments = attachments;
	fbInfo.width = xWnd.width;
	fbInfo.height = xWnd.height;
	fbInfo.layers = 1;

	xvkFrameBuffers.resize(swapChainCnt);
	for (size_t i = 0; i < swapChainCnt; i++)
	{
		xvkFrameBuffers[i].image = images[i]; //image

		viewInfo.image = images[i];
		ret = vkCreateImageView(vkDevice, &viewInfo, NULL, &xvkFrameBuffers[i].view); //view
		CheckResult(ret);

		attachments[0] = xvkFrameBuffers[i].view;
		attachments[1] = vkDepth.view;
		ret = vkCreateFramebuffer(vkDevice, &fbInfo, NULL, &xvkFrameBuffers[i].frameBuffer); //frameBuffer
		CheckResult(ret);

	}
}

void XVulkan::InitPipelineCache()
{
	VkPipelineCacheCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
	auto ret = vkCreatePipelineCache(vkDevice, &info, NULL, &vkPipelineCache);
	CheckResult(ret);
}

void XVulkan::SetViewPort(int x, int y, int width, int height)
{
	viewport.x = x;
	viewport.y = y;
	viewport.width = width;
	viewport.height = height;

	scissor.extent.width = width;
	scissor.extent.height = height;
	scissor.offset.x = 0;
	scissor.offset.y = 0;

	vkCmdSetViewport(vkCmdBuffer, 0, 1, &viewport);
	vkCmdSetScissor(vkCmdBuffer, 0, 1, &scissor);

}

void XVulkan::ClearColorDepthStencil(float r, float g, float b, float a, float depth, float s)
{
	clearValue.color.float32[0] = r;
	clearValue.color.float32[1] = g;
	clearValue.color.float32[2] = b;
	clearValue.color.float32[3] = a;
	clearValue.depthStencil.depth = depth;
	clearValue.depthStencil.stencil = s;
}

void XVulkan::ClearColor(float r, float g, float b, float a)
{
	clearValue.color.float32[0] = r;
	clearValue.color.float32[1] = g;
	clearValue.color.float32[2] = b;
	clearValue.color.float32[3] = a;
}

void XVulkan::ClearDepth(float depth)
{
	clearValue.depthStencil.depth = depth;
}

void XVulkan::ClearStencil(float s)
{
	clearValue.depthStencil.stencil = s;
}

bool XVulkan::ShouldClose()
{
	if (xWnd.ShouldClose())
	{
		return true;
	}

	xWnd.PollEvents();
	return false;
}

void XVulkan::CheckResult(VkResult err)
{
	if (err == 0)
		return;
	printf("VKResult : %d", err);

	abort();
}

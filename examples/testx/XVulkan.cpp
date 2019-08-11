#include "XVulkan.h"
#include"XWindow.h"
#include "XModel.h"

XVulkan xvk;
void XVulkan::InitInstance()
{
	//surface扩展是最基本的，没有此扩展将无法创建surface，也就无法进行任何的后续工作
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
	*注意这里的sType不能省，否则VKResult将返回：1000011001，即VK_ERROR_VALIDATION_FAILED_EXT
	*/
	VkWin32SurfaceCreateInfoKHR wscinfo = {}; //所有类型赋值为0，指针为null
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

	VkFormat imgFormat = VK_FORMAT_B8G8R8A8_UNORM;
	for (size_t i = 0; i < fmts.size(); i++)
	{
		if (fmts[i].format != VK_FORMAT_UNDEFINED) {
			imgFormat = fmts[i].format;
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
	scinfo.imageFormat = imgFormat;
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
	//step1，创建image
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

	//step2，申请内存
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


	//step3，创建image view，注意，必须在申请了内存之后，否则运行时崩溃
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

	ret = vkCreateImageView(vkDevice, &viewinfo, NULL, &vkDepth.imgView);
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


}

/***
*xvkBuffer作为参数比写为返回值的好处是：
*1，xvkBuffer可以是堆变量或栈变量，若写为返回值则只能是堆上申请，因为必须保证它的永久性
*2，xvkBuffer或作为栈变量返回显然是不行的，因为它不持久
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

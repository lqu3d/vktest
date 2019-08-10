// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include<GLFW/glfw3.h>	
#include<vulkan/vulkan.h>	
#include<vector>	
#include<string>	
#include<assert.h>

void CheckResult(VkResult err) {
	if (err == 0)
		return;

	printf("VKResult : %d", err);
	abort();
}

struct Vulkan {
	VkInstance vkInst;
	VkSurfaceKHR vkSurface;
	std::vector <const char*> vkInstExtensions;
	
	void InitInstance() {

		vkInstExtensions.clear();
		
		//surface扩展是最基本的，没有此扩展将无法创建surface，也就无法进行任何的后续工作
		//win32平台将包含VK_KHR_WIN32_SURFACE_EXTENSION_NAME 即 "VK_KHR_win32_surface"
		uint32_t extCnt = 0;
		auto exts = glfwGetRequiredInstanceExtensions(&extCnt);
		for (size_t i = 0; i < extCnt; i++)
		{
			vkInstExtensions.push_back(exts[i]);
		}

		VkInstanceCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		info.enabledExtensionCount = vkInstExtensions.size();
		info.ppEnabledExtensionNames = vkInstExtensions.data();
		auto ret = vkCreateInstance(&info, NULL, &vkInst);
		CheckResult(ret);

	}

	void Destroy() {
		vkDestroySurfaceKHR(vkInst, vkSurface, NULL);
		vkDestroyInstance(vkInst, NULL);
	}

};


Vulkan xvk;

int main()
{
	if (!glfwInit())
		return 1;

	xvk.InitInstance();

	auto window = glfwCreateWindow(1280, 720, "test", NULL, NULL);

	auto res = glfwCreateWindowSurface(xvk.vkInst, window, NULL, &xvk.vkSurface);
	CheckResult(res);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

	}
	
	xvk.Destroy();
	glfwDestroyWindow(window);
}

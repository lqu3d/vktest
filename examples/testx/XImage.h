#pragma once
#include "XVulkan.h"

class XImage
{

	friend class XVulkan;

	XVkImage xvkImage;
	float width, height;
public:

	bool Load(const char* file, VkImageView& view);

};


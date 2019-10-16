#pragma once
#include "XVulkan.h"

class XImage
{

	friend class XVulkan;

	XVkImage xvkImage;
	float width, height;

	bool destroyed = false;
public:
	XImage();
	~XImage();

	bool Load(const char* file);

	void Destroy();
};


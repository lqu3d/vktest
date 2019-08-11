#pragma once

#include <glm/glm.hpp>	
#include "XVulkan.h"

class XModel
{
public:
	void SetupData() {
		float fov = glm::radians(45.0f);
		float wdh = xvk.xWnd.width * 1.0f / xvk.xWnd.height;
		float hdw = xvk.xWnd.height * 1.0f / xvk.xWnd.width;
		fov *= wdh;


	}

	void Render() {

	}

	
};


#pragma once
#include <iostream>

#include "DrawCube.h"

class XGame
{
public:
	void Start() {
		SetupCamera();

		auto obj = objMgr.AddObject<DrawCube>();
		
	}

	void Update() {
		
	}

	void OnDestroy() {
		
	}

	void SetupCamera() {
		//float fov = glm::radians(45.0f);
		//float wdh = xvk.xWnd.width * 1.0f / xvk.xWnd.height;
		//float hdw = xvk.xWnd.height * 1.0f / xvk.xWnd.width;
		//fov *= wdh;

	}
};





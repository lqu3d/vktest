#pragma once
#include <iostream>
class XGame
{
public:
	void Start() {
		std::cout << ":start" << std::endl;
	}

	void Update() {
		std::cout << ":update" << std::endl;

	}

	void OnDestroy() {
		std::cout << ":destroy" << std::endl;

	}
};


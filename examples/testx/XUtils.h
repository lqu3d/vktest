#pragma once

#define X_OBJ_RELEASE(x){ if(x){ delete x; x = NULL;}}
#define X_ARR_RELEASE(x){ if(x){delete[] x; x = NULL;}}

#include <string>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace XUtils {

	const float XEps = 0.000001f;

	const std::string shaderRootPath = "shaders/";
	bool XIsZero(float fx);

	bool XIsZero(double fx);

	void XLogToFile();

	void XPrint(glm::mat4 m, const char* pInfo = NULL);

	void XPrint(glm::vec3 v, const char* pInfo = NULL);

	void XPrint(glm::vec4 v, const char* pInfo = NULL);
#pragma region Ä£°åÊµÏÖ 
	template<typename T1, typename T2>
	struct XSameType
	{
		operator bool()
		{
			return false;
		}
	};

	template<typename T1>
	struct XSameType<T1, T1>
	{
		operator bool()
		{
			return true;
		}
	};

#pragma endregion

}







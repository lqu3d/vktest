#include <iostream>
#include "XUtils.h"

void XUtils::XLogToFile()
{
}

void XUtils::XPrint(glm::mat4 m, const char* pInfo)
{
	printf("矩阵%s\n", pInfo!=NULL ? pInfo : "" );
	printf("%f, %f, %f, %f\n", m[0].x, m[0].y, m[0].z, m[0].w);
	printf("%f, %f, %f, %f\n", m[1].x, m[1].y, m[1].z, m[1].w);
	printf("%f, %f, %f, %f\n", m[2].x, m[2].y, m[2].z, m[2].w);
	printf("%f, %f, %f, %f\n\n", m[3].x, m[3].y, m[3].z, m[3].w);

}

void XUtils::XPrint(glm::vec3 v, const char* pInfo)
{
	printf("向量%s\n", pInfo != NULL ? pInfo : "");
	printf("%f, %f, %f\n", v.x, v.y, v.z);
}

void XUtils::XPrint(glm::vec4 v, const char* pInfo)
{
	printf("向量%s\n", pInfo != NULL ? pInfo : "");
	printf("%f, %f, %f, %f\n", v.x, v.y, v.z, v.w);
}

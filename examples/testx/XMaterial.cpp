#include <fstream>
#include "XMaterial.h"
#include "XRender.h"

XMaterial::XMaterial(XGameObject* gameObject):XComponent(gameObject)
{
	//按材质分类，添加到render中
	xrender.AddGameObject(gameObject);

}

void XMaterial::OnStart()
{
}

void XMaterial::OnUpdate()
{
}

void XMaterial::OnDestroy()
{
	//没有材质的物体不渲染，从渲染器中移除
	xrender.RemoveGameObject(gameObject);
}

void XMaterial::SetShaderVs(const char* file)
{
	if (vsFilename == file) return;

	vsFilename = file;
	std::string path = XUtils::shaderRootPath + file;

	std::fstream fs;
	fs.open(path, std::ios::in);
	if (!fs) {
		return;
	}

	
}

void XMaterial::SetShaderPs(const char* file)
{
	if (psFilename == file) return;

	psFilename = file;
	std::string path = XUtils::shaderRootPath + file;

	std::fstream fs;
	fs.open(path, std::ios::in);
	if (!fs) {
		return;
	}


}

uint* XMaterial::GetVsShaderSpirv()
{
	return vsCode.data();
}

uint XMaterial::GetVsShaderSpirvLength()
{
	return vsCode.size();
}

uint* XMaterial::GetPsShaderSpirv()
{
	return psCode.data();
}

uint XMaterial::GetPsShaderSpirvLength()
{
	return psCode.size();
}



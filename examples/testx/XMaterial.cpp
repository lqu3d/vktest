#include <fstream>
#include "XMaterial.h"
#include "XRender.h"

XMaterial::XMaterial(XGameObject* gameObject):XComponent(gameObject)
{
	//�����ʷ��࣬��ӵ�render��
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
	//û�в��ʵ����岻��Ⱦ������Ⱦ�����Ƴ�
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



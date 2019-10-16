#include <fstream>
#include <sstream>

#include "XMaterial.h"
#include "XRender.h"

XMaterial::XMaterial(XGameObject* gameObject):XComponent(gameObject)
{
	//�����ʷ��࣬��ӵ�render��
	xrender.AddGameObject(gameObject);

}

void XMaterial::LoadShader(const char* file, char** ppCode, uint* pLen)
{
	X_OBJ_RELEASE(*ppCode);

	std::string path = XUtils::shaderRootPath + file;

	std::fstream fs;
	fs.open(path, std::ios::in);
	if (!fs) {
		return;
	}

	//��ȡ�ļ��ֽ���
	fs.seekg(0, std::ios::end);
	*pLen = fs.tellg();
	fs.seekg(0, std::ios::beg);

	uint len = *pLen;
	*ppCode = new char[len];
	fs.read(*ppCode, len);

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
	
	LoadShader(file, &pVsCode, &vsCodeLength);
	
}

void XMaterial::SetShaderPs(const char* file)
{
	if (psFilename == file) return;
	psFilename = file;

	LoadShader(file, &pPsCode, &psCodeLength);
}

uint* XMaterial::GetVsShaderSpirv()
{
	return (uint*)pVsCode;
}

uint XMaterial::GetVsShaderSpirvLength()
{
	return vsCodeLength;
}

uint* XMaterial::GetPsShaderSpirv()
{
	return (uint*)pPsCode;
}

uint XMaterial::GetPsShaderSpirvLength()
{
	return psCodeLength;
}

void XMaterial::SetBaseMap(const char* file)
{
	if (!strcmp(file, imageFilePath))
		return;

	baseMap->Destroy();
	X_OBJ_RELEASE(baseMap);

	baseMap = new XImage();
	baseMap->Load(file);


}

XImage* XMaterial::GetBaseMap()
{
	return nullptr;
}

void XMaterial::SetNormalMap(const char* file)
{
}

XImage* XMaterial::GetNormalMap()
{
	return nullptr;
}



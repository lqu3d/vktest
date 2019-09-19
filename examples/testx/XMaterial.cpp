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


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


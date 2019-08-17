#include "XComponent.h"

XComponent::XComponent(XGameObject* gameObject)
	:gameObject(gameObject), transform(new XTransform(gameObject))
{
	
}

void XComponent::OnStart()
{
}

void XComponent::OnUpdate()
{
}

void XComponent::OnDestroy()
{
}

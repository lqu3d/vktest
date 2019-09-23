#include "XComponent.h"

XComponent::XComponent(XGameObject* gameObject)
	:gameObject(gameObject), transform(new XTransform(gameObject))
{
	
}

XComponent::~XComponent()
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

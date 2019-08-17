#include "XTransform.h"
#include <glm/ext.hpp>

XTransform::XTransform(XGameObject* gameObject)
	: gameObject(gameObject)
	
{
	position = glm::vec3(0);

}

void XTransform::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	Refresh();
}

void XTransform::SetPosition(const glm::vec3& pos)
{
	position = pos;
	Refresh();

}

void XTransform::SetX(float x)
{
	position.x = x;
	Refresh();

}

void XTransform::SetY(float y)
{
	position.y = y;
	Refresh();

}

void XTransform::SetZ(float z)
{
	position.z = z;
	Refresh();

}

const glm::vec3* XTransform::GetPosition()
{
	return &position;
}

void XTransform::SetParent(XTransform* parent)
{
	Refresh();
}

XTransform* XTransform::GetParent()
{
	return nullptr;
}

void XTransform::LookAt(const vec3 & eye, const vec3 & center, const vec3& up)
{
	tmView = glm::lookAt(eye, center, up);
}

const glm::mat4* XTransform::GetMatrix()
{
	return &tmView;
}


void XTransform::Refresh()
{
	//update self
	if (parent) {

	}

	//update childrens
	for each (auto var in childrens)
	{

	}
}

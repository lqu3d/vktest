#include "XTransform.h"
#include <glm/ext.hpp>

XTransform::XTransform(XGameObject* gameObject)
	: gameObject(gameObject)
	
{
	SetPos(0, 0, 0);
	SetRot(0, 0, 0);
	SetScale(1, 1, 1);

}

void XTransform::SetPos(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	posChanged = true;
}

void XTransform::SetPos(const glm::vec3& pos)
{
	position = pos;
	posChanged = true;
}

void XTransform::SetX(float x)
{
	position.x = x;
	posChanged = true;
}

void XTransform::SetY(float y)
{
	position.y = y;
	posChanged = true;
}

void XTransform::SetZ(float z)
{
	position.z = z;
	posChanged = true;
}

/***���ӹ۲���Ʒ�
* ֻ�е�һ�����ݱ��۲�ʱ����ȥ������
* �ŵ㣺���������ϱ������ü���
* ȱ�㣺����ʽGET����ɺ�ʱ���壬�ɲ���Ԥ��GET�����
*/
const glm::vec3* XTransform::GetPosition()
{
	if (posChanged) {
		RefreshHierachy();
		posChanged = false;
	}
	return &position;
}

void XTransform::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	scaleChanged = true;
}

void XTransform::SetScale(const vec3& scale)
{
	this->scale = scale;
	scaleChanged = true;
}

void XTransform::SetScaleX(float x)
{
	scale.x = x;
	scaleChanged = true;

}

void XTransform::SetScaleY(float y)
{
	scale.y = y;
	scaleChanged = true;

}

void XTransform::SetScaleZ(float z)
{
	scale.z = z;
	scaleChanged = true;

}

const vec3* XTransform::GetScale()
{
	if (scaleChanged) {
		RefreshHierachy();
		scaleChanged = false;
	}
	return &scale;
}

void XTransform::SetRot(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
	rotChanged = true;
}

void XTransform::SetRot(const vec3& rot)
{
	rotation = rot;
	rotChanged = true;
}

void XTransform::SetRotX(float x)
{
	rotation.x = x;
	rotChanged = true;
}

void XTransform::SetRotY(float y)
{
	rotation.y = y;
	rotChanged = true;
}

void XTransform::SetRotZ(float z)
{
	rotation.z = z;
	rotChanged = true;
}

const vec3* XTransform::GetRot()
{
	//�����ƽ����ת�ȼ��ڴӾ�����ϵ�任��������ϵ������任���̾�����ͼ�任����ͼ����
	if (rotChanged) {
		RefreshHierachy();
		rotChanged = false;
	}
	return &rotation;
}

void XTransform::SetParent(XTransform* parent)
{
	this->parent = parent;
	parentChanged = true;
}

XTransform* XTransform::GetParent()
{
	if (parentChanged) {
		RefreshHierachy();
		parentChanged = false;
	}
	return parent;
}

void XTransform::LookAt(const vec3 & eye, const vec3 & center, const vec3& up)
{
	tmView = glm::lookAt(eye, center, up);
}

const glm::mat4* XTransform::GetMatrix()
{
	return &tmView;
}


void XTransform::RefreshHierachy()
{
	if (posChanged) {
		tmProj = glm::translate(tmView, position);
	}

	//update self
	if (parent) {

	}

	//update childrens
	for each (auto var in childrens)
	{

	}
}

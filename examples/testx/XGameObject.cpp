#include "XGameObject.h"
#include "XComponent.h"
#include "XUtils.h"
#include "XTransform.h"

void XGameObject::RemoveAllComponents()
{
	for (size_t i = 0; i < objList->size(); i++)
	{
		auto obj = (*objList)[i];
		obj->OnDestroy();

		X_OBJ_RELEASE(obj);
	}

	objList->clear();
	
}

void XGameObject::OnStart()
{
	auto list = *objList;
	for each (auto var in list)
	{
		var->OnStart();
	}

}

void XGameObject::OnUpdate()
{
	auto list = *objList;
	for each (auto var in list)
	{
		var->OnUpdate();
	}
}

void XGameObject::OnDestroy()
{
	/*** �ͷ��ڴ棬C++�ͷ��ڴ����ӵ׵��߲���ͷţ���ֱ���ͷ���߲�ָ����ײ�ָ�붪ʧ�ڴ�й©
	*1�����ͷŸ�����ڴ�
	*2���ͷŴ�����������ռ�õ��ڴ�(delete objList�������ʹSTL��������������������
	*/

	//step 1
	RemoveAllComponents();

	//step2
	X_OBJ_RELEASE(objList);
}

/*** ����ʹ��std::string������char*��const char* ��ԭ��
* һ, ��ʹ��char*,���ⲿʹ�õ���string���ͻ�const char*���޷�ת�������ⲿֻ�ܣ�
1���������ַ���������XGameObject("myname")������ÿ�����ֶ��洢�ڳ���������������ʱ�ַ��������޷����٣��ڴ治�ɿء�
2����һ��ָ������ַ�����ָ�룬���������Լ���Ҫ���ַ�������һ�ݱ��浽���ڣ�����ֱ�ӱ���ָ�룬��Ϊ�ǻᵼ�������ڲ��ɿ�
* ������ʹ��const char*������������Զ���ɸģ������˹��ܣ�����ȡ
* ����ʹ��string����ֵʱ�Զ������˲����ĸ������Ժ�Ҳ���Ը��ģ��ⲿ���Դ����������ַ�����char*,const char*, string)����������ʱ�ַ���Ҳ������
*/
XGameObject::XGameObject(std::string name, XTransform* parent):transform(new XTransform(this))
{
	this->name = name; //����һ����������ԭ���ַ��������˹�ϵ
	transform->parent = parent;
}

void XGameObject::SetActive(bool active)
{
	isActive = active;
}

bool XGameObject::IsActive()
{
	return isActive;
}



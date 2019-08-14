#include "XGameObject.h"
#include "XComponent.h"
#include "XUtils.h"

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

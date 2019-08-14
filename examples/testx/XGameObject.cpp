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
	/*** 释放内存，C++释放内存必须从底到高层层释放，若直接释放最高层指针则底层指针丢失内存泄漏
	*1，先释放各组件内存
	*2，释放存放组件的容器占用的内存(delete objList操作会促使STL调用容器的析构函数）
	*/

	//step 1
	RemoveAllComponents();

	//step2
	X_OBJ_RELEASE(objList);
}

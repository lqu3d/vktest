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
	/*** 释放内存，C++释放内存必须从底到高层层释放，若直接释放最高层指针则底层指针丢失内存泄漏
	*1，先释放各组件内存
	*2，释放存放组件的容器占用的内存(delete objList操作会促使STL调用容器的析构函数）
	*/

	//step 1
	RemoveAllComponents();

	//step2
	X_OBJ_RELEASE(objList);
}

/*** 参数使用std::string而不是char*或const char* 的原理
* 一, 若使用char*,若外部使用的是string类型或const char*则无法转换，则外部只能：
1，传字面字符串常量如XGameObject("myname")，这样每个名字都存储在常量区，物体销毁时字符串常量无法销毁，内存不可控。
2，传一个指向堆上字符串的指针，这样我们自己还要把字符串拷贝一份保存到类内，不能直接保存指针，因为那会导致生命期不可控
* 二，若使用const char*，导致名字永远不可改，限制了功能，不可取
* 三，使用string，赋值时自动拷贝了参数的副本，以后也可以更改，外部可以传任意类型字符串（char*,const char*, string)，物体销毁时字符串也会销毁
*/
XGameObject::XGameObject(std::string name, XTransform* parent):transform(new XTransform(this))
{
	this->name = name; //拷贝一个副本，与原来字符串脱离了关系
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



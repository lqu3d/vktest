/*** 【设计原则】头文件只包含基类头文件
* 1，实现放到CPP文件中，在其中包含需要的头文件
* 2，头文件中外部类型引用全部用指针，这样就不用包含相应头文件，只需要进行类的前置声明
*/
#pragma once
#include<vector>

#include "XObject.h"

class XComponent;
class XGameObject :
	public XObject
{
	friend class XObjectMgr;
private:
	std::vector<XComponent*>* objList = new std::vector<XComponent*>();
public:
	template<typename T> T* AddComponent();
	template<typename T> T* GetComponent();
	template<typename T> void RemoveComponent();
	template<typename T> void RemoveAllComponents();
	void RemoveAllComponents();
protected:
	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
};


#pragma region 模板实现

template<typename T>
inline T* XGameObject::AddComponent()
{
	//显式赋值，用于检查T是不是XComponent的子类
	XComponent* go = new T(this);

	objList->push_back(go);
	return (T*)go;
}

template<typename T>
inline T* XGameObject::GetComponent()
{
	for (size_t i = 0; i < objList->size(); i++)
	{
		if (XSameType<T, decltype((*objList)[i])>())
			return (*objList)[i];
	}

	return NULL;
}

template<typename T>
inline void XGameObject::RemoveComponent()
{
	for(auto iter= objList->begin(); iter!=objList->end(); ++iter)
	{
		if (XSameType<T, decltype(*iter)>())
		{
			X_OBJ_RELEASE(*iter);
			objList->erase(iter);
			break;
		}
	}
}

template<typename T>
inline void XGameObject::RemoveAllComponents()
{
	std::vector<XGameObject*> vec;
	for (auto iter = objList->begin(); iter != objList->end(); ++iter)
	{
		if (XSameType<T, decltype(*iter)>())
		{
			vec.push_back(*iter);
		}
	}

	for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
		X_OBJ_RELEASE(*iter);
		objList->erase(iter);
	}
}

#pragma endregion

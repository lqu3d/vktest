/*** 【设计原则】头文件只包含基类头文件
* 1，实现放到CPP文件中，在其中包含需要的头文件
* 2，头文件中外部类型引用全部用指针，这样就不用包含相应头文件，只需要进行类的前置声明
*/
#pragma once
#include<vector>
#include<string>

#include "XObject.h"
#include "XTransform.h"

class XComponent;
class XGameObject :
	public XObject
{
	friend class XObjectMgr;
private:
	std::vector<XComponent*>* objList = new std::vector<XComponent*>();

protected:
	virtual void OnStart() override;

	virtual void OnUpdate() override;

	virtual void OnDestroy() override;

private:
	//只允许XObjectMgr构造，不允许继承，不允许外部私自调用-防止生成不受管制的GO
	XGameObject(std::string name = "GameObject", XTransform* parent = NULL);

public:
	XTransform* const transform; //只在GameObject生成时生成
	std::string name;

public:
	template<typename T> T* AddComponent() {
		//显式赋值，用于检查T是不是XComponent的子类
		XComponent* go = new T(this);

		objList->push_back(go);
		return (T*)go;
	}
	
	template<typename T> T* GetComponent() {
		for (size_t i = 0; i < objList->size(); i++)
		{
			if (XSameType<T, decltype((*objList)[i])>())
				return (*objList)[i];
		}

		return NULL;
	}
	
	template<typename T> void RemoveComponent() {
		for (auto iter = objList->begin(); iter != objList->end(); ++iter)
		{
			if (XSameType<T, decltype(*iter)>())
			{
				X_OBJ_RELEASE(*iter);
				objList->erase(iter);
				break;
			}
		}
	}
	
	template<typename T> void RemoveAllComponents() {
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

	void RemoveAllComponents();

};

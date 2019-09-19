/*** 【设计原则】头文件只包含基类头文件
* 1，实现放到CPP文件中，在其中包含需要的头文件
* 2，头文件中外部类型引用全部用指针，这样就不用包含相应头文件，只需要进行类的前置声明
*/
#pragma once
#include<vector>
#include<string>
#include "XUtils.h"
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
			/*** BUG 修复
			* decltype得到的是变量的字面类型，并不能得到一个指针的实际类型
			* 例：XComponent* pc = new XCamera(), decltype(pc) 得到 XComponent，而不是XCamera
			* 使用dynamic_cast的问题是：可以使用基类来取来所有此基类的子类，这虽然不精确，但也有好处
			* 类型u3d的 GetCompoent<Renderer>()就能取得所有渲染组件
			*/
			T* po = dynamic_cast<T*>((*objList)[i]);
			if (po != NULL) {
				return po;
			}

			//旧的方式实现有BUG，因为decltype反应的只是变量的字面类型，并不能反应出一个指针的实际类型，比如一个基类指针指向子类时
			//if (XUtils::XSameType<T*, decltype((*objList)[i])>())
			//	return (T*)(*objList)[i];
		}

		return NULL;
	}
	
	template<typename T> void RemoveComponent() {
		for (auto iter = objList->begin(); iter != objList->end(); ++iter)
		{
			T* po = dynamic_cast<T*>((*objList)[i]);
			if (po != NULL) {
				X_OBJ_RELEASE(*iter);
				objList->erase(iter);
				break;
			}

			//旧的方式
			//if (XUtils::XSameType<T, decltype(*iter)>())
			//{
			//	X_OBJ_RELEASE(*iter);
			//	objList->erase(iter);
			//	break;
			//}
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

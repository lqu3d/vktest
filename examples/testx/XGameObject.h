#pragma once
#include<vector>

#include "XObject.h"

class XGameObject :
	public XObject
{
private:
	std::vector<XGameObject*>* objList = new std::vector<XGameObject*>();
public:
	template<typename T> T* AddComponent();
	template<typename T> T* GetComponent();
	template<typename T> void RemoveComponent();
	template<typename T> void RemoveAllComponents();

	void RemoveAllComponents();
};


#pragma region Ä£°åÊµÏÖ

template<typename T>
inline T* XGameObject::AddComponent()
{
	
	auto go = new T();
	objList->push_back(go);
	return go;
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

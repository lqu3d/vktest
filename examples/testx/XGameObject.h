/*** �����ԭ��ͷ�ļ�ֻ��������ͷ�ļ�
* 1��ʵ�ַŵ�CPP�ļ��У������а�����Ҫ��ͷ�ļ�
* 2��ͷ�ļ����ⲿ��������ȫ����ָ�룬�����Ͳ��ð�����Ӧͷ�ļ���ֻ��Ҫ�������ǰ������
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


#pragma region ģ��ʵ��

template<typename T>
inline T* XGameObject::AddComponent()
{
	//��ʽ��ֵ�����ڼ��T�ǲ���XComponent������
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

/*** �����ԭ��ͷ�ļ�ֻ��������ͷ�ļ�
* 1��ʵ�ַŵ�CPP�ļ��У������а�����Ҫ��ͷ�ļ�
* 2��ͷ�ļ����ⲿ��������ȫ����ָ�룬�����Ͳ��ð�����Ӧͷ�ļ���ֻ��Ҫ�������ǰ������
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
	//ֻ����XObjectMgr���죬������̳У��������ⲿ˽�Ե���-��ֹ���ɲ��ܹ��Ƶ�GO
	XGameObject(std::string name = "GameObject", XTransform* parent = NULL);

public:
	XTransform* const transform; //ֻ��GameObject����ʱ����
	std::string name;

public:
	template<typename T> T* AddComponent() {
		//��ʽ��ֵ�����ڼ��T�ǲ���XComponent������
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

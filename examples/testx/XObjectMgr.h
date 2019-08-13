/*** �����ԭ��ͷ�ļ�ֻ��������ͷ�ļ�
* 1��ʵ�ַŵ�CPP�ļ��У������а�����Ҫ��ͷ�ļ�
* 2��ͷ�ļ����ⲿ��������ȫ����ָ�룬�����Ͳ��ð�����Ӧͷ�ļ���ֻ��Ҫ�������ǰ������
*/
#pragma once
#include<vector>

class XObject;
class XObjectMgr
{
private:

	friend class XGameMgr;
	/*** vector��������Ϊָ��ĺô���
	*vector���ڴ��������ʱ���ܱ��ͷ�(ʹ��swap����)��ָ�������ʱ��delete����ʹvector�ڴ���ͷ�
	*���vector����Ϊ������ֻҪ��Ϸ������vector���ڴ���޷����ͷţ��һ�Խ��Խ��
	*����һ����Ϸ���м��죬���ܻ������ڴ�й©��崻�
	*/
	std::vector<XObject*>* pObjList = new std::vector<XObject*>();
public:
	template<typename T> T* AddObject();

	void DestroyObject(XObject* pObj);

	bool HasObject(XObject* pObj);
protected:
	void Start();

	void Update();

	void Clear();

	void OnDestroy();
};

extern XObjectMgr objMgr;

#pragma region template implement

/*** ֻ��AddObject�����ṩGetObject�Ĳ������ϲ��߼��Լ�����ָ�룬���ǱȽ��ִ���ģʽ
* Ϊ����߱���Ч�ʣ����Կ���ÿAddObjectһ����һ����
*/
template<typename T>
inline T* XObjectMgr::AddObject()
{
	XObject* obj = new T();
	if (obj == NULL)
		return NULL;

	pObjList->push_back(obj);
	obj->OnStart();

	return (T*)obj;
}
#pragma endregion



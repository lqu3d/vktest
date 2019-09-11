#include "XGameObject.h"
#include "XObjectMgr.h"
#include "XUtils.h"

XObjectMgr xobjMgr;

/***
*�����ڻ���ʱҪ��Ҫ������ش���
*��Ҫ���ײ�Ҫ���⣬���ϲ���Եõ���ȫ�Ŀ��ƣ�������˶���أ��ϲ�Ϳ��Ʋ����ڴ����ȫ�ͷţ�����GC����һ����������
*���Ҫ������أ����ϲ��߼�ȥ��
*/
void XObjectMgr::DestroyObject(XGameObject* pObj)
{
	if (pObj == NULL)
		return;

	for (auto iter = pObjList->begin(); iter != pObjList->end(); ++iter) {
		if (*iter._Ptr == pObj) {
			
			//step1�����������Ƴ�
			pObjList->erase(iter);

			//step2�����������Լ������ٴ������ͷ�����ĸ����
			pObj->OnDestroy();

			//step3���������屾��
			X_OBJ_RELEASE(pObj);

			break;
		}
	}
}

bool XObjectMgr::HasObject(XGameObject* pObj)
{
	if (pObj == NULL)
		return false;

	for (size_t i = 0; i < pObjList->size(); i++)
	{
		if ((*pObjList)[i] == pObj)
		{
			return true;
		}
	}

	return false;
}

#pragma region protected
void XObjectMgr::Start()
{
	pObjList->reserve(1000);
}

void XObjectMgr::Update()
{
	for (size_t i = 0; i < pObjList->size(); i++)
	{
		auto po = (*pObjList)[i];
		po->OnUpdate();
	}
}


/*** ע�⣬��ղ������������ж���
*һ������������Ϸ���ݣ����������͹����߻��ڣ�ֻ�����������
*/
void XObjectMgr::Clear()
{
	for (size_t i = 0; i < pObjList->size(); i++)
	{
		auto po = (*pObjList)[i];
		po->OnDestroy();
	}

	pObjList->clear();
}

void XObjectMgr::Destroy()
{
	Clear();

	//����delete��ǿ��vector�������������ͷ��ڴ�
	X_OBJ_RELEASE(pObjList);
}
#pragma endregion




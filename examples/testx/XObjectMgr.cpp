#include "XObject.h"


/***
*�����ڻ���ʱҪ��Ҫ������ش���
*��Ҫ���ײ�Ҫ���⣬���ϲ���Եõ���ȫ�Ŀ��ƣ�������˶���أ��ϲ�Ϳ��Ʋ����ڴ����ȫ�ͷţ�����GC����һ����������
*���Ҫ������أ����ϲ��߼�ȥ��
*/
void XObjectMgr::DestroyObject(XObject* pObj)
{
	if (pObj == NULL)
		return;

	for (auto iter = pObjList->begin(); iter != pObjList->end(); ++iter) {
		if (*iter._Ptr == pObj) {
			pObjList->erase(iter);
			delete pObj;
			break;
		}
	}
}

void XObjectMgr::Start()
{
	pObjList->reserve(1000);
}

void XObjectMgr::Update()
{
	for (size_t i = 0; i < pObjList->size(); i++)
	{
		auto po = (*pObjList)[i];
		if (po) {
			po->OnUpdate();
		}
	}
}

void XObjectMgr::Clear()
{
	for (size_t i = 0; i < pObjList->size(); i++)
	{
		auto po = (*pObjList)[i];
		if (po) {
			po->OnDestroy();
		}
	}

	pObjList->clear();
	
	//����delete��ǿ��vector�������������ͷ��ڴ�
	X_OBJ_RELEASE(pObjList);
}

void XObjectMgr::OnDestroy()
{
}


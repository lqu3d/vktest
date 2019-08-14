#include "XGameObject.h"
#include "XObjectMgr.h"
#include "XUtils.h"

XObjectMgr objMgr;

/***
*这里在回收时要不要做对象池处理？
*不要，底层要纯粹，让上层可以得到完全的控制，如果做了对象池，上层就控制不了内存的完全释放，就像GC机制一样让人难受
*如果要做对象池，让上层逻辑去做
*/
void XObjectMgr::DestroyObject(XGameObject* pObj)
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

	//调用delete，强制vector调用析构函数释放内存
	X_OBJ_RELEASE(pObjList);
}

void XObjectMgr::OnDestroy()
{
}
#pragma endregion




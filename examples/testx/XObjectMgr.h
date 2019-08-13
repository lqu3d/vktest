/*** 【设计原则】头文件只包含基类头文件
* 1，实现放到CPP文件中，在其中包含需要的头文件
* 2，头文件中外部类型引用全部用指针，这样就不用包含相应头文件，只需要进行类的前置声明
*/
#pragma once
#include<vector>

class XObject;
class XObjectMgr
{
private:

	friend class XGameMgr;
	/*** vector对象声明为指针的好处：
	*vector的内存仅在析构时才能被释放(使用swap除外)，指针可以随时被delete，促使vector内存的释放
	*如果vector声明为对象，则只要游戏不结束vector的内存就无法被释放，且会越来越大
	*考虑一个游戏运行几天，可能会由于内存泄漏而宕机
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

/*** 只有AddObject，不提供GetObject的操作，上层逻辑自己保存指针，这是比较现代的模式
* 为了提高遍历效率，可以考虑每AddObject一次排一次序
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



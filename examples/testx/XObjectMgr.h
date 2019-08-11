#pragma once

#include<vector>

class XObject;
class XObjectMgr
{
private:

	/*** vector对象声明为指针的好处：
	*vector的内存仅在析构时才能被释放(使用swap除外)，指针可以随时被delete，促使vector内存的释放
	*如果vector声明为对象，则只要游戏不结束vector的内存就无法被释放，且会越来越大
	*考虑一个游戏运行几天，可能会由于内存泄漏而宕机
	*/
	std::vector<XObject*>* pObjList = new std::vector<XObject*>();
public:
	XObject* AddObject();

	void DestroyObject(XObject* pObj);
protected:
	void Start();

	void Update();

	void Clear();
};


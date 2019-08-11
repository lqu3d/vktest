#pragma once

#include<vector>

class XObject;
class XObjectMgr
{
private:

	/*** vector��������Ϊָ��ĺô���
	*vector���ڴ��������ʱ���ܱ��ͷ�(ʹ��swap����)��ָ�������ʱ��delete����ʹvector�ڴ���ͷ�
	*���vector����Ϊ������ֻҪ��Ϸ������vector���ڴ���޷����ͷţ��һ�Խ��Խ��
	*����һ����Ϸ���м��죬���ܻ������ڴ�й©��崻�
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


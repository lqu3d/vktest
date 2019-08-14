#pragma once

class XObject
{
	friend class XObjectMgr;
protected:
	virtual void OnStart();

	virtual void OnUpdate();

	virtual void OnDestroy();

};

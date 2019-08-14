#pragma once

class XObject
{
protected:
	virtual void OnStart() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDestroy() = 0;
};

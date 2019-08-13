#pragma once

class XGame
{
	friend class XGameMgr;
protected:
	void Start();

	void Update();

	void OnDestroy();

	void SetupCamera();
};





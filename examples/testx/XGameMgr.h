#pragma once


class XGameMgr
{
private:
	static XGameMgr* mgr;
	XGameMgr();
public:
	static XGameMgr* get();

	void Start();
	void Loop();
	void Clear();
	void Destroy();
};


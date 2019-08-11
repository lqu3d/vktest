#include "XGameMgr.h"
#include "XVulkan.h"
#include "XGame.h"

XGame xgame;

XGameMgr* XGameMgr::mgr;

XGameMgr::XGameMgr()
{
}

XGameMgr* XGameMgr::get()
{
	if (mgr == NULL) {
		mgr = new XGameMgr();
	}
	return mgr;
}

void XGameMgr::Start()
{
	xvk.Setup();

	xvk.BeginCmdBuffer();

	xgame.Start();
	objMgr.Start();

	xvk.EndCmdBuffer();
}

void XGameMgr::Loop()
{
	while (!xvk.xWnd.ShouldClose()) {
		xvk.xWnd.PollEvents();
		xgame.Update();
		objMgr.Update();
	}
}

void XGameMgr::Clear()
{
	objMgr.Clear();
}

void XGameMgr::Destroy()
{
	objMgr.OnDestroy();
	xgame.OnDestroy();
	xvk.Destroy();
}

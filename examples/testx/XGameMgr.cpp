#include "XGameMgr.h"
#include "XWindow.h"
#include "XGame.h"
#include "XObjectMgr.h"
#include "XRender.h"

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
	xobjMgr.Start();
	xgame.Start();
	xrender.Start();

}

void XGameMgr::Loop()
{
	while (!xWnd.ShouldClose()) {
		xWnd.PollEvents();

		xobjMgr.Update();
		xgame.Update();
	}
}

/*** 注意，清空并不是销毁所有东西
*一般清空是清除游戏数据，但各容器和管理者还在，只是数据清掉了
*/
void XGameMgr::Clear()
{
	xobjMgr.Clear();
}

void XGameMgr::Destroy()
{
	xobjMgr.Destroy();
	xgame.Destroy();
}

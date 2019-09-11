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

/*** ע�⣬��ղ������������ж���
*һ������������Ϸ���ݣ����������͹����߻��ڣ�ֻ�����������
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

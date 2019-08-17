#include "XGameMgr.h"
#include "XVulkan.h"
#include "XGame.h"
#include "XObjectMgr.h"

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

	objMgr.Start();
	xgame.Start();

	xvk.BeginCmdBuffer();


	

	xvk.EndCmdBuffer();
}

void XGameMgr::Loop()
{
	while (!xvk.xWnd.ShouldClose()) {
		xvk.xWnd.PollEvents();

		objMgr.Update();
		xgame.Update();
	}
}

/*** ע�⣬��ղ������������ж���
*һ������������Ϸ���ݣ����������͹����߻��ڣ�ֻ�����������
*/
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

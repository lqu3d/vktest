
#include "XGameMgr.h"

int main()
{
	XGameMgr::get()->Start();

	XGameMgr::get()->Loop();

	XGameMgr::get()->Clear();

	XGameMgr::get()->Destroy();
}

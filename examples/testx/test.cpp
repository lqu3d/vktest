
#include <iostream>
#include<vector>	
#include<string>	

#include "XVulkan.h"
#include "XModel.h"
#include "XGame.h"

XGame xgame;
int main()
{
	xvk.Setup();
	
	xvk.BeginCmdBuffer();
	xgame.Start();


	xvk.EndCmdBuffer();

	while (!xvk.xWnd.ShouldClose()) {
		xvk.xWnd.PollEvents();
		xgame.Update();
	}

	xgame.OnDestroy();
	xvk.Destroy();

}


#include <iostream>
#include<vector>	
#include<string>	

#include "XVulkan.h"

XVulkan xvk;

int main()
{
	xvk.Setup();

	xvk.BeginCmdBuffer();

	xvk.EndCmdBuffer();

	while (!xvk.ShouldClose()) {

	}
	
	xvk.Destroy();
}

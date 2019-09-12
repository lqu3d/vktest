#include "XRender.h"
#include "XVulkan.h"
#include "XObject.h"

XRenderer xrender;
void XRenderer::Start()
{
	xvk.Setup();
}

void XRenderer::Update()
{

	Render();
}

void XRenderer::Clear()
{
}

void XRenderer::Destroy()
{
	xvk.Destroy();
}

void XRenderer::Render()
{
	xvk.BeginCmdBuffer();




	xvk.EndCmdBuffer();
}

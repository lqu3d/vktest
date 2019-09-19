#include "XRender.h"
#include "XVulkan.h"
#include <algorithm>

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

void XRenderer::AddGameObject(XGameObject* gameObject)
{
	XMaterial* mat = gameObject->GetComponent<XMaterial>();
	auto mesh = gameObject->GetComponent<XMesh>();
	if (!mat || !mesh) return;

	auto iter = goMap.find(mat);
	if (iter != goMap.end()) {
		iter->second.push_back(mesh);
	}

}

void XRenderer::RemoveGameObject(XGameObject* gameObject)
{
	auto mat = gameObject->GetComponent<XMaterial>();
	auto mesh = gameObject->GetComponent<XMesh>();
	if (!mat || !mesh) return;

	auto iter = goMap.find(mat);
	if (iter != goMap.end()) {
		auto iter2 = std::find(iter->second.begin(), iter->second.end(), mesh);
		if (iter2 != iter->second.end()) {
			iter->second.erase(iter2);
		}
	}
}

void XRenderer::Render()
{
	xvk.BeginCmdBuffer();




	xvk.EndCmdBuffer();
}

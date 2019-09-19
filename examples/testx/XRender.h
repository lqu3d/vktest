#pragma once
#include <map>
#include <list>
#include "XGameObject.h"
#include "XMaterial.h"
#include "XMesh.h"

class XRenderer
{
public:
	void Start();

	void Update();

	void Clear();

	void Destroy();


	void AddGameObject(XGameObject* gameObject);

	void RemoveGameObject(XGameObject* gameObject);
private:

	void Render();

	std::map<XMaterial*, std::list<XMesh*>> goMap;
};

extern XRenderer xrender;
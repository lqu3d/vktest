#pragma once
class XRenderer
{
public:
	void Start();

	void Update();

	void Clear();

	void Destroy();

private:

	void Render();
};

extern XRenderer xrender;
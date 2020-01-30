#pragma once
#include "IScene.h"
#include "Material.h"
#include "Mesh.h"
#include "Graphics.h"

class SceneMainMenu : public Core::IScene
{
public:

	//TODO: Cpp dazu schreiben

	void Load();
	void UnLoad();
	void Update();
	void Draw();

private:
	Core::Material* mGradientMaterial = nullptr;
	Core::Mesh* mPlane = nullptr;
};

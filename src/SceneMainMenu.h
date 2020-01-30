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
	D3D11_BUFFER_DESC bufferDescription{};
	D3D11_SUBRESOURCE_DATA bufferSubresource{};
	ID3D11Buffer* buffer = nullptr;
};

#include "SceneMainMenu.h"

void SceneMainMenu::Load()
{
	mGradientMaterial = new Core::Material(("assets\\shader.txt"));
	mPlane = new Core::Mesh(Core::PrimitiveType::Plane);
	// Materials laden
	// Meshes laden
}

void SceneMainMenu::UnLoad()
{
	delete mGradientMaterial;
	delete mPlane;
	// Materials killen
	// Meshes killen
}

void SceneMainMenu::Update()
{
	// not yet implemented
}

void SceneMainMenu::Draw()
{
	D3D11_BUFFER_DESC bufferDescription{};
	bufferDescription.ByteWidth = sizeof( &(mPlane->Vertices));
	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescription.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA bufferSubresource{};
	bufferSubresource.pSysMem = &(mPlane->Vertices); //TODO: Maybe deref?

	ID3D11Buffer* buffer;
	Core::Graphics& gp = Core::Graphics::GetInstance();
	if (FAILED(gp.Device->CreateBuffer(&bufferDescription, &bufferSubresource, &buffer)))
		std::cerr << "Buffer geht nicht :/";

	gp.DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	gp.DeviceContext->IASetInputLayout(mGradientMaterial->ShaderInputLayout);
	gp.DeviceContext->VSSetShader(mGradientMaterial->ShaderVertex,nullptr,0);
	gp.DeviceContext->PSSetShader(mGradientMaterial->ShaderPixel,nullptr,0);
	const UINT stride = 28;
	const UINT offset = 0;
	gp.DeviceContext->IASetVertexBuffers(0,1,&buffer,&stride,&offset);

	gp.DeviceContext->Draw( 4 ,0); //Hack: maybe better: sizeof(mPlane->Vertices) / sizeof(mPlane->Vertices[0] / 3)

	//for each gameobject oder so, sortiert nach shader währ cool
		//Mesh mit Material setzen
		//Zeichnen
}

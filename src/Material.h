#pragma once
#include <string>
#include <d3d11.h>
#include <fstream>
#include <iostream>
#include "Graphics.h"
#include <D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

/*
	Material:
	Constructor: L�d eine Datei in der Shader enthalten sind
		kompiliert sie und stellt sie public zur verf�gung
		dateien schliessen
	Destructor: killt alle objekte hinter pointern
*/
namespace Core
{
	class Material
	{
	public:
		Material(std::string pFileName);

		~Material();

		ID3D11VertexShader* ShaderVertex = nullptr;
		ID3D11PixelShader* ShaderPixel = nullptr;
		D3D11_INPUT_ELEMENT_DESC ShaderInputDescription[2]{};
		ID3D11InputLayout* ShaderInputLayout = nullptr;
	
	private:
		ID3DBlob* mShaderDataPS; // puffer f�r compilierten Pixelshader
		ID3DBlob* mShaderError; // puffer f�r potenzielle fehler
		ID3DBlob* mShaderDataVS; // puffer f�r compilierten Vertexshader
	};
}

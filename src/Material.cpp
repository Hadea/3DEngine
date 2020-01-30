#include "Material.h"

Core::Material::Material(std::string pFileName)
{
	std::ifstream ShaderFile;
	ShaderFile.open(pFileName, std::ios::in ); // Offnet eine datei zum lesen (funktioniert wie eine Casette)
	if (ShaderFile)
	{
		ShaderFile.seekg(0, ShaderFile.end); // Datei bis ans ende vorspulen
		int fileLength = (int)ShaderFile.tellg() + 1; // aktuelle position (ende) speichern und position als dateigrösse nutzen

		ShaderFile.seekg(0, ShaderFile.beg); // Datei zurückspulen
		char* fileBuffer = new char[fileLength]; // Speicher als char array bereitstellen um datei darin zu speichern
		ZeroMemory(fileBuffer, fileLength); // Speicher zur sicherheit einfach mal nullen
		ShaderFile.read(fileBuffer, fileLength);

		ShaderFile.close(); // Betriebssystem bescheidgeben das wir fertig sind und andere die datei nutzen können. NICHT Vergessen!!
		
		if (FAILED( D3DCompile(fileBuffer, fileLength, "Shader.txt", nullptr, nullptr, "PS_Main", "ps_4_0", 0, 0, &mShaderDataPS, &mShaderError))) // shader compilieren
		{	// falls was schief geht ein paar ausgaben machen zum debuggen
			char* errorText = reinterpret_cast<char*>(mShaderError->GetBufferPointer());
			OutputDebugStringA(errorText);
			std::cout << "Shader kann nicht kompiliert werden :(";
		} 



		if (FAILED(D3DCompile(fileBuffer, fileLength, "Shader.txt", nullptr, nullptr, "VS_Main", "vs_4_0", 0, 0, &mShaderDataVS, &mShaderError))) // shader compilieren
		{	// falls was schief geht ein paar ausgaben machen zum debuggen
			char* errorText = reinterpret_cast<char*>(mShaderError->GetBufferPointer());
			OutputDebugStringA(errorText);
			std::cout << "Shader kann nicht kompiliert werden :(";
		}

		delete[] fileBuffer; // kopie der datei im RAM wird nicht mehr benötigt
		
		Graphics& gp = Graphics::GetInstance();
		

		if (FAILED(gp.Device->CreatePixelShader(mShaderDataPS->GetBufferPointer(),mShaderDataPS->GetBufferSize(),0,&ShaderPixel)))
			std::cerr << "Pixelshader kann nicht erstellt werden :(";
		if (FAILED(gp.Device->CreateVertexShader(mShaderDataVS->GetBufferPointer(), mShaderDataVS->GetBufferSize(), 0, &ShaderVertex)))
			std::cerr << "Vertexshader kann nicht erstellt werden :(";

		ShaderInputDescription[0].SemanticName = "POSITION";
		ShaderInputDescription[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		ShaderInputDescription[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		
		ShaderInputDescription[1].SemanticName = "COLOR";
		ShaderInputDescription[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		ShaderInputDescription[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		
		if(FAILED(gp.Device->CreateInputLayout(ShaderInputDescription,ARRAYSIZE(ShaderInputDescription),mShaderDataVS->GetBufferPointer(),mShaderDataVS->GetBufferSize(), &ShaderInputLayout)))
			std::cerr << "Input Layout konnte nicht erstellt werden :(";
	}
	else
	{
		std::cout << "Shaderdatei " << pFileName << " nicht geladen :(" << std::endl;
	}
}

Core::Material::~Material()
{
	if (ShaderPixel != nullptr) ShaderPixel->Release();
	if (ShaderVertex != nullptr)  ShaderVertex->Release();
	if (mShaderDataPS != nullptr)  mShaderDataPS->Release();
	if (mShaderError != nullptr)   mShaderError->Release();
	if (mShaderDataVS != nullptr)  mShaderDataVS->Release();
	if (ShaderInputLayout != nullptr)  ShaderInputLayout->Release();

}

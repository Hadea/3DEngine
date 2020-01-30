#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <iostream>

#pragma comment(lib, "d3d11.lib")

namespace Core
{
	class Graphics
	{
	public:
		void Initialize(HWND pWindowHandler);

		static Graphics & GetInstance();

		~Graphics();

		//static Graphics _instance;
		ID3D11Device* Device = nullptr;
		IDXGISwapChain* SwapChain = nullptr;
		ID3D11DeviceContext* DeviceContext = nullptr;
		D3D_FEATURE_LEVEL SelectedFeatureLevel = {};

	private:
		Graphics() {};
		Graphics(const Graphics&);
		Graphics& operator = (const Graphics &);


	};
}
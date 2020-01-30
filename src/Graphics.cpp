#include "Graphics.h"

Core::Graphics* Core::Graphics::mInstance = nullptr;

void Core::Graphics::Initialize(HWND pWindowHandler)
{
	OutputDebugString("preparing graphics");
	DXGI_SWAP_CHAIN_DESC mSCD = { 0 };
	mSCD.BufferCount = 1; // Anzahl der Buffer 0= Direkt auf GPU, 1 = DoubleBuffering, ...
	mSCD.BufferDesc.Width = 0;  // 0 = Max Fenstergr�sse, ansonsten Aufl�sung
	mSCD.BufferDesc.Height = 0; // 0 = Max Fenstergr�sse, ansonsten Aufl�sung
	mSCD.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; // Unspecified = mach nix, Stretching wenn Width und Height abweicht vom Screen
	mSCD.BufferDesc.RefreshRate.Numerator = 0;  // 0 =  no limit! MaxFPS   RTFM
	mSCD.BufferDesc.RefreshRate.Denominator = 0; // 0 =  no limit! Bilder Pro Frame
	mSCD.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; // Interlacing f�r alte Monitore ... no need
	mSCD.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // Art wie die Daten gespeichert werden sollen
	mSCD.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //Art der Verwendung des Buffers, wir wollen RenderTargets
	mSCD.SampleDesc.Count = 1;
	mSCD.SampleDesc.Quality = 0; // Aliasing einstellungen, 0 = n� da wir das lieber �ber shader selbst machen
	mSCD.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Art wie die Buffer ausgetauscht werden. Betriebssystem beachten!
	mSCD.OutputWindow = pWindowHandler; // Fenster auf dessen client bereich gezeichnet wird.
	mSCD.Windowed = true;


	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr, //Pointer zu gew�nschtem Adapter (kann Software, IGPU oder PEG )
		D3D_DRIVER_TYPE_HARDWARE, // Art des Treibers. Hardware = schnell, Reference = Bugfree, ...
		nullptr, // Pointer zum Treiber wenn Software_Type angegeben wurde
		0, // Flags die beim Debugging helfen k�nnen (einfach zusammen-odern): DEBUG f�r mehr Logs, SINGLETHREADED um Race conditions zu testen
		nullptr, // Featurelevels die angefragt werden sollen. H�chster nutzbarer wird dann auslesbar
		0, // 0 wenn keine Featurelevel angegeben sind, ansonsten _countof() auf den vorhergehen Parameter verwenden
		D3D11_SDK_VERSION, //Softwareversion von DirectX die ben�tigt wird
		&mSCD, //Adresse zum Struct
		&SwapChain, // Adresse des SwapChain Pointers wo die Swap Chain dann erstellt wird
		&Device,    // Adresse des Device Pointers wo das Device dann erstellt wird
		&SelectedFeatureLevel,  // Adresse der FeatureLevel-Variable wo ausgew�hlte Featurelevel eingetragen
		&DeviceContext   // Adresse des DeviceContext-Pointers wo der Device Context erstellt wird 
	)))
		std::cout << "Device and Swapchain failed :(" << std::endl;

}


Core::Graphics* Core::Graphics::GetInstance()
{
	if (mInstance == nullptr)
	{
		OutputDebugString("creating graphics");
		mInstance = new Graphics();
	}
	return mInstance;
}

Core::Graphics::~Graphics()
{
	OutputDebugString("unloading graphics");
	if (DeviceContext != nullptr) DeviceContext->Release();
	if (Device != nullptr) Device->Release();
	if (SwapChain != nullptr) SwapChain->Release();

}

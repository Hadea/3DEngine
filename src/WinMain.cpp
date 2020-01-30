#include <Windows.h>
#include "Window.h"
#include "Graphics.h"
#include <string>
#include <list>
#include "IScene.h"
#include "SceneMainMenu.h"

int CALLBACK WinMain(
	_In_	 HINSTANCE hInstance, //meine Instanz
	_In_opt_ HINSTANCE hPrevInstance, // Instanz die mich aufgerufen hat, seit Win 3.11 immer null
	_In_	 LPSTR lpCommandLine, // kompletter String der gestarteten Kommandozeile und aller parameter
	_In_	 int nCmdShow) // soll das Fenster angezeigt werden
{
	
	Core::Window mWindow(800,600, hInstance); // erstellt das Windows-Fenster

	OutputDebugString("HalloWelt");
	
	Core::Graphics::GetInstance()->Initialize(mWindow.WindowHandle);
	
	MSG mMsg = { 0 };

	/* Inhalt von MSG:
	HWND   hwnd;     // handle zu dem Fenster für das der Input bestimmt ist
	UINT   message;  // Typ der NAchricht
	WPARAM wParam;   // abhänging vom Nachrichtentyp andere Infos
	LPARAM lParam;   // abhänging vom Nachrichtentyp andere Infos
	DWORD  time;     // Zeit des Auslösens
	POINT  pt;       // Cursor Postition in Bildschirm-Koordinaten! Kann ausserhalb des Fensters sein
	DWORD  lPrivate; // DO NOT TOUCH :D
	*/

	std::list<Core::IScene*> SceneList; // erstellt eine Liste aus Pointern zu Szenen;
	SceneList.push_back(new SceneMainMenu()); // Szene wird geladen und am ende der Liste angefügt
	SceneList.back()->Load(); // Szene wird initialisiert
	
	ID3D11Texture2D* backBuffer;
	Core::Graphics::GetInstance()->SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	ID3D11RenderTargetView* renderTargetView;
	Core::Graphics::GetInstance()->Device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	Core::Graphics::GetInstance()->DeviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

	D3D11_VIEWPORT viewport{};
	viewport.Width= 800;
	viewport.Height = 600;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	Core::Graphics::GetInstance()->DeviceContext->RSSetViewports(1, &viewport);

	bool colorswitch = false;
	float clearColorA[4] = { 0.5f,0.5f,0.4f,1.0f };
	float clearColorB[4] = { 0.5f,0.4f,0.5f,1.0f };

	while (true)
	{
		SceneList.back()->Update(); // Aktualisiert die Oberste Szene, die anderen schlafen im Hintergrund.

		colorswitch = !colorswitch;


		Core::Graphics::GetInstance()->DeviceContext->ClearRenderTargetView(renderTargetView, (colorswitch? clearColorA: clearColorB));		//TODO: Prepare new frame with clearcolor

		SceneList.back()->Draw(); // Zeichnet die oberste Szene.
		Core::Graphics::GetInstance()->SwapChain->Present(4, 0);


		if (PeekMessage(
			&mMsg, // Adresse des Structs in den die Daten der Nachricht geschrieben werden
			nullptr, // Filter für das Fenster, handle = nur für das Fenster hinter dem Handle, nullptr = alles
			0, // unterste Message ID 
			0, // oberste Message ID, nur nachrichten innerhalb des Bereiches beachten. 0 = alles)
			PM_REMOVE)) // was soll mit der angeschauten nachricht passieren?
		{
			TranslateMessage(&mMsg);
			DispatchMessage(&mMsg);

			switch (mMsg.message)
			{
			case WM_CREATE:
				OutputDebugString("WM_CREATE gestartet\n");
				break;
			case WM_KEYDOWN:
				OutputDebugString("WM_KEYDOWN ");
				OutputDebugString(std::to_string(mMsg.wParam).c_str());
				OutputDebugString("\n");
				if (mMsg.wParam == 27) //if escape is pressed
					goto exitMainLoop;
				break;
			case WM_QUIT:
				goto exitMainLoop;
			default:
				break;
			}
		}
	}
exitMainLoop:

	for (auto Scene : SceneList)
		Scene->UnLoad();
	
	return 0;
}

#include "Window.h"

Core::Window::Window(uint16_t pResolutionX, uint16_t pResolutionY, HINSTANCE pInstance)
{
	const auto mClassName = "MeinFenster";

	WNDCLASSEX mWindowClass = { 0 };
	mWindowClass.cbSize = sizeof(WNDCLASSEX); // gr�sse des structs
	mWindowClass.style = CS_OWNDC; // Art des Fensters
	mWindowClass.lpfnWndProc = WinInputHandler; // wer k�mmert sich um Events aus Windows?
	mWindowClass.hInstance = pInstance; // zu wem geh�rt das fenster
	mWindowClass.lpszClassName = mClassName;
	mWindowClass.lpszMenuName = nullptr;


	if (!RegisterClassEx(&mWindowClass)) // Registriert die Klasse damit sie erstellt werden kann.
		throw "Klassenregistrierung kaputt :(";

	WindowHandle = CreateWindowExA(
		0, // zus�tzliche Styles des fensters. z.B. Scrollbars, Ramenoptionen, ...
		mClassName, //Name der Klasse die erzeugt werden soll
		"Titelleistentext xD", // Text in der Titelleiste
		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // standard styles wie MinimierButton, Rahmen zum vergr�ssern, Titelleiste, ...
		100, 100, pResolutionX, pResolutionY, // position und gr�sse des Fensters  X,Y,W,H
		nullptr, // pointer zum parent, obsolete
		nullptr, // pointer zum Men�-Strip
		pInstance, // pointer zur eigenen Inztanz
		nullptr); // zus�tzlicher Speicher der irgendwie verwendet werden kann.

	if (WindowHandle == nullptr)
		throw "Window creation failed :(";

	ShowWindow(WindowHandle, SW_SHOW);
	UpdateWindow(WindowHandle);
}

Core::Window::~Window()
{
	DestroyWindow(WindowHandle);

}

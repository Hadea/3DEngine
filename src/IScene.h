#pragma once

/*
	Grundaufbau aller Szenen mit Pflicht-Funktionen
*/

namespace Core
{
	class IScene
	{
	public:
		virtual void Load() = 0;
		virtual void UnLoad() = 0;
		virtual void Draw() = 0;
		virtual void Update() = 0;
		bool IsLoaded = false;
	};


}

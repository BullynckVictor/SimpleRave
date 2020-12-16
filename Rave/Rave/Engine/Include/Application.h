#pragma once
#include <functional>
#include <optional>
#include "Engine/Utilities/Include/Timer.h"
#include "Engine/Utilities/Include/PerformanceProfiler.h"
#include "Engine/Graphics/Include/Graphics.h"
#include "Engine/Include/Window.h"
#include "Engine/Include/MemoryManager.h"
#include "Engine/Audio/Include/AudioManager.h"
#include "Engine/Include/ComManager.h"

#include "Engine/Drawables/Include/Drawable.h"
#include "Engine/Drawables/Include/Shape.h"
#include "Engine/Drawables/Include/Sprite.h"
#include "Engine/Drawables/Include/Animation.h"

namespace rave
{
	class Application
	{
	public:
		Application(const wchar_t* windowName, const int width, const int height, const bool useMouseEvents = false, const bool useMouseRawDeltas = false, const wchar_t* className = L"RaveEngine Direct3D Class");
		virtual ~Application() {}

		void Go();

	protected:
		virtual void Update(const float dt) = 0;

		Vector2 MousePos() const noexcept;
		void ControllCamera(const float dt, const float moveSpeed = 1.0f, const float rotationSpeed = 1.0f, const float scrollSpeed = 15.0f) noexcept;
		void LoadTexture(const char* key, const wchar_t* path);

	private:
		Timer ft;
		PerformanceProfiler profiler;
		ImageDecoder decoder;

	protected:
		Graphics gfx;
		Window wnd;
		GraphicsMemory memory;
		AudioManager audio;
		Camera& camera;
	};

	template<typename T>
	requires std::is_base_of_v<Application, T>
	void Execute()
	{
		try
		{
			ComManager com;
			T{}.Go();
		}
		catch (rave::Exception& e)
		{
			MessageBox(NULL, e.whide_what(), L"rave::Exception", MB_OK | MB_ICONEXCLAMATION);
		}
		catch (std::exception& e)
		{
			MessageBox(NULL, Widen(e.what()).c_str(), L"std::exception", MB_OK | MB_ICONEXCLAMATION);
		}
		catch (...)
		{
			MessageBox(NULL, L"Unknown type caught", L"Unknown exception", MB_OK | MB_ICONEXCLAMATION);
		}
	}
}
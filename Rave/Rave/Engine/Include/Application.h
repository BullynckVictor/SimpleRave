#pragma once
#include "Engine/Utilities/Include/Timer.h"
#include "Engine/Graphics/Include/Graphics.h"
#include "Engine/Include/Window.h"

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

	private:
		Graphics gfx;
		Timer ft;

	protected:
		Window wnd;
	};

	template<typename T>
	requires std::is_base_of_v<Application, T>
	void Execute()
	{
		try
		{
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
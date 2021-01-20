#pragma once
#include "Engine/Include/Windows.h"
#include "Engine/Include/Application.h"

#include "Engine/Utilities/Include/Exception.h"
#include "Engine/Utilities/Include/Vector.h"
#include "Engine/Utilities/Include/Timer.h"
#include "Engine/Utilities/Include/PerformanceProfiler.h"
#include "Engine/Utilities/Include/Random.h"

#include "Engine/Audio/Include/Sound.h"

#include "Engine/Drawables/Include/Shape.h"
#include "Engine/Drawables/Include/Sprite.h"
#include "Engine/Drawables/Include/Animation.h"
#include "Engine/Drawables/Include/Cube.h"

#include "Engine/GUI/Include/guiWindow.h"

namespace rave
{
	template<void(*MainFunc)(void)>
	void Try()
	{
		try
		{
			ComManager com;
			MainFunc();
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


	template<typename T>
	requires std::is_base_of_v<Application, T>
	void Execute()
	{
		Try<[](){ T{}.Go(); }>();
	}
}
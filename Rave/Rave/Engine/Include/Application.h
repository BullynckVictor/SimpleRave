#pragma once
#include "Engine/Utilities/Include/Timer.h"
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	class Application
	{
	public:
		Application(const wchar_t* windowName, const int width, const int height);
		void Go() noexcept;

	protected:
		virtual void Update(const float dt) = 0;

	protected:
		Graphics gfx;

	private:
		Timer ft;
	};
}
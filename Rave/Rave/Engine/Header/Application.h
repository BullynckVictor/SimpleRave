#pragma once
#include "Engine/Header/Windows.h"
#include "Engine/Utilities/Header/Exception.h"

namespace rave
{
	class Application
	{
	public:
		Application(const wchar_t* windowName, const int width, const int height);
		void Go() noexcept;

	protected:
		virtual void Update(const float dt) = 0;

	private:
	};
}
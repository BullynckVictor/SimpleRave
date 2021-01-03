#pragma once
#include "Engine/Drawables/Include/Text.h"
#include "Engine/Drawables/Include/Shape.h"
#include "Engine/Utilities/Include/Box.h"
#include "Engine/Include/Window.h"

namespace rave
{
	namespace gui
	{
		class Window
		{
		public:
			Window& Load(Graphics& gfx, rave::Window& wnd, const wchar_t* title, const Box& box);
			void Bind(Graphics& gfx, RenderTarget& target) const;

			void Update(Graphics& gfx, rave::Window& wnd);

		private:
			static constexpr FColor defaultbg = FColor({ .212f, .224f, .247f });
			static constexpr FColor defaultln = FColor({ .447f, .537f, .855f });
			static constexpr FColor defaulttc = FColor({ .184f, .192f, .212f });
			static constexpr float defaultFontSize = 1.0f / 25.0f;

			Vector2 mpos;
			Vector2 centre;
			Vector2 tboxcentre;

			Text title;
			Box box;

			Shape outline;
			Shape background;
			Shape titleBox;
		};
	}
}
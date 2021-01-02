#pragma once
#include "Engine/Graphics/Include/Graphics.h"
#include "Engine/Graphics/Include/RenderTarget.h"

namespace rave
{
	template<typename T>
	concept GuiConcept = requires(T t, Graphics& gfx, RenderTarget& target)
	{
		t.Bind(gfx, target);
	};
}
#pragma once
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	template<typename T>
	concept BindableConcept = requires(T t, Graphics gfx)
	{
		t.Bind(gfx);
	};
}
#pragma once
#include "Engine/Graphics/Include/Texture.h"
#include "Engine/Graphics/Include/ResourceView.h"

namespace rave
{
	class TextureView : public ResourceView
	{
	public:
		TextureView& Load(Graphics& gfx, const Texture& texture);
	};
}
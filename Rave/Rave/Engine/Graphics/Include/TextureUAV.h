#pragma once
#include "Engine/Graphics/Include/Texture.h"
#include "Engine/Graphics/Include/ResourceUAV.h"

namespace rave
{
	class TextureUAV : public ResourceUAV
	{
	public:
		TextureUAV& Load(Graphics& gfx, const Texture& texture);
		void Bind(Graphics& gfx);
	};
}
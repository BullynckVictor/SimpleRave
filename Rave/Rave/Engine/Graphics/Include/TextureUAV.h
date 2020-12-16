#pragma once
#include "Engine/Graphics/Include/Texture.h"
#include "Engine/Graphics/Include/ResourceUAV.h"

namespace rave
{
	class TextureUAV : public ResourceUAV
	{
	public:
		TextureUAV(Graphics& gfx, const Texture& texture);
		void Bind(Graphics& gfx);

	private:
		static D3D11_UNORDERED_ACCESS_VIEW_DESC GetDesc() noexcept;
	};
}
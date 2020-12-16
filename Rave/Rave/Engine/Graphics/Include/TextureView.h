#pragma once
#include "Engine/Graphics/Include/Texture.h"
#include "Engine/Graphics/Include/ResourceView.h"

namespace rave
{
	class TextureView : public ResourceView
	{
	public:
		TextureView(Graphics& gfx, const Texture& texture);
		void Bind(Graphics& gfx);

	private:
		static D3D11_SHADER_RESOURCE_VIEW_DESC GetDesc(const Texture& texture) noexcept;
	};
}
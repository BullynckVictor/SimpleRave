#pragma once
#include "Engine/Graphics/Include/Texture.h"

namespace rave
{
	class TextureView : public GraphicsFriend
	{
	public:
		TextureView(Graphics& gfx, const Texture& texture);
		void Bind(Graphics& gfx);

	private:
		ComPtr<ID3D11ShaderResourceView> pView;
	};
}
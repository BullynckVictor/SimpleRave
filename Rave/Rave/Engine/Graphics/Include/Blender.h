#pragma once
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	class Blender : public GraphicsFriend
	{
	public:
		Blender(Graphics& gfx, const bool blendAlpha);

		void SetAlpha(Graphics& gfx, const bool blendAlpha);
		void Bind(Graphics& gfx) const noexcept;

	private:
		ComPtr<ID3D11BlendState> pBlendState;
	};
}
#pragma once
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	class Sampler : public GraphicsFriend
	{
	public:
		Sampler(Graphics& gfx, const D3D11_FILTER filter);
		void Bind(Graphics& gfx);

	private:
		ComPtr<ID3D11SamplerState> pSamplerState;
	};
}
#pragma once
#include "Engine/Graphics/Include/Graphics.h"
#include "Engine/Graphics/Include/SwapChain.h"
#include "Engine/Utilities/Include/Color.h"

namespace rave
{
	class RenderTarget : GraphicsFriend
	{
	public:
		RenderTarget(Graphics& gfx, SwapChain& swap);

		void Bind(Graphics& gfx);
		void Clear(Graphics& gfx, const FColor& background);
		
	private:
		ComPtr<ID3D11RenderTargetView> pTarget;
	};
}
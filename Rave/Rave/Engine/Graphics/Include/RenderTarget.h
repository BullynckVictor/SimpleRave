#pragma once
#include "Engine/Graphics/Include/Graphics.h"
#include "Engine/Graphics/Include/SwapChain.h"
#include "Engine/Graphics/Include/Texture.h"
#include "Engine/Graphics/Include/DepthStencilBuffer.h"
#include "Engine/Utilities/Include/Vector.h"
#include "Engine/Include/TargetSize.h"

namespace rave
{
	class RenderTarget : GraphicsFriend
	{
	public:
		RenderTarget& Load(Graphics& gfx, Texture& texture);
		RenderTarget& Load(Graphics& gfx, SwapChain& swap);

		void Bind(Graphics& gfx);
		void Clear(Graphics& gfx, const FColor& background) noexcept;
		void EndDraw();

		unsigned int GetWidth()  const noexcept;
		unsigned int GetHeight() const noexcept;

		TargetSize GetTargetSize() const noexcept;
		
	private:
		DepthStencilBuffer depth;

		ComPtr<ID3D11RenderTargetView> pTarget;
		ComPtr<ID2D1RenderTarget>	   pD2DTarget;
		D3D11_VIEWPORT vp;

		friend class RenderTargetFriend;
	};


	class RenderTargetFriend
	{
	protected:
		static ComPtr<ID2D1RenderTarget>& GetD2DTarget(RenderTarget& target) noexcept;
		static D3D11_VIEWPORT const& GetViewPort(RenderTarget& target) noexcept;
	};
}
#pragma once
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	class DepthStencilBuffer : public GraphicsFriend
	{
	public:
		DepthStencilBuffer& Load(Graphics& gfx, const unsigned int width, const unsigned int height);

		ID3D11DepthStencilView* Bind(Graphics& gfx) const noexcept;
		void Clear(Graphics& gfx) const noexcept;

	private:
		ComPtr<ID3D11DepthStencilState> pState;
		ComPtr<ID3D11DepthStencilView> pView;
	};
}
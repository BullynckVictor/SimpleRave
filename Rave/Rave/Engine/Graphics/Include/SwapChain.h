#pragma once
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	class SwapChain : GraphicsFriend
	{
	public:
		SwapChain(Graphics& gfx, HWND hwnd, unsigned int width, unsigned int height);

		void Present() noexcept;

		void SetVSync(const bool vsync) noexcept;
		bool GetVSync() const noexcept;

	private:
		ComPtr<IDXGISwapChain> pSwap;
		unsigned int sync = 1;

		friend class RenderTarget;
	};
}
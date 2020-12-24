#include "Engine/Graphics/Include/SwapChain.h"

rave::SwapChain& rave::SwapChain::Load(Graphics& gfx, HWND hwnd, unsigned int width, unsigned int height)
{
	HRESULT hr;

	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;


	rave_check_hr(GetDXGIFactory(gfx)->CreateSwapChain(
		GetDevice(gfx).Get(),
		&sd,
		&pSwap
	));

	return *this;
}

void rave::SwapChain::Present()
{
	HRESULT hr;
	rave_check_hr( pSwap->Present(sync, 0) );
}

void rave::SwapChain::SetVSync(const bool vsync) noexcept
{
	sync = (vsync ? 1u : 0u);
}

bool rave::SwapChain::GetVSync() const noexcept
{
	return sync;
}

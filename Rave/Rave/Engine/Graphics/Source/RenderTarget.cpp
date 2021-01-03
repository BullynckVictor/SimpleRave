#include "Engine/Graphics/Include/RenderTarget.h"

rave::RenderTarget& rave::RenderTarget::Load(Graphics& gfx, Texture& texture)
{
	HRESULT hr;

	D3D11_RENDER_TARGET_VIEW_DESC desc{};
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D = D3D11_TEX2D_RTV{ 0 };

	rave_check_hr(GetDevice(gfx)->CreateRenderTargetView(texture.pTexture.Get(), &desc, &pTarget));

	D2D1_RENDER_TARGET_PROPERTIES props =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			96,
			96
		);

	ComPtr<IDXGISurface> pDXGIBackBuffer;
	rave_check_hr(texture.pTexture->QueryInterface(__uuidof(IDXGISurface), &pDXGIBackBuffer));

	rave_check_hr(GetD2DFactory(gfx)->CreateDxgiSurfaceRenderTarget(pDXGIBackBuffer.Get(), props, &pD2DTarget));

	DXGI_SURFACE_DESC sd;
	pDXGIBackBuffer->GetDesc(&sd);

	vp.Width = (float)sd.Width;
	vp.Height = (float)sd.Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	return *this;
}

rave::RenderTarget& rave::RenderTarget::Load(Graphics& gfx, SwapChain& swap)
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> pBackBuffer;
	rave_check_hr(swap.pSwap->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer));

	D3D11_RENDER_TARGET_VIEW_DESC desc{};
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D = D3D11_TEX2D_RTV{ 0 };

	rave_check_hr(GetDevice(gfx)->CreateRenderTargetView(pBackBuffer.Get(), &desc, &pTarget));

	D2D1_RENDER_TARGET_PROPERTIES props =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			96,
			96
		);

	ComPtr<IDXGISurface> pDXGIBackBuffer;
	rave_check_hr(swap.pSwap->GetBuffer(0, __uuidof(IDXGISurface), &pDXGIBackBuffer));

	rave_check_hr(GetD2DFactory(gfx)->CreateDxgiSurfaceRenderTarget(pDXGIBackBuffer.Get(), props, &pD2DTarget));

	DXGI_SURFACE_DESC sd;
	pDXGIBackBuffer->GetDesc(&sd);

	vp.Width = (float)sd.Width;
	vp.Height = (float)sd.Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;

	depth.Load(gfx, sd.Width, sd.Height);

	return *this;
}

void rave::RenderTarget::Bind(Graphics& gfx)
{
	ID3D11ShaderResourceView* pClearView = nullptr;

	GetContext(gfx)->VSSetShaderResources(0u, 1u, &pClearView);
	GetContext(gfx)->PSSetShaderResources(0u, 1u, &pClearView);

	GetContext(gfx)->OMSetRenderTargets(1u, pTarget.GetAddressOf(), depth.Bind(gfx));

	GetContext(gfx)->RSSetViewports(1u, &vp);

	targetSize = GetTargetSize();
}

void rave::RenderTarget::Clear(Graphics& gfx, const FColor& background) noexcept
{
	GetContext(gfx)->ClearRenderTargetView(pTarget.Get(), background.data.data());
	depth.Clear(gfx);
	pD2DTarget->BeginDraw();
}

void rave::RenderTarget::EndDraw()
{
	HRESULT hr;
	rave_check_hr(pD2DTarget->EndDraw());
}

unsigned int rave::RenderTarget::GetWidth() const noexcept
{
	return static_cast<unsigned int>(vp.Width);
}

unsigned int rave::RenderTarget::GetHeight() const noexcept
{
	return static_cast<unsigned int>(vp.Height);
}

rave::TargetSize rave::RenderTarget::GetTargetSize() const noexcept
{
	TargetSize ts;

	ts.pixel.view.x = GetWidth();
	ts.pixel.view.y = GetHeight();
	const float min = std::min(vp.Width, vp.Height);
	ts.relative.view.x = vp.Width / min;
	ts.relative.view.y = vp.Height / min;

	return ts;
}

rave::ComPtr<ID2D1RenderTarget>& rave::RenderTargetFriend::GetD2DTarget(RenderTarget& target) noexcept
{
	return target.pD2DTarget;
}

D3D11_VIEWPORT const& rave::RenderTargetFriend::GetViewPort(RenderTarget& target) noexcept
{
	return target.vp;
}

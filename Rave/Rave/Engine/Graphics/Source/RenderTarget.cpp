#include "Engine/Graphics/Include/RenderTarget.h"

rave::RenderTarget::RenderTarget(Graphics& gfx, SwapChain& swap)
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> pBackBuffer;
	rave_check_hr(swap.pSwap->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBuffer));

	D3D11_RENDER_TARGET_VIEW_DESC desc{};
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D = D3D11_TEX2D_RTV{ 0 };

	rave_check_hr(GetDevice(gfx)->CreateRenderTargetView(pBackBuffer.Get(), &desc, &pTarget));
}

void rave::RenderTarget::Bind(Graphics& gfx)
{
	ID3D11ShaderResourceView* pClearView = nullptr;

	GetContext(gfx)->VSGetShaderResources(0u, 1u, &pClearView);
	GetContext(gfx)->PSGetShaderResources(0u, 1u, &pClearView);

	GetContext(gfx)->OMSetRenderTargets(0u, pTarget.GetAddressOf(), NULL);
}

void rave::RenderTarget::Clear(Graphics& gfx, const FColor& background)
{
	GetContext(gfx)->ClearRenderTargetView(pTarget.Get(), background.Get());
}

#include "Engine/Graphics/Include/TextureUAV.h"

rave::TextureUAV::TextureUAV(Graphics& gfx, const Texture& texture)
	:
	ResourceUAV(gfx, texture, GetDesc())
{
}

void rave::TextureUAV::Bind(Graphics& gfx)
{
	GetContext(gfx)->CSSetUnorderedAccessViews(0, 1, pUAV.GetAddressOf(), NULL);
}

D3D11_UNORDERED_ACCESS_VIEW_DESC rave::TextureUAV::GetDesc() noexcept
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC descUAV;
	ZeroMemory(&descUAV, sizeof(descUAV));
	descUAV.Format = DXGI_FORMAT_UNKNOWN;
	descUAV.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	descUAV.Texture2D.MipSlice = 0;
	return descUAV;
}

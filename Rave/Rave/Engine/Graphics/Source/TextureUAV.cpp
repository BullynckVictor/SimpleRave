#include "Engine/Graphics/Include/TextureUAV.h"

rave::TextureUAV& rave::TextureUAV::Load(Graphics& gfx, const Texture& texture)
{
	D3D11_UNORDERED_ACCESS_VIEW_DESC descUAV;
	ZeroMemory(&descUAV, sizeof(descUAV));
	descUAV.Format = DXGI_FORMAT_UNKNOWN;
	descUAV.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	descUAV.Texture2D.MipSlice = 0;

	ResourceUAV::Load(gfx, texture, descUAV);

	return *this;
}

void rave::TextureUAV::Bind(Graphics& gfx)
{
	GetContext(gfx)->CSSetUnorderedAccessViews(0, 1, pUAV.GetAddressOf(), NULL);
}

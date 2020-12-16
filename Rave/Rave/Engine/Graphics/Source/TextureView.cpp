#include "Engine/Graphics/Include/TextureView.h"

rave::TextureView::TextureView(Graphics& gfx, const Texture& texture)
	:
	ResourceView(gfx, texture, GetDesc(texture))
{
}

void rave::TextureView::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pView.GetAddressOf());
}

D3D11_SHADER_RESOURCE_VIEW_DESC rave::TextureView::GetDesc(const Texture& texture) noexcept
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = texture.format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	return srvDesc;
}

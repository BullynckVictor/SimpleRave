#include "Engine/Graphics/Include/TextureView.h"

rave::TextureView& rave::TextureView::Load(Graphics& gfx, const Texture& texture)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = texture.GetFormat();
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	ResourceView::Load(gfx, texture, srvDesc);

	return *this;
}

void rave::TextureView::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pView.GetAddressOf());
}

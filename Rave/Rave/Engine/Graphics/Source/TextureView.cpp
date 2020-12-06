#include "Engine/Graphics/Include/TextureView.h"

rave::TextureView::TextureView(Graphics& gfx, const Texture& texture)
{
	HRESULT hr;

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = texture.format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	rave_check_hr(GetDevice(gfx)->CreateShaderResourceView(texture.pTexture.Get(), &srvDesc, &pView));
}

void rave::TextureView::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pView.GetAddressOf());
}
#include "Engine/Graphics/Include/DepthStencilBuffer.h"

rave::DepthStencilBuffer& rave::DepthStencilBuffer::Load(Graphics& gfx, const unsigned int width, const unsigned int height)
{
	HRESULT hr;

	// create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	rave_check_hr(GetDevice(gfx)->CreateDepthStencilState(&dsDesc, &pState));


	// create depth stensil texture
	ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	rave_check_hr(GetDevice(gfx)->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

	// create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	rave_check_hr(GetDevice(gfx)->CreateDepthStencilView(
		pDepthStencil.Get(), &descDSV, &pView
	));

	return *this;
}

ID3D11DepthStencilView* rave::DepthStencilBuffer::Bind(Graphics& gfx) const noexcept
{
	GetContext(gfx)->OMSetDepthStencilState(pState.Get(), 1u);
	return pView.Get();
}

void rave::DepthStencilBuffer::Clear(Graphics& gfx) const noexcept
{
	GetContext(gfx)->ClearDepthStencilView(pView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

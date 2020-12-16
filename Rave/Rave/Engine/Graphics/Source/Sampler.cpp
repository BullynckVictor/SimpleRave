#include "Engine/Graphics/Include/Sampler.h"

rave::Sampler& rave::Sampler::Load(Graphics& gfx, const D3D11_FILTER filter)
{
	HRESULT hr;

	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = filter;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[3] = 0;

	rave_check_hr( GetDevice(gfx)->CreateSamplerState(&desc, &pSamplerState) );

	return *this;
}

void rave::Sampler::Bind(Graphics& gfx)
{
	GetContext(gfx)->PSSetSamplers(0u, 1u, pSamplerState.GetAddressOf());
}

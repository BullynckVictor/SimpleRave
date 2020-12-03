#include "Engine/Graphics/Include/Graphics.h"

rave::Graphics::Graphics()
{
	HRESULT hr;

#ifndef NDEBUG
	static constexpr unsigned int createFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
#else
	static constexpr unsigned int createFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#endif
	
	rave_check_hr( D3D11CreateDevice(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		createFlags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&pDevice,
		NULL,
		&pContext
	));

	rave_check_hr(CreateDXGIFactory(__uuidof(IDXGIFactory), &pFactory));
}

rave::ComPtr<ID3D11Device>& rave::GraphicsFriend::GetDevice(Graphics& gfx) noexcept
{
	return gfx.pDevice;
}

rave::ComPtr<ID3D11DeviceContext>& rave::GraphicsFriend::GetContext(Graphics& gfx) noexcept
{
	return gfx.pContext;
}

rave::ComPtr<IDXGIFactory>& rave::GraphicsFriend::GetFactory(Graphics& gfx) noexcept
{
	return gfx.pFactory;
}

#include "Engine/Graphics/Include/Graphics.h"
#include "Engine/Utilities/Include/Exception.h"

rave::Graphics::Graphics()
{
#ifndef NDEBUG
	static constexpr unsigned int createFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
	static constexpr unsigned int createFlags = 0u;
#endif
	
	D3D11CreateDevice(
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
	);
}

void rave::Graphics::BeginDraw()
{
}

void rave::Graphics::EndDraw()
{
}

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

	//DirectWrite
	rave_check_hr(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(pDWFactory.ReleaseAndGetAddressOf())));

	// create the Direct2D factory
	D2D1_FACTORY_OPTIONS options{};
	options.debugLevel = D2D1_DEBUG_LEVEL_NONE;

	rave_check_hr(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory), &options, (void**)pD2DFactory.ReleaseAndGetAddressOf()));
}

void rave::Graphics::ClearInfoManager() noexcept
{
#ifndef NDEBUG
	infoManager.ClearQueue();
#endif
}

void rave::Graphics::CheckInfoManager()
{
#ifndef NDEBUG
	const auto messages = infoManager.GetNewMessages();
	if (!messages.empty())
	{
		std::string message;
		for (const auto s : messages)
			message += s + '\n';
		message.pop_back();
		rave_throw_message(Widen(message).c_str());
	}
#endif
}

rave::ComPtr<ID3D11Device>& rave::GraphicsFriend::GetDevice(Graphics& gfx) noexcept
{
	return gfx.pDevice;
}

rave::ComPtr<ID3D11DeviceContext>& rave::GraphicsFriend::GetContext(Graphics& gfx) noexcept
{
	return gfx.pContext;
}

rave::ComPtr<IDXGIFactory>& rave::GraphicsFriend::GetDXGIFactory(Graphics& gfx) noexcept
{
	return gfx.pFactory;
}

rave::ComPtr<ID2D1Factory>& rave::GraphicsFriend::GetD2DFactory(Graphics& gfx) noexcept
{
	return gfx.pD2DFactory;
}

rave::ComPtr<IDWriteFactory>& rave::GraphicsFriend::GetDWFactory(Graphics& gfx) noexcept
{
	return gfx.pDWFactory;
}
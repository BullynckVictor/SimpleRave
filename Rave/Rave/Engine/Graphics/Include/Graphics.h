#pragma once
#include "Engine/Graphics/Include/DirectX.h"
#include "Engine/Utilities/Include/Exception.h"
#include "Engine/Graphics/Include/InfoManager.h"

namespace rave
{
	class Graphics
	{
	public:
		Graphics();

		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;

		void ClearInfoManager() noexcept;
		void CheckInfoManager();

	private:
#ifndef NDEBUG
		DXInfoManager infoManager;
#endif

		ComPtr<ID3D11Device>		pDevice;
		ComPtr<ID3D11DeviceContext>	pContext;
		ComPtr<IDXGIFactory>		pFactory;

		ComPtr<ID2D1Factory>		pD2DFactory;
		ComPtr<IDWriteFactory>		pDWFactory;

		friend class GraphicsFriend;
	};

	class GraphicsFriend
	{
	protected:
		static ComPtr<ID3D11Device>&		GetDevice  (Graphics& gfx) noexcept;
		static ComPtr<ID3D11DeviceContext>&	GetContext (Graphics& gfx) noexcept;
		static ComPtr<IDXGIFactory>&		GetDXGIFactory (Graphics& gfx) noexcept;

		static ComPtr<ID2D1Factory>&		GetD2DFactory (Graphics& gfx) noexcept;
		static ComPtr<IDWriteFactory>&		GetDWFactory  (Graphics& gfx) noexcept;
	};
}
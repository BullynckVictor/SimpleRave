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

		friend class GraphicsFriend;
	};

	class GraphicsFriend
	{
	protected:
		static ComPtr<ID3D11Device>&		GetDevice  (Graphics& gfx) noexcept;
		static ComPtr<ID3D11DeviceContext>&	GetContext (Graphics& gfx) noexcept;
		static ComPtr<IDXGIFactory>&		GetFactory (Graphics& gfx) noexcept;
	};
}
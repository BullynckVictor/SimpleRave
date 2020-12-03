#pragma once
#include "Engine/Graphics/Include/DirectX.h"

namespace rave
{
	class Graphics
	{
	public:
		Graphics();

		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;

	private:
		ComPtr<ID3D11Device>		pDevice;
		ComPtr<ID3D11DeviceContext>	pContext;
	};
}
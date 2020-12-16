#pragma once
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	class PixelShader : public GraphicsFriend
	{
	public:
		PixelShader& Load(Graphics& gfx, const wchar_t* path);
		void Bind(Graphics& gfx) const noexcept;

	private:
		ComPtr<ID3D11PixelShader> pShader;
	};
}
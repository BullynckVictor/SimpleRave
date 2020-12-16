#pragma once
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	class VertexShader : public GraphicsFriend
	{
	public:
		VertexShader& Load(Graphics& gfx, const wchar_t* path);
		void Bind(Graphics& gfx) const noexcept;

	private:
		ComPtr<ID3D11VertexShader> pShader;
	};
}
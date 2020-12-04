#pragma once
#include "Engine/Graphics/Include/Graphics.h"
#include <vector>

namespace rave
{
	struct InputLayoutElement
	{
		InputLayoutElement(const char* semanticName, const DXGI_FORMAT format, const size_t byteSize);
		const std::string semanticName;
		const DXGI_FORMAT format;
		const size_t byteSize;
	};

	class InputLayout : public GraphicsFriend
	{
	public:
		InputLayout(Graphics& gfx, const wchar_t* path, const std::vector<InputLayoutElement>& elements);
		void Bind(Graphics& gfx) const noexcept;

	private:
		ComPtr<ID3D11InputLayout> pLayout;
	};
}
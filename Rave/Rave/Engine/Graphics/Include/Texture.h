#pragma once
#include "Engine/Graphics/Include/Graphics.h"
#include "Engine/Graphics/Include/ImageDecoder.h"

namespace rave
{
	class Texture : public GraphicsFriend
	{
	public:
		Texture(Graphics& gfx, const size_t width, const size_t height, const size_t byteWidth, const DXGI_FORMAT format, const void* pData, const bool shaderResource = true);
		Texture(Graphics& gfx, ImageDecoder& decoder, const size_t byteWidth, const DXGI_FORMAT format, const wchar_t* fileName, size_t* pWidth = nullptr, size_t* pHeight = nullptr, const bool shaderResource = true);
		const DXGI_FORMAT format;

	private:
		GUID GetWICFormat() const;
		ComPtr<ID3D11Texture2D> pTexture;

		friend class TextureView;
	};
}
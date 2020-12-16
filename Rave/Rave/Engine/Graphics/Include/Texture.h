#pragma once
#include "Engine/Graphics/Include/Resource.h"
#include "Engine/Graphics/Include/ImageDecoder.h"
#include "Engine/Utilities/Include/Flag.h"

namespace rave
{
	class Texture : public Resource
	{
	public:
		Texture& Load(Graphics& gfx, const size_t width, const size_t height, const size_t byteWidth, const DXGI_FORMAT format, const void* pData, const Flag<Texture> shaderResource = NewFlag<Texture>(0));
		Texture& Load(Graphics& gfx, ImageDecoder& decoder, const size_t byteWidth, const DXGI_FORMAT format, const wchar_t* fileName, size_t* pWidth = nullptr, size_t* pHeight = nullptr, const bool shaderResource = true);
		DXGI_FORMAT GetFormat() const noexcept;

	private:
		DXGI_FORMAT format;
		ID3D11Resource* GetResource() const noexcept override;
		GUID GetWICFormat() const;
		ComPtr<ID3D11Texture2D> pTexture;
	};

	static constexpr Flag<Texture> bindTextureView = NewFlag<Texture>(0);
	static constexpr Flag<Texture> bindTextureUAV  = NewFlag<Texture>(1);
}
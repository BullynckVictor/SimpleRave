#pragma once
#include "Engine/Graphics/Include/Resource.h"
#include "Engine/Graphics/Include/ImageDecoder.h"
#include "Engine/Utilities/Include/Flag.h"
#include "Engine/Utilities/Include/Vector2D.h"

namespace rave
{
	class Texture : public Resource
	{
	public:
		Texture& Load(Graphics& gfx, const size_t width, const size_t height, const size_t byteWidth, const DXGI_FORMAT format, const void* pData, const Flag<Resource> flags = bindResourceView);
		Texture& Load(Graphics& gfx, ImageDecoder& decoder, const size_t byteWidth, const DXGI_FORMAT format, const wchar_t* fileName, size_t* pWidth = nullptr, size_t* pHeight = nullptr, const bool shaderResource = true);
		DXGI_FORMAT GetFormat() const noexcept;

		void Save(Graphics& gfx, ImageDecoder& decoder, const wchar_t* filename, const size_t byteWidth = 4);
		template<typename T>
		std::vector<T> Read(Graphics& gfx, const size_t byteWidth = 4)
		{
			HRESULT hr;

			std::vector<T> out;

			D3D11_TEXTURE2D_DESC desc = {};
			pTexture->GetDesc(&desc);
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			desc.Usage = D3D11_USAGE_STAGING;
			desc.BindFlags = 0;
			desc.MiscFlags = 0;
			out.resize(desc.Width * desc.Height * byteWidth / sizeof T);

			ComPtr<ID3D11Texture2D> pDest;

			rave_check_hr(GetDevice(gfx)->CreateTexture2D(&desc, nullptr, &pDest));
			Resource::Read(gfx, pDest.Get(), pTexture.Get(), reinterpret_cast<BYTE*>(out.data()), out.size() * sizeof T, desc.Height);

			return out;
		}

		Size GetSize() const noexcept;

	private:
		DXGI_FORMAT format;
		ID3D11Resource* GetResource() const noexcept override;
		GUID GetWICFormat() const;
		ComPtr<ID3D11Texture2D> pTexture;

		friend class RenderTarget;
	};
}
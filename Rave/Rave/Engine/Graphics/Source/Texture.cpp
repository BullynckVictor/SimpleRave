#include "Engine/Graphics/Include/Texture.h"

rave::Texture::Texture(Graphics& gfx, const size_t width, const size_t height, const size_t byteWidth, const DXGI_FORMAT format, const void* pData, const bool shaderResource)
	:
	format(format)
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = (shaderResource ?  D3D11_BIND_SHADER_RESOURCE : D3D11_BIND_UNORDERED_ACCESS);
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sub;
	sub.pSysMem = pData;
	sub.SysMemPitch = width * byteWidth;

	ComPtr<ID3D11Texture2D> pTexture;
	rave_check_hr(GetDevice(gfx)->CreateTexture2D(&desc, &sub, &pTexture));
}

rave::Texture::Texture(Graphics& gfx, ImageDecoder& decoder, const size_t byteWidth, const DXGI_FORMAT format, const wchar_t* filename, size_t* pWidth, size_t* pHeight, const bool shaderResource)
	:
	format(format)
{
	HRESULT hr;

	UINT width, height;
	decoder.ReadImage(filename, width, height, GetWICFormat());
	std::vector<BYTE> pData(width * height * byteWidth);
	decoder.CopyPixels(pData.data(), width * height * 4, (width * 4));

	if (pWidth)
		*pWidth = width;
	if (pHeight)
		*pHeight = height;

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = (shaderResource ? D3D11_BIND_SHADER_RESOURCE : D3D11_BIND_UNORDERED_ACCESS);
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sub;
	sub.pSysMem = pData.data();
	sub.SysMemPitch = width * byteWidth;

	ComPtr<ID3D11Texture2D> pTexture;
	rave_check_hr(GetDevice(gfx)->CreateTexture2D(&desc, &sub, &pTexture));
}

GUID rave::Texture::GetWICFormat() const
{
	switch (format)
	{
	case (DXGI_FORMAT_R32G32B32A32_FLOAT):
		return GUID_WICPixelFormat128bppRGBAFloat;
		break;
	case (DXGI_FORMAT_R16G16B16A16_FLOAT):
		return GUID_WICPixelFormat64bppRGBAHalf;
		break;
	case (DXGI_FORMAT_R16G16B16A16_UNORM):
		return GUID_WICPixelFormat64bppRGBA;
		break;
	case (DXGI_FORMAT_R8G8B8A8_UNORM):
		return GUID_WICPixelFormat32bppRGBA;
		break;
	case (DXGI_FORMAT_B8G8R8A8_UNORM):
		return GUID_WICPixelFormat32bppBGRA;
		break;
	case (DXGI_FORMAT_B8G8R8X8_UNORM):
		return GUID_WICPixelFormat32bppBGR;
		break;
	case (DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM):
		return GUID_WICPixelFormat32bppRGBA1010102XR;
		break;
	case (DXGI_FORMAT_R10G10B10A2_UNORM):
		return GUID_WICPixelFormat32bppRGBA1010102;
		break;
	case (DXGI_FORMAT_R9G9B9E5_SHAREDEXP):
		return GUID_WICPixelFormat32bppRGBE;
		break;
	case (DXGI_FORMAT_B5G5R5A1_UNORM):
		return GUID_WICPixelFormat16bppBGRA5551;
		break;
	case (DXGI_FORMAT_B5G6R5_UNORM):
		return GUID_WICPixelFormat16bppBGR565;
		break;
	case (DXGI_FORMAT_R32_FLOAT):
		return GUID_WICPixelFormat32bppGrayFloat;
		break;
	case (DXGI_FORMAT_R16_FLOAT):
		return GUID_WICPixelFormat16bppGrayHalf;
		break;
	case (DXGI_FORMAT_R16_UNORM):
		return GUID_WICPixelFormat16bppGray;
		break;
	case (DXGI_FORMAT_R8_UNORM):
		return GUID_WICPixelFormat8bppGray;
		break;
	case (DXGI_FORMAT_A8_UNORM):
		return GUID_WICPixelFormat8bppAlpha;
		break;
	case (DXGI_FORMAT_R32G32B32_FLOAT):
		return GUID_WICPixelFormat96bppRGBFloat;
		break;
	default:
		std::wstringstream ss;
		ss << "Unimplemented DXGI_FORMAT: " << format;
		rave_throw_message(ss.str().c_str());
		break;
	}
}

rave::Texture rave::LoadTexture(Graphics& gfx, ImageDecoder& decoder, const wchar_t* fileName, size_t* pWidth, size_t* pHeight, const bool shaderResource)
{
	return Texture(gfx, decoder, 4, DXGI_FORMAT_R8G8B8A8_UNORM, fileName, pWidth, pHeight, shaderResource);
}

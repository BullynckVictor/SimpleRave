#pragma once
#include "Engine/Graphics/Include/DirectX.h"
#include <string_view>
#include <wincodec.h>

namespace rave
{
	class ImageDecoder
	{
	public:
		ImageDecoder();
		void ReadImage(const wchar_t* filename, UINT& width, UINT& height, const REFWICPixelFormatGUID format);
		void CopyPixels(void* pData, const UINT size, const UINT stride);

		void SaveImage(std::wstring_view filename, const UINT width, const UINT height, const UINT size, const UINT stride, WICPixelFormatGUID format, void* pData, const size_t nPaletteColors = 256, const bool useAlpha = true);

	private:
		ComPtr<IWICImagingFactory>	pFactory;
		ComPtr<IWICBitmapDecoder>	pDecoder;
		ComPtr<IWICFormatConverter> pConverter;
	};
}
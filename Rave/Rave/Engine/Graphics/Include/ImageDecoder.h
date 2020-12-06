#pragma once
#include "Engine/Graphics/Include/DirectX.h"
#include <wincodec.h>


namespace rave
{
	class ImageDecoder
	{
	public:
		ImageDecoder();
		void ReadImage(const wchar_t* filename, UINT& width, UINT& height, const REFWICPixelFormatGUID format);
		void CopyPixels(void* pData, const UINT size, const UINT stride);

	private:
		ComPtr<IWICImagingFactory>	pFactory;
		ComPtr<IWICBitmapDecoder>	pDecoder;
		ComPtr<IWICFormatConverter> pConverter;
	};
}
#include "Engine/Graphics/Include/ImageDecoder.h"
#include "Engine/Utilities/Include/Exception.h"

rave::ImageDecoder::ImageDecoder()
{
	HRESULT hr;

	rave_check_hr(CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pFactory)
	));
}

void rave::ImageDecoder::ReadImage(const wchar_t* filename, UINT& width, UINT& height, const REFWICPixelFormatGUID format)
{
	HRESULT hr;

	rave_check_hr(pFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	));

	ComPtr<IWICBitmapFrameDecode> pFrame;

	rave_check_hr(pDecoder->GetFrame(0, &pFrame));

	//convert
	rave_check_hr(pFactory->CreateFormatConverter(&pConverter));
	rave_check_hr(pConverter->Initialize(pFrame.Get(), format, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom));

	rave_check_hr(pFrame->GetSize(&width, &height));
}

void rave::ImageDecoder::CopyPixels(void* pData, const UINT size, const UINT stride)
{
	HRESULT hr;
	rave_check_hr( pConverter->CopyPixels(NULL, stride, size, (BYTE*)pData) );
}

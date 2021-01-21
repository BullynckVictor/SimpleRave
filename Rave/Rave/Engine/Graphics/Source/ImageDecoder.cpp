#include "Engine/Graphics/Include/ImageDecoder.h"
#include "Engine/Utilities/Include/Exception.h"
#include "Engine/Utilities/Include/String.h"

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

void rave::ImageDecoder::SaveImage(std::wstring_view filename, const UINT width, const UINT height, const UINT size, const UINT stride, WICPixelFormatGUID format, void* pData, const UINT nPaletteColors, const bool useAlpha)
{
	HRESULT hr;

	ComPtr<IWICStream> pStream;
	ComPtr<IWICBitmapEncoder> pEncoder;
	ComPtr<IWICBitmapFrameEncode> pFrame;
	ComPtr<IWICPalette> pPalette;
	ComPtr<IWICBitmap> pBitmap;

	GUID fileformat = GUID_NULL;

	size_t dotpos = filename.rfind(L'.');
	rave_assert_info(dotpos != filename.npos, L"Invalid file name");
	std::wstring_view formatstr = filename.substr(dotpos);

	switch (HashString(Narrow(formatstr.data())))
	{
		case HashString(".png"):  fileformat = GUID_ContainerFormatPng;	 break;
		case HashString(".gif"):  fileformat = GUID_ContainerFormatGif;	 break;
		case HashString(".bmp"):  fileformat = GUID_ContainerFormatBmp;	 break;
		case HashString(".ico"):  fileformat = GUID_ContainerFormatIco;	 break;
		case HashString(".jpg"):  fileformat = GUID_ContainerFormatJpeg; break;
		case HashString(".jpe"):  fileformat = GUID_ContainerFormatJpeg; break;
		case HashString(".jpeg"): fileformat = GUID_ContainerFormatJpeg; break;
		case HashString(".tiff"): fileformat = GUID_ContainerFormatTiff; break;
		case HashString(".tif"):  fileformat = GUID_ContainerFormatTiff; break;

		default: rave_throw_message(L"File format not recognised");
	}

	rave_check_hr( pFactory->CreatePalette(&pPalette) );

	rave_check_hr( pFactory->CreateBitmapFromMemory(width, height, format, stride, size, reinterpret_cast<BYTE*>(pData), &pBitmap) );
	rave_check_hr( pFactory->CreateStream(&pStream) );
	rave_check_hr( pFactory->CreateEncoder(fileformat, NULL, &pEncoder) );
	rave_check_hr( pPalette->InitializeFromBitmap(pBitmap.Get(), nPaletteColors, useAlpha) );
	rave_check_hr( pStream->InitializeFromFilename(filename.data(), GENERIC_WRITE) );
	rave_check_hr( pEncoder->Initialize(pStream.Get(), WICBitmapEncoderNoCache) );
	rave_check_hr( pEncoder->CreateNewFrame(&pFrame, NULL) );
	rave_check_hr( pFrame->Initialize(NULL) );
	rave_check_hr( pFrame->SetSize(width, height) );
	rave_check_hr( pFrame->SetPixelFormat(&format) );
	rave_check_hr( pBitmap->SetPalette(pPalette.Get()) );
	rave_check_hr( pFrame->WriteSource(pBitmap.Get(), nullptr) );
//	rave_check_hr( pFrame->WritePixels(height, stride, size, reinterpret_cast<BYTE*>(pData)) );
	rave_check_hr( pFrame->Commit() );
	rave_check_hr( pEncoder->Commit() );
}

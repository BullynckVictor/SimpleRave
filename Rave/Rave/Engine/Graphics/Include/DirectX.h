#pragma once
#include "Engine/Include/Windows.h"
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include <dwrite.h>
#include <d2d1.h>
#include <d2d1helper.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")
#pragma comment(lib,"dxgi.lib")

namespace rave
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	template<typename I>
	static void SafeRelease(ComPtr<I>& pInteface)
	{
		if (pInteface.Get())
			pInteface.ReleaseAndGetAddressOf();
	}

	template<typename I>
	static void SafeRelease(I*& pInteface)
	{
		if (pInteface)
			pInteface->Release();
		pInteface = nullptr;
	}
}
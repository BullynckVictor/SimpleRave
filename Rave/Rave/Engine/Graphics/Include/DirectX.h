#pragma once
#include "Engine/Include/Windows.h"
#include <d3d11.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

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
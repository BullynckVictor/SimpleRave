#pragma once
#include "Engine/Graphics/Include/ResourceView.h"
#include "Engine/Graphics/Include/ResourceUAV.h"

namespace rave
{
	class ComputeShader : public GraphicsFriend
	{
	public:
		ComputeShader(Graphics& gfx, const wchar_t* filename);
		void Run(Graphics& gfx, const std::vector<ResourceView>& views, const std::vector<ResourceUAV>& uavs, const UINT x, const UINT y, const UINT z);


	private:
		ComPtr<ID3D11ComputeShader> pShader;
	};
}
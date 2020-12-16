#include "Engine/Graphics/Include/ComputeShader.h"

rave::ComputeShader::ComputeShader(Graphics& gfx, const wchar_t* filename)
{
	HRESULT hr;

	ComPtr<ID3DBlob> pBlob;
	rave_check_hr(D3DReadFileToBlob(filename, &pBlob));
	rave_check_hr(GetDevice(gfx)->CreateComputeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pShader));
}

void rave::ComputeShader::Run(Graphics& gfx, const std::vector<ResourceView>& views, const std::vector<ResourceUAV>& uavs, const UINT x, const UINT y, const UINT z)
{
	gfx.ClearInfoManager();

	GetContext(gfx)->CSSetShader(pShader.Get(), NULL, 0u);

	std::vector<ID3D11ShaderResourceView*> rawViews;
	rawViews.reserve(views.size());
	for (size_t i = 0; i < views.size(); i++)
	{
		rawViews.emplace_back(views[i].pView.Get());
	}
	GetContext(gfx)->CSSetShaderResources(0u, views.size(), rawViews.data());

	std::vector<ID3D11UnorderedAccessView*> rawUAVs;
	rawUAVs.reserve(uavs.size());
	for (size_t i = 0; i < uavs.size(); i++)
	{
		rawUAVs.emplace_back(uavs[i].pUAV.Get());
	}
	GetContext(gfx)->CSSetUnorderedAccessViews(0u, uavs.size(), rawUAVs.data(), NULL);
	GetContext(gfx)->Dispatch(x, y, z);

	ID3D11UnorderedAccessView* nullUAV = nullptr;
	ID3D11ShaderResourceView* nullView = nullptr;

	GetContext(gfx)->CSSetShaderResources(0u, 1, &nullView);
	GetContext(gfx)->CSSetUnorderedAccessViews(0u, 1, &nullUAV, NULL);

	gfx.CheckInfoManager();
}
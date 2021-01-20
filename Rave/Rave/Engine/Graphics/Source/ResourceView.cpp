#include "Engine/Graphics/Include/ResourceView.h"

rave::ResourceView& rave::ResourceView::Load(Graphics& gfx, const Resource& resource, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc)
{
	HRESULT hr;
	rave_check_hr(GetDevice(gfx)->CreateShaderResourceView(resource.GetResource(), &srvDesc, &pView));
	return *this;
}

void rave::ResourceView::Bind(Graphics& gfx, const ShaderType& shader) const noexcept
{
	switch (shader)
	{
	case ShaderType::Pixel:
		GetContext(gfx)->PSSetShaderResources(0u, 1u, pView.GetAddressOf());
		break;
	case ShaderType::Vertex:
		GetContext(gfx)->VSSetShaderResources(0u, 1u, pView.GetAddressOf());
		break;
	case ShaderType::Compute:
		GetContext(gfx)->CSSetShaderResources(0u, 1u, pView.GetAddressOf());
		break;
	}
}

#include "Engine/Graphics/Include/ResourceView.h"

rave::ResourceView::ResourceView(Graphics& gfx, const Resource& resource, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc)
{
	HRESULT hr;
	rave_check_hr(GetDevice(gfx)->CreateShaderResourceView(resource.GetResource(), &srvDesc, &pView));
}
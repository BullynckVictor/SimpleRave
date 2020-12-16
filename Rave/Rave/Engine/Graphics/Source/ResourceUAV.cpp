#include "Engine/Graphics/Include/ResourceUAV.h"

rave::ResourceUAV& rave::ResourceUAV::Load(Graphics& gfx, const Resource& resource, const D3D11_UNORDERED_ACCESS_VIEW_DESC& desc)
{
	HRESULT hr;
	rave_check_hr( GetDevice(gfx)->CreateUnorderedAccessView(resource.GetResource(), &desc, pUAV.GetAddressOf()) );

	return *this;
}
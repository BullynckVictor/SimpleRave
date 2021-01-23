#include "Engine/Graphics/Include/Resource.h"

void rave::Resource::Read(Graphics& gfx, ID3D11Resource* pDestResource, ID3D11Resource* pSourceResource, BYTE* pData, const uint32_t size, const uint32_t nRows)
{
	HRESULT hr;

	GetContext(gfx)->CopyResource(pDestResource, pSourceResource);
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	rave_check_hr(GetContext(gfx)->Map(pDestResource, 0u, D3D11_MAP_READ, 0u, &mappedResource));
	const BYTE const* pSource = reinterpret_cast<BYTE*>(mappedResource.pData);
	const size_t width = size / nRows;
	for(size_t i = 0; i < nRows; i++)
		memcpy(&pData[i * width], &pSource[i * mappedResource.RowPitch], width);
	GetContext(gfx)->Unmap(pDestResource, 0u);
}

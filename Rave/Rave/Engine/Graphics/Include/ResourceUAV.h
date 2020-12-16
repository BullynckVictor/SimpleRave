#pragma once
#include "Engine/Graphics/Include/Resource.h"

namespace rave
{
	class ResourceUAV : public GraphicsFriend
	{
	public:
		ResourceUAV(Graphics& gfx, const Resource& resource, const D3D11_UNORDERED_ACCESS_VIEW_DESC& desc);
		virtual ~ResourceUAV() {}

	protected:
		ComPtr<ID3D11UnorderedAccessView> pUAV;

		friend class ComputeShader;
	};
}
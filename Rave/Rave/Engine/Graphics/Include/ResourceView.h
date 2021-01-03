#pragma once
#include "Engine/Graphics/Include/Resource.h"
#include "Engine/Graphics/Include/Shader.h"

namespace rave
{
	class ResourceView : public GraphicsFriend
	{
	public:
		ResourceView& Load(Graphics& gfx, const Resource& resource, const D3D11_SHADER_RESOURCE_VIEW_DESC& srvDesc);
		virtual ~ResourceView() {}
		void Bind(Graphics& gfx, const ShaderType& shader = ShaderType::Pixel) const noexcept;

	protected:
		ComPtr<ID3D11ShaderResourceView> pView;
		friend class ComputeShader;
	};
}
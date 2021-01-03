#pragma once
#include "Engine/Graphics/Include/Buffer.h"
#include "Engine/Graphics/Include/ResourceView.h"
#include "Engine/Graphics/Include/Shader.h"

namespace rave
{
	class BufferView : public ResourceView
	{
	public:
		template<typename T>
		BufferView& Load(Graphics& gfx, const std::vector<T>& data, const DXGI_FORMAT& format, const bool writeAccess = false)
		{
			Buffer buffer;
			buffer.Load(gfx, writeAccess, D3D11_BIND_SHADER_RESOURCE, data);
			
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = format;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = data.size();

			ResourceView::Load(gfx, buffer, srvDesc);

			return *this;
		}
	};
}
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
		BufferView& Load(Graphics& gfx, const std::vector<T>& data, const DXGI_FORMAT& format, const bool writeAccess = false, const bool structured = false)
		{
			Buffer buffer;
			buffer.Load(gfx, writeAccess, D3D11_BIND_SHADER_RESOURCE, data, structured);
			
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = format;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = data.size();

			ResourceView::Load(gfx, buffer, srvDesc);

			return *this;
		}

		Buffer GetResource()
		{
			Buffer buffer;
			ComPtr<ID3D11Resource> pBuffer;
			pView->GetResource(&pBuffer);
			rave_assert_info(pView, L"Failed to get resource!");
			buffer.pBuffer = dynamic_cast<ID3D11Buffer*>(pBuffer.Get());
			return buffer;
		}
	};
}
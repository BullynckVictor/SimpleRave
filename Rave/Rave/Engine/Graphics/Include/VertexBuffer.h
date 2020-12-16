#pragma once
#include "Engine/Graphics/Include/Buffer.h"
#include <vector>

namespace rave
{
	template<typename V>
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer& Load(Graphics& gfx, const std::vector<V>& vertices, const bool writeAccess = false)
		{
			Buffer::Load(gfx, writeAccess, D3D11_BIND_VERTEX_BUFFER, sizeof(V) * vertices.size(), sizeof(V), vertices.data());
			return *this;
		}
		void Write(Graphics& gfx, const std::vector<V>& vertices)
		{
			Buffer::Write(gfx, sizeof(V) * vertices.size(), 0u, sizeof(V) * vertices.size(), vertices.data());
		}

		void Bind(Graphics& gfx) const noexcept
		{
			UINT stride = sizeof(V);
			UINT offset = 0u;
			GetContext(gfx)->IASetVertexBuffers(0u, 1u, pBuffer.GetAddressOf(), &stride, &offset);
		}
	};
}
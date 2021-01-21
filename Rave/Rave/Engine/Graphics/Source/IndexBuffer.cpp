#include "Engine/Graphics/Include/IndexBuffer.h"

rave::IndexBuffer& rave::IndexBuffer::Load(Graphics& gfx, const std::vector<uint32_t>& vertices, const bool writeAccess)
{
	Buffer::Load(gfx, writeAccess, D3D11_BIND_INDEX_BUFFER, sizeof(size_t) * (uint32_t)vertices.size(), sizeof(uint32_t), vertices.data());

	return *this;
}


void rave::IndexBuffer::Write(Graphics& gfx, const std::vector<uint32_t>& vertices)
{
	Buffer::Write(gfx, sizeof(uint32_t) * (uint32_t)vertices.size(), 0u, sizeof(uint32_t) * (uint32_t)vertices.size(), vertices.data());
}

void rave::IndexBuffer::Bind(Graphics& gfx) const noexcept
{
	GetContext(gfx)->IASetIndexBuffer(pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
#include "Engine/Graphics/Include/IndexBuffer.h"

rave::IndexBuffer::IndexBuffer(Graphics& gfx, const std::vector<size_t>& vertices, const bool writeAccess)
	:
	Buffer(gfx, writeAccess, D3D11_BIND_INDEX_BUFFER, sizeof(size_t)* vertices.size(), sizeof(size_t), vertices.data())
{}


void rave::IndexBuffer::Write(Graphics& gfx, const std::vector<size_t>& vertices)
{
	Buffer::Write(gfx, sizeof(size_t) * vertices.size(), 0u, sizeof(size_t) * vertices.size(), vertices.data());
}

void rave::IndexBuffer::Bind(Graphics& gfx) const noexcept
{
	GetContext(gfx)->IASetIndexBuffer(pBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}
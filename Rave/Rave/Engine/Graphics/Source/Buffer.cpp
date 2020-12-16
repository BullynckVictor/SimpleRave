#include "Engine/Graphics/Include/Buffer.h"

rave::Buffer::Buffer(Graphics& gfx, const bool writeAccess, const D3D11_BIND_FLAG bindFlag, const size_t byteWidth, const size_t stride, const void* const data)
	:
	writeAccess(writeAccess)
{
	HRESULT hr;

	if(bindFlag == D3D11_BIND_CONSTANT_BUFFER)
		rave_assert_info(!(byteWidth % 16), L"Constant buffers must have a byte size which is a multiple of 16");

	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = bindFlag;
	if (writeAccess)
	{
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
	}
	bd.MiscFlags = 0u;
	bd.ByteWidth = byteWidth;
	bd.StructureByteStride = stride;
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = data;
	rave_check_hr(GetDevice(gfx)->CreateBuffer(&bd, &sd, &pBuffer));
}

void rave::Buffer::Write(Graphics& gfx, const size_t rowPitch, const size_t depthPitch, const size_t size, const void* const data)
{
	rave_assert_info(writeAccess, L"Buffer must have writeAccess in order to write to it.\nThis value can be changed in the constructor");
	HRESULT hr;

	D3D11_MAPPED_SUBRESOURCE sd;
	sd.DepthPitch = depthPitch;
	sd.RowPitch = rowPitch;
	rave_check_hr(GetContext(gfx)->Map(pBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sd));
	memcpy(sd.pData, data, size);
	GetContext(gfx)->Unmap(pBuffer.Get(), 0u);
}

ID3D11Resource* rave::Buffer::GetResource() const noexcept
{
	return pBuffer.Get();
}

bool rave::Buffer::HasWriteAccess() const noexcept
{
	return writeAccess;
}

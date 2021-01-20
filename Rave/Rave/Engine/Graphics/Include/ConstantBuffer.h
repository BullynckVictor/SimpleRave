#pragma once
#include "Engine/Graphics/Include/Buffer.h"
#include <vector>

namespace rave
{
	template<typename T>
	class ConstantBuffer : public Buffer
	{
	public:
		ConstantBuffer& Load(Graphics& gfx, const T& value, const bool writeAccess = false)
		{
			if constexpr (bool(sizeof(T) % 16))
			{
				static constexpr size_t size = (sizeof(T) / 16 + 1) * 16;
				std::vector<unsigned char> data(size);
				memcpy(data.data(), &value, sizeof(T));
				Buffer::Load(gfx, writeAccess, D3D11_BIND_CONSTANT_BUFFER, size, 0, &value);
			}
			else
			{
				Buffer::Load(gfx, writeAccess, D3D11_BIND_CONSTANT_BUFFER, sizeof(T), 0, &value);
			}
			return *this;
		}

		void Write(Graphics& gfx, const T& value)
		{
			if constexpr (sizeof (T) % 16)
			{
				static constexpr size_t size = (sizeof(T) / 16 + 1) * 16;
				std::vector<unsigned char> data(size);
				memcpy(data.data(), &value, size);
				Buffer::Write(gfx, 0, 0, size, &data.data());
			}
			else
			{
				Buffer::Write(gfx, 0, 0, sizeof T, &value);
			}
		}

		void BindToPixelShader(Graphics& gfx) const noexcept
		{
			GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pBuffer.GetAddressOf());
		}

		void BindToVertexShader(Graphics& gfx) const noexcept
		{
			GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pBuffer.GetAddressOf());
		}

		void BindToComputeShader(Graphics& gfx) const noexcept
		{
			GetContext(gfx)->CSSetConstantBuffers(0u, 1u, pBuffer.GetAddressOf());
		}
	};
}
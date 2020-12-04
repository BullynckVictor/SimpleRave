#pragma once
#include "Engine/Graphics/Include/Buffer.h"
#include <vector>

namespace rave
{
	template<typename T>
	class ConstantBuffer : public Buffer
	{
	public:
		ConstantBuffer(Graphics& gfx, const T& value, const bool writeAccess = false)
			:
			Buffer(CreateBuffer(gfx, value, writeAccess))
		{}

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
			GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pBuffer.Get());
		}

		void BindToVertexShader(Graphics& gfx) const noexcept
		{
			GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pBuffer.Get());
		}

	private:
		static Buffer CreateBuffer(Graphics& gfx, const T& value, const bool writeAccess)
		{
			if constexpr (sizeof(T) % 16)
			{
				static constexpr size_t size = (sizeof(T) / 16 + 1) * 16;
				std::vector<unsigned char> data(size);
				memcpy(data.data(), &value, sizeof (T));
				return Buffer(gfx, writeAccess, D3D11_BIND_CONSTANT_BUFFER, size, 0, &value)
			}
			else
			{
				return Buffer(gfx, writeAccess, D3D11_BIND_CONSTANT_BUFFER, sizeof(T), 0, &value)
			}
		}
	};
}
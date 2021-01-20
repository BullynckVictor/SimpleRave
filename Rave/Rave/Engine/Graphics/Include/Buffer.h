#pragma once
#include "Engine/Graphics/Include/Resource.h"

namespace rave
{
	class Buffer : public Resource
	{
	public:
		virtual ~Buffer() {}
		template<typename C>
		Buffer& Load(Graphics& gfx, const bool writeAccess, const D3D11_BIND_FLAG bindFlag, const C& container, const bool structured)
		{
			return Load(gfx, writeAccess, bindFlag, sizeof(typename C::value_type) * container.size(), sizeof(typename C::value_type), container.data(), structured);
		}
		Buffer& Load(Graphics& gfx, const bool writeAccess, const D3D11_BIND_FLAG bindFlag, const size_t byteWidth, const size_t stride, const void* const data, const bool structured = false);
		bool HasWriteAccess() const noexcept;

		template<typename T>
		std::vector<T> Read(Graphics& gfx)
		{
			HRESULT hr;

			std::vector<T> out;

			D3D11_BUFFER_DESC desc = {};
			pBuffer->GetDesc(&desc);
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			desc.Usage = D3D11_USAGE_STAGING;
			desc.BindFlags = 0;
			desc.MiscFlags = 0;
			out.resize(desc.ByteWidth / sizeof(T));

			ComPtr<ID3D11Buffer> pDest;

			rave_check_hr(GetDevice(gfx)->CreateBuffer(&desc, nullptr, &pDest));
			Resource::Read(gfx, pDest.Get(), pBuffer.Get(), reinterpret_cast<BYTE*>(out.data()), out.size() * sizeof(T), 1);

			return out;
		}


		template<typename C>
		void Write(Graphics& gfx, const C& container)
		{
			Write(gfx, container.size() * sizeof(typename C::value_type), container.size() * sizeof(typename C::value_type), container.size(), container.data());
		}

	protected:
		void Write(Graphics& gfx, const size_t rowPitch, const size_t depthPitch, const size_t size, const void* const data);

	protected:
		ComPtr<ID3D11Buffer> pBuffer;

	private:
		ID3D11Resource* GetResource() const noexcept override;
		bool writeAccess;

		friend class BufferView;
	};
}
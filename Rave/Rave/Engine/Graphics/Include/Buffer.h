#pragma once
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	class Buffer : public GraphicsFriend
	{
	public:
		virtual ~Buffer() {}
		bool HasWriteAccess() const noexcept;

	protected:
		Buffer(Graphics& gfx, const bool writeAccess, const D3D11_BIND_FLAG bindFlag, const size_t byteWidth, const size_t stride, const void* const data);
		void Write(Graphics& gfx, const size_t rowPitch, const size_t depthPitch, const size_t size, const void* const data);

	protected:
		ComPtr<ID3D11Buffer> pBuffer;

	private:
		const bool writeAccess;
	};
}
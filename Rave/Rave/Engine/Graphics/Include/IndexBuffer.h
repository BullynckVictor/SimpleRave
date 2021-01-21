#pragma once
#include "Engine/Graphics/Include/Buffer.h"
#include <vector>

namespace rave
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer& Load(Graphics& gfx, const std::vector<uint32_t>& vertices, const bool writeAccess = false);

		void Write(Graphics& gfx, const std::vector<uint32_t>& vertices);

		void Bind(Graphics& gfx) const noexcept;
	};
}
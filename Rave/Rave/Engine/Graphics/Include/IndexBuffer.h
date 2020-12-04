#pragma once
#include "Engine/Graphics/Include/Buffer.h"
#include <vector>

namespace rave
{
	class IndexBuffer : public Buffer
	{
		IndexBuffer(Graphics& gfx, const std::vector<size_t>& vertices, const bool writeAccess = false);

		void Write(Graphics& gfx, const std::vector<size_t>& vertices);

		void Bind(Graphics& gfx) const noexcept;
	};
}
#pragma once
#include "Engine/Graphics/Include/Graphics.h"

namespace rave
{
	class Resource : public GraphicsFriend
	{
	public:
		virtual ~Resource() {}

	protected:
		virtual ID3D11Resource* GetResource() const noexcept = 0;
		friend class ResourceView;
		friend class ResourceUAV;
	};
}
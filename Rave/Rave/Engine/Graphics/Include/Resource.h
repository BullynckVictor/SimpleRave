#pragma once
#include "Engine/Graphics/Include/Graphics.h"
#include "Engine/Utilities/Include/Flag.h"
#include <vector>

namespace rave
{
	class Resource : public GraphicsFriend
	{
	public:
		virtual ~Resource() {}

	protected:
		static void Read(Graphics& gfx, ID3D11Resource* pDestResource, ID3D11Resource* pSourceResource, BYTE* pData, const size_t size, const size_t nRows);

		virtual ID3D11Resource* GetResource() const noexcept = 0;
		friend class ResourceView;
		friend class ResourceUAV;
	};

	static constexpr Flag<Resource> bindResourceView = NewFlag<Resource>(0);
	static constexpr Flag<Resource> bindResourceUAV  = NewFlag<Resource>(1);
	static constexpr Flag<Resource> bindResourceRT   = NewFlag<Resource>(2);
	static constexpr Flag<Resource> readResource	 = NewFlag<Resource>(3);
	static constexpr Flag<Resource> writeResource	 = NewFlag<Resource>(4);
}
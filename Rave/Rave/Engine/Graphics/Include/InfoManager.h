#pragma once
#include "Engine/Graphics/Include/DirectX.h"
#include <dxgidebug.h>

#include <vector>
#include <string>

namespace rave
{
	class DXInfoManager
	{
	public:
		DXInfoManager();
		void ClearQueue() noexcept;
		const std::vector<std::string> GetNewMessages();

	private:
		unsigned long long index = 0;
		ComPtr<IDXGIInfoQueue> pInfoQueue;
	};
}
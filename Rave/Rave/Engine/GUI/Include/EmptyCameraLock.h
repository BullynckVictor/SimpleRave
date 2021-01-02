#pragma once
#include "Engine/Include/Transform.h"

namespace rave
{
	class EmptyCameraLock
	{
	public:
		EmptyCameraLock();
		~EmptyCameraLock();

	private:
		Camera empty;
		Camera* pPrev;
	};
}
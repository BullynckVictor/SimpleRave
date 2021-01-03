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
		Camera2 empty;
		Camera2* pPrev;
	};
}
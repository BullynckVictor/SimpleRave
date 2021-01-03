#pragma once
#include "Engine/Utilities/Include/Vector.h"

namespace rave
{
	struct TargetSize
	{
		Size	pixel;
		Vector2	relative;
	};

	extern TargetSize targetSize;
}
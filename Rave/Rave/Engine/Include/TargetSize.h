#pragma once
#include "Engine/Utilities/Include/Vector2D.h"

namespace rave
{
	struct TargetSize
	{
		Size	pixel;
		Vector2	relative;
	};

	extern TargetSize targetSize;
}
#pragma once
#include "Engine/Utilities/Include/Vector.h"

namespace rave
{
	struct WideMaterial
	{
		FColor diffuse;
		FColor specular;
		float  specularPower;
		Padding<12> padding;
	};

	struct Material
	{
		Color diffuse;
		Color specular;
		float specularPower;

		WideMaterial Widen() const noexcept
		{
			return {
				ConvertColor(diffuse),
				ConvertColor(specular),
				specularPower
			};
		}
	};
}
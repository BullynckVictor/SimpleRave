#pragma once
#include "Engine/Utilities/Include/Vector.h"

namespace rave
{
	struct WideMaterial
	{
		FColor diffuse;
		FColor specular;
		float  specularIntensity;
		float  specularPower;
		Padding<8> padding;
	};

	struct Material
	{
		Color diffuse;
		Color specular;
		float specularIntensity;
		float specularPower;

		WideMaterial Widen() const noexcept
		{
			return {
				ConvertColor(diffuse),
				ConvertColor(specular),
				specularIntensity,
				specularPower
			};
		}
	};
}
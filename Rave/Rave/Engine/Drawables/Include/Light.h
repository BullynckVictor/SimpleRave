#pragma once
#include "Engine/Utilities/Include/Vector.h"
#include "Engine/Graphics/Include/BufferView.h"
#include <vector>

namespace rave
{
	struct Light
	{
		enum class Type
		{
			Point = 0,
			Spot,
			Directional
		};

		struct Attenuation
		{
			Attenuation() = default;
			Attenuation(const float constant, const float linear, const float quadratic);
			Attenuation(const float range);

			float constant;
			float linear;
			float quadratic;
		};

		FColor		color		= {};
		Vector3		position	= {};
		Type		type		= {};
		Vector3		direction	= {};
		Attenuation attenuation	= {};
		float		spotAngle	= {};
		Padding<4>	padding		= {};
	};

	class LightBuffer
	{
	public:
		std::vector<Light> lights;

		void Load (Graphics& gfx, const bool write = false);
		void Bind (Graphics& gfx);
		void Write(Graphics& gfx);

	private:
		BufferView buffer;
	};
}
#pragma once
#include "Engine/Graphics/Include/DirectX.h"
#include "Engine/Utilities/Include/Vector2D.h"

namespace rave
{
	static constexpr long double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

	constexpr float Radian(const float degree) noexcept { return degree / 180.0f * (float)pi; }
	constexpr float Degree(const float radian) noexcept { return radian * 180.0f / (float)pi; }

	typedef DirectX::XMMATRIX Matrix;

	struct Camera
	{
		float zoom = 1;
		float rotation = 0;
		Vector2 position = { 0, 0 };
		Vector2 size = { 1, 1 };
	};

	class Transform
	{
	public:
		Transform() noexcept;
		Transform(const Vector2& pos, const Vector2& scale, const float rotation) noexcept;

		Matrix& Concatonate() noexcept;

		Vector2 position;
		Vector2 scale;
		float rotation;
		
		Matrix viewMatrix;

		static Camera camera;
	};
}
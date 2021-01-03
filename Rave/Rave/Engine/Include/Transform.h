#pragma once
#include "Engine/Graphics/Include/DirectX.h"
#include "Engine/Utilities/Include/Vector.h"
#include "Engine/Include/TargetSize.h"

namespace rave
{
	static constexpr long double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

	constexpr float Radian(const float degree) noexcept { return degree / 180.0f * (float)pi; }
	constexpr float Degree(const float radian) noexcept { return radian * 180.0f / (float)pi; }

	typedef DirectX::XMMATRIX Matrix;

	struct Camera2
	{
		float zoom = 1;
		float rotation = 0;
		Vector2 position = { 0, 0 };
	};

	class Transform2
	{
	public:
		Transform2() noexcept;
		Transform2(const Matrix& matrix) noexcept;
		Transform2(const Vector2& pos, const Vector2& scale, const float rotation) noexcept;

		Matrix& Concatonate() noexcept;

		void TransformPoint(Vector2& point) const noexcept;
		Vector2 GetTransformedPoint(Vector2 point) const noexcept;

		void TransformPointView(Vector2& point) noexcept;
		Vector2 GetTransformedPointView(Vector2 point) noexcept;

		Vector2 position;
		Vector2 scale;
		float rotation;
		
		Matrix viewMatrix;
		Matrix worldMatrix;

		static Camera2* pCamera;
	};

	struct Camera3
	{
		Camera3() noexcept;
		Camera3(const Vector3& pos, const Vector3& rot, const float n = 0.5f, const float f = 10.0f) noexcept;

		Matrix& Concatonate() noexcept;

		Vector3 position;
		Vector3 rotation;

		float nearPlane;
		float farPlane;

		Matrix matrix;
	};

	class Transform3
	{
	public:
		Transform3() noexcept;
		Transform3(const Vector3& pos, const Vector3& scale, const Vector3& rotation) noexcept;

		Matrix& Concatonate() noexcept;

		void	TransformPoint(Vector3& point) const noexcept;
		Vector3	GetTransformedPoint(Vector3 point) const noexcept;

		Vector3 position;
		Vector3 scale;
		Vector3 rotation;

		Matrix viewMatrix;
		Matrix worldMatrix;

		static Camera3* pCamera;
	};
}
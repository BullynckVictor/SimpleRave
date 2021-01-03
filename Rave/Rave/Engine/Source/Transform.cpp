#include "Engine/Include/Transform.h"

rave::Camera2* rave::Transform2::pCamera = nullptr;
rave::Camera3* rave::Transform3::pCamera = nullptr;

rave::Transform2::Transform2() noexcept
	:
	position(0),
	scale(1),
	rotation(0)
{
	Concatonate();
}

rave::Transform2::Transform2(const Vector2& pos, const Vector2& scale, const float rotation) noexcept
	:
	position(pos),
	scale(scale),
	rotation(rotation)
{
	Concatonate();
}

rave::Transform2::Transform2(const Matrix& matrix) noexcept
	:
	rotation(),
	scale(),
	position(),
	viewMatrix(matrix),
	worldMatrix()
{
}

rave::Matrix& rave::Transform2::Concatonate() noexcept
{
	viewMatrix = DirectX::XMMatrixTranspose(
		  DirectX::XMMatrixScaling(scale.view.x, scale.view.y, 1)
		* DirectX::XMMatrixRotationZ(rotation)
		* DirectX::XMMatrixTranslation((position.view.x - pCamera->position.view.x), (position.view.y - pCamera->position.view.y), 0)
		* DirectX::XMMatrixRotationZ(-pCamera->rotation)
		* DirectX::XMMatrixTranslation(-(position.view.x - pCamera->position.view.x), -(position.view.y - pCamera->position.view.y), 0)
		* DirectX::XMMatrixTranslation((position.view.x - pCamera->position.view.x), (position.view.y - pCamera->position.view.y), 0)
		* DirectX::XMMatrixScaling(1 / (targetSize.relative.view.x * pCamera->zoom), 1 / (targetSize.relative.view.y * pCamera->zoom), 1)
	);
	worldMatrix = DirectX::XMMatrixTranspose(
		  DirectX::XMMatrixRotationZ(rotation)
		* DirectX::XMMatrixScaling(scale.view.x, scale.view.y, 1)
		* DirectX::XMMatrixTranslation(position.view.x, position.view.y, 0)
	);

	return viewMatrix;
}

void rave::Transform2::TransformPoint(Vector2& point) const noexcept
{
	DirectX::XMFLOAT2 f;
	f.x = point.view.x;
	f.y = point.view.y;
	DirectX::XMVECTOR vec = DirectX::XMLoadFloat2(&f);
	vec = DirectX::XMVector2Transform(vec, worldMatrix);
	point.view.x = DirectX::XMVectorGetX(vec);
	point.view.y = DirectX::XMVectorGetY(vec);
}

rave::Vector2 rave::Transform2::GetTransformedPoint(Vector2 point) const noexcept
{
	TransformPoint(point);
	return point;
}

void rave::Transform2::TransformPointView(Vector2& point) noexcept
{
	DirectX::XMFLOAT2 f;
	f.x = point.view.x;
	f.y = point.view.y;
	DirectX::XMVECTOR vec = DirectX::XMLoadFloat2(&f);
	vec = DirectX::XMVector2Transform(vec, viewMatrix);
	point.view.x = DirectX::XMVectorGetX(vec);
	point.view.y = DirectX::XMVectorGetY(vec);
}

rave::Vector2 rave::Transform2::GetTransformedPointView(Vector2 point) noexcept
{
	TransformPointView(point);
	return point;
}

rave::Transform3::Transform3() noexcept
	:
	position(0),
	scale(1),
	rotation(0),
	viewMatrix(),
	worldMatrix()
{
}

rave::Transform3::Transform3(const Vector3& pos, const Vector3& scale, const Vector3& rotation) noexcept
	:
	position(pos),
	scale(scale),
	rotation(rotation),
	viewMatrix(),
	worldMatrix()
{
	Concatonate();
}

rave::Matrix& rave::Transform3::Concatonate() noexcept
{
	Vector2 r = targetSize.relative / std::max(targetSize.relative.view.width, targetSize.relative.view.height);
	Matrix twm =
		  DirectX::XMMatrixScaling(scale.view.x, scale.view.y, scale.view.z)
		* DirectX::XMMatrixRotationRollPitchYaw(rotation.view.x, rotation.view.y, rotation.view.z)
		* DirectX::XMMatrixTranslation(position.view.x, position.view.y, position.view.z)
	;
	worldMatrix = DirectX::XMMatrixTranspose(twm);
	viewMatrix = DirectX::XMMatrixTranspose(
		  twm
		* pCamera->matrix
		* DirectX::XMMatrixPerspectiveLH(r.view.width, r.view.height, pCamera->nearPlane, pCamera->farPlane)
	);
	return viewMatrix;
}

void rave::Transform3::TransformPoint(Vector3& point) const noexcept
{
	DirectX::XMVECTOR vec = DirectX::XMVectorSet(
		point.view.x,
		point.view.y,
		point.view.z,
		1.0f
	);
	vec = DirectX::XMVector3Transform(vec, worldMatrix);
	point.view.x = DirectX::XMVectorGetX(vec);
	point.view.y = DirectX::XMVectorGetY(vec);
	point.view.z = DirectX::XMVectorGetZ(vec);
}

rave::Vector3 rave::Transform3::GetTransformedPoint(Vector3 point) const noexcept
{
	TransformPoint(point);
	return point;
}

rave::Camera3::Camera3() noexcept
	:
	position(0),
	rotation(0),
	nearPlane(0.5f),
	farPlane(10.0f),
	matrix()
{
	Concatonate();
}

rave::Camera3::Camera3(const Vector3& pos, const Vector3& rot, const float n, const float f) noexcept
	:
	position(pos),
	rotation(rot),
	nearPlane(n),
	farPlane(f),
	matrix()
{
	Concatonate();
}

rave::Matrix& rave::Camera3::Concatonate() noexcept
{
	const DirectX::XMVECTOR forwardBaseVector = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const auto lookVector = DirectX::XMVector3Transform(forwardBaseVector,
		DirectX::XMMatrixRotationRollPitchYaw(rotation.view.x, rotation.view.y, rotation.view.z)
	);
	const auto camPosition = DirectX::XMVectorSet(position.view.x, position.view.y, position.view.z, 1.0f);
	const auto camTarget = DirectX::XMVectorAdd( camPosition, lookVector );

	matrix = DirectX::XMMatrixLookAtLH(camPosition, camTarget, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));

	return matrix;
}

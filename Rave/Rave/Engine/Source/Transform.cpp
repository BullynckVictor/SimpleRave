#include "Engine/Include/Transform.h"

rave::Camera rave::Transform::camera;

rave::Transform::Transform() noexcept
	:
	position(0),
	scale(1),
	rotation(0)
{
	Concatonate();
}

rave::Transform::Transform(const Vector2& pos, const Vector2& scale, const float rotation) noexcept
	:
	position(pos),
	scale(scale),
	rotation(rotation)
{
	Concatonate();
}

rave::Transform::Transform(const Matrix& matrix) noexcept
	:
	rotation(),
	scale(),
	position(),
	viewMatrix(matrix),
	worldMatrix()
{
}

rave::Matrix& rave::Transform::Concatonate() noexcept
{
	viewMatrix = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScaling(scale.x, scale.y, 1)
		* DirectX::XMMatrixRotationZ(rotation)
		* DirectX::XMMatrixTranslation((position.x - camera.position.x), (position.y - camera.position.y), 0)
		* DirectX::XMMatrixRotationZ(-camera.rotation)
		* DirectX::XMMatrixTranslation(-(position.x - camera.position.x), -(position.y - camera.position.y), 0)
		* DirectX::XMMatrixTranslation((position.x - camera.position.x), (position.y - camera.position.y), 0)
		* DirectX::XMMatrixScaling(1 / (camera.size.x * camera.zoom), 1 / (camera.size.y * camera.zoom), 1)
	);
	worldMatrix = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixRotationZ(rotation)
		* DirectX::XMMatrixScaling(scale.x, scale.y, 1)
		* DirectX::XMMatrixTranslation(position.x, position.y, 0)
	);

	return viewMatrix;
}

void rave::Transform::TransformPoint(Vector2& point) const noexcept
{
	DirectX::XMFLOAT2 f;
	f.x = point.x;
	f.y = point.y;
	DirectX::XMVECTOR vec = DirectX::XMLoadFloat2(&f);
	vec = DirectX::XMVector2Transform(vec, worldMatrix);
	point.x = DirectX::XMVectorGetX(vec);
	point.y = DirectX::XMVectorGetY(vec);
}

rave::Vector2 rave::Transform::GetTransformedPoint(Vector2 point) const noexcept
{
	TransformPoint(point);
	return point;
}

void rave::Transform::TransformPointView(Vector2& point) noexcept
{
	DirectX::XMFLOAT2 f;
	f.x = point.x;
	f.y = point.y;
	DirectX::XMVECTOR vec = DirectX::XMLoadFloat2(&f);
	vec = DirectX::XMVector2Transform(vec, viewMatrix);
	point.x = DirectX::XMVectorGetX(vec);
	point.y = DirectX::XMVectorGetY(vec);
}

rave::Vector2 rave::Transform::GetTransformedPointView(Vector2 point) noexcept
{
	TransformPointView(point);
	return point;
}

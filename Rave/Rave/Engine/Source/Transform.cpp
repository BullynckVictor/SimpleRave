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

	return viewMatrix;
}
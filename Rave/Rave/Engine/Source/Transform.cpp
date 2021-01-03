#include "Engine/Include/Transform.h"

rave::Camera* rave::Transform2::pCamera = nullptr;

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

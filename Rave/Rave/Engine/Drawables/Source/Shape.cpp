#include "Engine/Drawables/Include/Shape.h"

rave::Shape& rave::Shape::Load(Graphics& gfx, const std::vector<Vertex2>& vertices_, const Transform2& transform_, const FColor& color_, const bool fill, const bool write)
{
	vertices.Load(gfx, vertices_, write);
	color.Load(gfx, color_, write);
	transform.Load(gfx, transform_.viewMatrix, write);
	size = vertices_.size();
	topology = fill ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP : D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;

	return *this;
}

void rave::Shape::Bind(Graphics& gfx) const
{
	gfx.ClearInfoManager();

	vertices.Bind(gfx);
	color.BindToPixelShader(gfx);
	transform.BindToVertexShader(gfx);

	GetContext(gfx)->IASetPrimitiveTopology(topology);
	GetContext(gfx)->Draw(size, 0);

	gfx.CheckInfoManager();
}

bool rave::Shape::IsFilled() const noexcept
{
	return topology == D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
}

void rave::Shape::WriteTransform(Graphics& gfx, const Transform2& transform_)
{
	transform.Write(gfx, transform_.viewMatrix);
}

rave::Shape rave::Triangle(Graphics& gfx, const Vector2& pos, const float rotation, const float scale, const FColor color, const bool fill, const bool write)
{
	static constexpr float p1 = Radian(90.0f);
	static constexpr float p2 = Radian(-30.0f);
	static constexpr float p3 = Radian(210.0f);

	std::vector<Vertex2> vertices;

	if (fill)
		vertices = {
			{ cosf(p1) * scale, sinf(p1) * scale },
			{ cosf(p2) * scale, sinf(p2) * scale },
			{ cosf(p3) * scale, sinf(p3) * scale }
	};
	else
		vertices = {
			{ cosf(p1) * scale, sinf(p1) * scale },
			{ cosf(p2) * scale, sinf(p2) * scale },
			{ cosf(p3) * scale, sinf(p3) * scale },
			{ cosf(p1) * scale, sinf(p1) * scale }
	};

	return Shape().Load(
		gfx,
		vertices,
		Transform2(pos, scale, Radian(rotation)),
		color,
		fill,
		write
	);
}

rave::Shape rave::Rect(Graphics& gfx, const Vector2& pos, const float width, const float height, const float rotation, const FColor color, const bool fill, const bool write)
{
	std::vector<Vertex2> vertices;

	if (fill)
		vertices = {
			{ -width,  height},
			{  width,  height},
			{ -width, -height},
			{  width, -height}
	};
	else
		vertices = {
			{ -width,  height},
			{  width,  height},
			{  width, -height},
			{ -width, -height},
			{ -width,  height}
	};

	return Shape().Load(
		gfx,
		vertices,
		Transform2(pos, 1, Radian(rotation)),
		color,
		fill,
		write
	);
}

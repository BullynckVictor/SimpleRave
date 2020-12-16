#include "Engine/Drawables/Include/Shape.h"

rave::InputLayout*  rave::Shape::pLayout = nullptr;
rave::PixelShader*  rave::Shape::pPixelShader = nullptr;
rave::VertexShader* rave::Shape::pVertexShader = nullptr;

rave::Shape& rave::Shape::Load(Graphics& gfx, const std::vector<Vertex>& vertices_, const Transform& transform_, const FColor& color_, const bool fill, const bool write)
{
	vertices.Load(gfx, vertices_, write);
	color.Load(gfx, color_, write);
	transform.Load(gfx, transform_.viewMatrix, write);
	size = vertices_.size();
	topology = fill ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP : D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;

	return *this;
}

void rave::Shape::Bind(Graphics& gfx)
{
	rave_assert_info(IsInitialized(), L"rave::Shape has not been staticaly initialized yet, have you called rave::Shape::StaticInitialize?");

	gfx.ClearInfoManager();

	pLayout->Bind(gfx);
	pPixelShader->Bind(gfx);
	pVertexShader->Bind(gfx);

	vertices.Bind(gfx);
	color.BindToPixelShader(gfx);
	transform.BindToVertexShader(gfx);

	GetContext(gfx)->IASetPrimitiveTopology(topology);
	GetContext(gfx)->Draw(size, 0);

	gfx.CheckInfoManager();
}

void rave::Shape::StaticInitialize(Graphics& gfx, GraphicsMemory& memory)
{
	pLayout = memory.inputLayoutCodex.Get("position");
	pPixelShader = memory.pixelShaderCodex.Get("color");
	pVertexShader = memory.vertexShaderCodex.Get("transform");

	rave_assert_info(pLayout, L"Key \"position\" not found in inputLayoutCodex");
	rave_assert_info(pPixelShader, L"Key \"color\" not found in inputLayoutCodex");
	rave_assert_info(pVertexShader, L"Key \"transform\" not found in inputLayoutCodex");
}

bool rave::Shape::IsFilled() const noexcept
{
	return topology == D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
}

bool rave::Shape::IsInitialized() noexcept
{
	return pPixelShader && pLayout && pVertexShader;
}

rave::Shape rave::Triangle(Graphics& gfx, const Vector2& pos, const float rotation, const float scale, const FColor color, const bool fill, const bool write)
{
	static constexpr float p1 = Radian(90.0f);
	static constexpr float p2 = Radian(-30.0f);
	static constexpr float p3 = Radian(210.0f);

	std::vector<Vertex> vertices;

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
		Transform(pos, scale, Radian(rotation)),
		color,
		fill,
		write
	);
}

rave::Shape rave::Rect(Graphics& gfx, const Vector2& pos, const float width, const float height, const float rotation, const FColor color, const bool fill, const bool write)
{
	std::vector<Vertex> vertices;

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
		Transform(pos, 1, Radian(rotation)),
		color,
		fill,
		write
	);
}

#include "Engine/Drawables/Include/Shape.h"

rave::InputLayout*  rave::Shape::pLayout = nullptr;
rave::PixelShader*  rave::Shape::pPixelShader = nullptr;
rave::VertexShader* rave::Shape::pVertexShader = nullptr;

rave::Shape::Shape(Graphics& gfx, const std::vector<Vertex>& vertices, const FColor& color, const bool fill, const bool write)
	:
	vertices(gfx, vertices, write),
	color(gfx, color, write),
	size(vertices.size()),
	topology(fill ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP : D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP)
{
}

void rave::Shape::Bind(Graphics& gfx)
{
	rave_assert_info(IsInitialized(), L"rave::Shape has not been staticaly initialized yet, have you called rave::Shape::StaticInitialize?");

	pLayout->Bind(gfx);
	pPixelShader->Bind(gfx);
	pVertexShader->Bind(gfx);

	vertices.Bind(gfx);
	color.BindToPixelShader(gfx);

	GetContext(gfx)->IASetPrimitiveTopology(topology);
	GetContext(gfx)->Draw(size, 0);
}

void rave::Shape::StaticInitialize(Graphics& gfx, GraphicsMemory& memory)
{
	pLayout = memory.inputLayoutCodex.Get("position");
	pPixelShader = memory.pixelShaderCodex.Get("color");
	pVertexShader = memory.vertexShaderCodex.Get("position");

	rave_assert_info(pLayout, L"Key \"position\" not found in inputLayoutCodex");
	rave_assert_info(pPixelShader, L"Key \"color\" not found in inputLayoutCodex");
	rave_assert_info(pVertexShader, L"Key \"position\" not found in inputLayoutCodex");
}

bool rave::Shape::IsFilled() const noexcept
{
	return topology == D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
}

bool rave::Shape::IsInitialized() noexcept
{
	return pPixelShader && pLayout && pVertexShader;
}

rave::Shape rave::Triangle(Graphics& gfx, const FColor color, const float rotation, const float scale, const bool fill, const bool write)
{
	const float p1 = Radian(90.0f + rotation);
	const float p2 = Radian(-30.0f + rotation);
	const float p3 = Radian(210.0f + rotation);

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

	return Shape(
		gfx,
		vertices,
		color,
		fill,
		write
	);
}

rave::Shape rave::Rectangle(Graphics& gfx, const FColor color, const float width, const float height, const bool fill, const bool write)
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
			{ -width, -height},
			{  width, -height},
			{ -width,  height}
		};

	return Shape(
		gfx,
		vertices,
		color,
		fill,
		write
	);
}


#include "Engine/Drawables/Include/Cube.h"
#include "Engine/Utilities/Include/Random.h"

rave::Color RandomColor()
{
	return rave::Colors::Make(
		rave::RandomChar<unsigned char>(),
		rave::RandomChar<unsigned char>(),
		rave::RandomChar<unsigned char>()
	);
}

rave::Cube& rave::Cube::Load(Graphics& gfx, const Vector3& dim, const Transform3& transform_)
{
	vertices.Load(
		gfx, 
		{
			{ -dim.view.width / 2, -dim.view.height / 2, -dim.view.depth / 2 },
			{  dim.view.width / 2, -dim.view.height / 2, -dim.view.depth / 2 },
			{ -dim.view.width / 2,  dim.view.height / 2, -dim.view.depth / 2 },
			{  dim.view.width / 2,  dim.view.height / 2, -dim.view.depth / 2 },
			{ -dim.view.width / 2, -dim.view.height / 2,  dim.view.depth / 2 },
			{  dim.view.width / 2, -dim.view.height / 2,  dim.view.depth / 2 },
			{ -dim.view.width / 2,  dim.view.height / 2,  dim.view.depth / 2 },
			{  dim.view.width / 2,  dim.view.height / 2,  dim.view.depth / 2 },
		}, 
		false
	);
	indices.Load(
		gfx,
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
		},
		false
	);
	std::vector<Color> v(8);
	for (auto& c : v)
		c = RandomColor();
	colors.Load(
		gfx, 
		v,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		false
	);
	transform.Load(gfx, transform_.viewMatrix, true);

	return *this;
}

void rave::Cube::Bind(Graphics& gfx) const
{
	gfx.ClearInfoManager();

	vertices.Bind(gfx);
	indices.Bind(gfx);
	colors.Bind(gfx);
	transform.BindToVertexShader(gfx);

	GetContext(gfx)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetContext(gfx)->DrawIndexed(36, 0, 0);

	gfx.CheckInfoManager();
}
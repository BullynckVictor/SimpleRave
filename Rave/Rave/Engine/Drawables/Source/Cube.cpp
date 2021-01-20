#include "Engine/Drawables/Include/Cube.h"
#include "Engine/Utilities/Include/Random.h"

rave::Color RandomColor()
{
	return rave::Colors::Make(
		rave::Random<unsigned char>(),
		rave::Random<unsigned char>(),
		rave::Random<unsigned char>()
	);
}

rave::Cube& rave::Cube::Load(Graphics& gfx, const Vector3& dim, const Transform3& transform_)
{
	vertices.Load(
		gfx, 
		{
			/*										front										*/
			{ { -dim.view.width / 2, -dim.view.height / 2, -dim.view.depth / 2 }, {  0,  0, -1 } },
			{ {  dim.view.width / 2, -dim.view.height / 2, -dim.view.depth / 2 }, {  0,  0, -1 } },
			{ { -dim.view.width / 2,  dim.view.height / 2, -dim.view.depth / 2 }, {  0,  0, -1 } },
			{ {  dim.view.width / 2,  dim.view.height / 2, -dim.view.depth / 2 }, {  0,  0, -1 } },

			/*										back										*/
			{ { -dim.view.width / 2, -dim.view.height / 2,  dim.view.depth / 2 }, {  0,  0,  1 } },
			{ {  dim.view.width / 2, -dim.view.height / 2,  dim.view.depth / 2 }, {  0,  0,  1 } },
			{ { -dim.view.width / 2,  dim.view.height / 2,  dim.view.depth / 2 }, {  0,  0,  1 } },
			{ {  dim.view.width / 2,  dim.view.height / 2,  dim.view.depth / 2 }, {  0,  0,  1 } },

			/*										right										*/
			{ {  dim.view.width / 2, -dim.view.height / 2, -dim.view.depth / 2 }, {  1,  0,  0 } },
			{ {  dim.view.width / 2, -dim.view.height / 2,  dim.view.depth / 2 }, {  1,  0,  0 } },
			{ {  dim.view.width / 2,  dim.view.height / 2, -dim.view.depth / 2 }, {  1,  0,  0 } },
			{ {  dim.view.width / 2,  dim.view.height / 2,  dim.view.depth / 2 }, {  1,  0,  0 } },

			/*										left										*/
			{ { -dim.view.width / 2, -dim.view.height / 2, -dim.view.depth / 2 }, { -1,  0,  0 } },
			{ { -dim.view.width / 2, -dim.view.height / 2,  dim.view.depth / 2 }, { -1,  0,  0 } },
			{ { -dim.view.width / 2,  dim.view.height / 2, -dim.view.depth / 2 }, { -1,  0,  0 } },
			{ { -dim.view.width / 2,  dim.view.height / 2,  dim.view.depth / 2 }, { -1,  0,  0 } },

			/*										top											*/
			{ { -dim.view.width / 2,  dim.view.height / 2, -dim.view.depth / 2 }, {  0,  1,  0 } },
			{ { -dim.view.width / 2,  dim.view.height / 2,  dim.view.depth / 2 }, {  0,  1,  0 } },
			{ {  dim.view.width / 2,  dim.view.height / 2,  dim.view.depth / 2 }, {  0,  1,  0 } },
			{ {  dim.view.width / 2,  dim.view.height / 2, -dim.view.depth / 2 }, {  0,  1,  0 } },

			/*										bottom										*/
			{ { -dim.view.width / 2, -dim.view.height / 2, -dim.view.depth / 2 }, {  0, -1,  0 } },
			{ { -dim.view.width / 2, -dim.view.height / 2,  dim.view.depth / 2 }, {  0, -1,  0 } },
			{ {  dim.view.width / 2, -dim.view.height / 2,  dim.view.depth / 2 }, {  0, -1,  0 } },
			{ {  dim.view.width / 2, -dim.view.height / 2, -dim.view.depth / 2 }, {  0, -1,  0 } },
		}, 
		false
	);
	indices.Load(
		gfx,
		{
			0,  2,  1,		2,  3,  1,
			5,  7,  4,		7,  6,  4,
			9,  8,  10,		10, 11, 9,
			12, 13, 14,		13, 15, 14,
			16, 17, 19,		17, 18, 19,
			20, 23, 21,		23, 22, 21
		},
		false
	);
	transform.Load(gfx, { transform_.viewMatrix, transform_.worldMatrix }, true);
	materialBuffer.Load(gfx, material.Widen());

	return *this;
}

void rave::Cube::Bind(Graphics& gfx) const
{
	gfx.ClearInfoManager();

	vertices.Bind(gfx);
	indices.Bind(gfx);
	transform.BindToVertexShader(gfx);
	materialBuffer.BindToPixelShader(gfx);
	
	GetContext(gfx)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetContext(gfx)->DrawIndexed(36, 0, 0);

	gfx.CheckInfoManager();
}

void rave::Cube::WriteTransform(Graphics& gfx, const Transform3& transform_)
{
	transform.Write(gfx, { transform_.viewMatrix, transform_.worldMatrix });
}

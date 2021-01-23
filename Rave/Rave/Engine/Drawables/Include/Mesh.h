#pragma once
#include "Engine/Drawables/Include/Drawable.h"

namespace rave
{
	class Mesh
	{
	public:
		Mesh& Load(Graphics& gfx, const Transform3& transform, const wchar_t* filename);
		void Bind(Graphics& gfx) const;

		void WriteTransform(Graphics& gfx, const Transform3& transform);
		Material material;

	private:
		ConstantBuffer<MatrixBuffer> transform;
		ConstantBuffer<WideMaterial> materialBuffer;
		VertexBuffer<NVertex3> vertices;
		IndexBuffer indices;
	};
}
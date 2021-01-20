#pragma once
#include "Engine/Drawables/Include/Drawable.h"

namespace rave
{
	class Cube : public GraphicsFriend
	{
	public:
		Cube& Load(Graphics& gfx, const Vector3& dim, const Transform3& transform);
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
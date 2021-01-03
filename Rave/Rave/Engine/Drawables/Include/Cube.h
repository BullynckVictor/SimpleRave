#pragma once
#include "Engine/Drawables/Include/Drawable.h"

namespace rave
{
	class Cube : public GraphicsFriend
	{
	public:
		Cube& Load(Graphics& gfx, const Vector3& dim, const Transform3& transform);
		void Bind(Graphics& gfx) const;

		ConstantBuffer<Matrix> transform;
		
	private:
		VertexBuffer<Vertex3> vertices;
		IndexBuffer indices;
		BufferView colors;
	};
}
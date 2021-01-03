#pragma once
#include "Engine/Drawables/Include/Drawable.h"
#include "Engine/Utilities/Include/Vector.h"

namespace rave
{
	class Shape : public GraphicsFriend
	{
	public:
		Shape& Load(Graphics& gfx, const std::vector<Vertex2>& vertices, const Transform2& transform, const FColor& color, const bool fill = true, const bool write = true);

		void Bind(Graphics& gfx) const;

		bool IsFilled() const noexcept;
		void WriteTransform(Graphics& gfx, const Transform2& transform);

		VertexBuffer<Vertex2>	vertices;
		ConstantBuffer<FColor>	color;
		ConstantBuffer<Matrix>	transform;

	private:
		Topology topology;
		size_t size;
	};

	Shape Triangle(Graphics& gfx, const Vector2& pos, const float rotation, const float scale, const FColor color, const bool fill = true, const bool write = true);
	Shape Rect(Graphics& gfx, const Vector2& pos, const float width, const float height, const float rotation, const FColor color, const bool fill = true, const bool write = true);
}
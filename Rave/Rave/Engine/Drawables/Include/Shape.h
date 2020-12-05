#pragma once
#include "Engine/Drawables/Include/Drawable.h"
#include "Engine/Utilities/Include/Color.h"

namespace rave
{
	class Shape : public GraphicsFriend
	{
	public:
		Shape(Graphics& gfx, const std::vector<Vertex>& vertices, const Transform& transform, const FColor& color, const bool fill = true, const bool write = false);

		void Bind(Graphics& gfx);
		static void StaticInitialize(Graphics& gfx, GraphicsMemory& memory);

		bool IsFilled() const noexcept;

		VertexBuffer<Vertex>	vertices;
		ConstantBuffer<FColor>	color;
		ConstantBuffer<Matrix>	transform;

	private:
		static bool IsInitialized() noexcept;

		const Topology topology;
		const size_t size;

		static InputLayout*  pLayout;
		static PixelShader*  pPixelShader;
		static VertexShader* pVertexShader;
	};

	Shape Triangle(Graphics& gfx, const Vector2& pos, const float rotation, const float scale, const FColor color, const bool fill = true, const bool write = false);
	Shape Rectangle(Graphics& gfx, const Vector2& pos, const float width, const float height, const float rotation, const FColor color, const bool fill = true, const bool write = false);
}
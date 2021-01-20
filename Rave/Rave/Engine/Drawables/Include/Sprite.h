#pragma once
#include "Engine/Drawables/Include/Drawable.h"

namespace rave
{

	class Sprite : public GraphicsFriend
	{
	public:
		Sprite& Load(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const Transform2& transform, const bool pixel = false, const bool write = true);

		void Bind(Graphics& gfx) const;

		void WriteTransform(Graphics& gfx, const Transform2& transform);		
		ConstantBuffer<Matrix>	transform;

	private:
		VertexBuffer<TVertex2> vertices;

		Sampler* pSampler = nullptr;
		TextureView* pTexture = nullptr;
	};
}
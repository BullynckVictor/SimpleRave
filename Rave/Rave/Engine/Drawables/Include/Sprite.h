#pragma once
#include "Engine/Drawables/Include/Drawable.h"

namespace rave
{

	class Sprite : public GraphicsFriend
	{
	public:
		Sprite& Load(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const Transform& transform, const bool pixel = false, const bool write = true);

		void Bind(Graphics& gfx) const;

		ConstantBuffer<Matrix>	transform;

	private:
		VertexBuffer<TVertex> vertices;

		Sampler* pSampler = nullptr;
		TextureView* pTexture = nullptr;
	};
}
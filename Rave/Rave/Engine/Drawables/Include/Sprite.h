#pragma once
#include "Engine/Drawables/Include/Drawable.h"

namespace rave
{

	class Sprite : public GraphicsFriend
	{
	public:
		Sprite& Load(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const Transform& transform, const bool pixel = false, const bool write = true);

		void Bind(Graphics& gfx);
		static void StaticInitialize(Graphics& gfx, GraphicsMemory& memory);

		ConstantBuffer<Matrix>	transform;

	private:
		static bool IsInitialized() noexcept;

		VertexBuffer<TVertex> vertices;
		TextureView* pTexture;
		Sampler* pSampler;

		static InputLayout* pLayout;
		static PixelShader* pPixelShader;
		static VertexShader* pVertexShader;
	};
}
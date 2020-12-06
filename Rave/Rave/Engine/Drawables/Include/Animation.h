#pragma once
#include "Engine/Drawables/Include/Drawable.h"

namespace rave
{
	class AnimationState : public GraphicsFriend
	{

	};

	class Animation : public GraphicsFriend
	{
	public:
		Animation(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const Transform& transform, const size_t nFrames, const float fps, const bool write = true);

		void Bind(Graphics& gfx);
		static void StaticInitialize(Graphics& gfx, GraphicsMemory& memory);

		ConstantBuffer<Matrix>	transform;

	private:
		static bool IsInitialized() noexcept;

		std::vector<VertexBuffer<TVertex>> vertices;
		TextureView* pTexture;
		const float spf;

		static InputLayout* pLayout;
		static PixelShader* pPixelShader;
		static VertexShader* pVertexShader;
	};
}
#pragma once
#include "Engine/Drawables/Include/Drawable.h"
#include "Engine/Utilities/Include/Timer.h"

namespace rave
{
	struct AnimationState : public GraphicsFriend
	{
		AnimationState(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const size_t nFrames);
		std::vector<VertexBuffer<TVertex>> vertices;
		TextureView* pTexture;
	};

	class Animation : public GraphicsFriend
	{
	public:
		Animation(Graphics& gfx, GraphicsMemory& memory, const std::vector<AnimationState>& states, const Transform& transform, const float fps, const bool pixel = false, const bool write = true);

		void Bind(Graphics& gfx);
		void SetState(const size_t state) noexcept;
		void ResetTimer() noexcept;
		static void StaticInitialize(Graphics& gfx, GraphicsMemory& memory);

		ConstantBuffer<Matrix>	transform;

	private:
		static bool IsInitialized() noexcept;

		const float spf;
		size_t index = 0;
		std::vector<AnimationState> animations;
		Sampler* pSampler;
		Timer timer;

		static InputLayout* pLayout;
		static PixelShader* pPixelShader;
		static VertexShader* pVertexShader;
	};
}
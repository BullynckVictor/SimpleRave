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
		Animation& Load(Graphics& gfx, GraphicsMemory& memory, const std::vector<AnimationState>& states, const Transform& transform, const float fps, const bool pixel = false, const bool write = true);
		Animation& Load(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const size_t nFrames, const Transform& transform, const float fps, const bool pixel = false, const bool write = true);

		void WriteTransform(Graphics& gfx, const Transform& transform);
		void Bind(Graphics& gfx) const;
		void SetState(const size_t state) noexcept;
		void ResetTimer() noexcept;

		ConstantBuffer<Matrix>	transform;

	private:
		float spf = 0;
		size_t index = 0;
		std::vector<AnimationState> animations;
		Sampler* pSampler = nullptr;
		Timer timer;
	};
}
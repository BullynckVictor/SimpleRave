#include "Engine/Drawables/Include/Animation.h"

rave::Animation& rave::Animation::Load(Graphics& gfx, GraphicsMemory& memory, const std::vector<AnimationState>& states, const Transform& transform_, const float fps, const bool pixel, const bool write)
{
	animations = states;
	spf = (1.0f / fps);
	pSampler = memory.samplerCodex.Get(pixel ? "pixel" : "linear");

	transform.Load(gfx, transform_.viewMatrix, write);

#ifndef NDEBUG
	if (!pSampler)
	{
		std::wstringstream error;
		error << L"Key \"";
		error << pixel ? "pixel" : "linear";
		error << L"\" not found in textureCodex";

		rave_throw_message(error.str().c_str());
	}
#endif

	return *this;
}

rave::Animation& rave::Animation::Load(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const size_t nFrames, const Transform& transform, const float fps, const bool pixel, const bool write)
{
	return Load(gfx, memory, { { gfx, memory, textureKey, nFrames } }, transform, fps, pixel, write);
}

void rave::Animation::Bind(Graphics& gfx) const
{
	gfx.ClearInfoManager();

	animations[index].pTexture->Bind(gfx);
	pSampler->Bind(gfx);

	auto& v = animations[index].vertices;
	v[size_t(timer.Peek() / spf) % v.size()].Bind(gfx);

	transform.BindToVertexShader(gfx);

	GetContext(gfx)->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	GetContext(gfx)->Draw(4, 0);

	gfx.CheckInfoManager();
}

void rave::Animation::SetState(const size_t state) noexcept
{
	index = state;
}

void rave::Animation::ResetTimer() noexcept
{
	timer.Mark();
}

rave::AnimationState::AnimationState(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const size_t nFrames)
	:
	pTexture(memory.textureCodex.Get(textureKey))
{
#ifndef NDEBUG
	if (!pTexture)
	{
		std::wstringstream error;
		error << L"Key \"";
		error << textureKey;
		error << L"\" not found in textureCodex";

		rave_throw_message(error.str().c_str());
	}
#endif

	Vertex size = *memory.sizeCodex.Get(textureKey);
	size.x /= (float)nFrames;
	size /= std::max(size.x, size.y);
	const float frameWidth = 1.0f / (float)nFrames;

	vertices.reserve(nFrames);
	for (size_t i = 0; i < nFrames; i++)
	{
		VertexBuffer<TVertex> v;
		v.Load(
			gfx,
			{
				{ {-size.x,  size.y}, { ((float)i + 0) * frameWidth, 0 } },
				{ { size.x,  size.y}, { ((float)i + 1) * frameWidth, 0 } },
				{ {-size.x, -size.y}, { ((float)i + 0) * frameWidth, 1 } },
				{ { size.x, -size.y}, { ((float)i + 1) * frameWidth, 1 } }
			},
			false
		);

		vertices.push_back(v);
	}
}

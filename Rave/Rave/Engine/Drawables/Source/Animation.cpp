#include "Engine/Drawables/Include/Animation.h"

rave::InputLayout*  rave::Animation::pLayout = nullptr;
rave::PixelShader*  rave::Animation::pPixelShader = nullptr;
rave::VertexShader* rave::Animation::pVertexShader = nullptr;


rave::Animation::Animation(Graphics& gfx, GraphicsMemory& memory, const std::vector<AnimationState>& states, const Transform& transform, const float fps, const bool pixel, const bool write)
	:
	animations(states),
	transform(gfx, transform.viewMatrix, write),
	spf(1.0f / fps),
	pSampler(memory.samplerCodex.Get(pixel ? "pixel" : "linear"))
{
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
}

void rave::Animation::Bind(Graphics& gfx)
{
	rave_assert_info(IsInitialized(), L"rave::Animation has not been staticaly initialized yet, have you called rave::Animation::StaticInitialize?");

	gfx.ClearInfoManager();

	pLayout->Bind(gfx);
	pPixelShader->Bind(gfx);
	pVertexShader->Bind(gfx);

	animations[index].pTexture->Bind(gfx);
	pSampler->Bind(gfx);

	auto& v = animations[index].vertices;
	v[size_t(timer.Peek() / spf) % v.size()].Bind(gfx);

	transform.BindToVertexShader(gfx);

	GetContext(gfx)->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	GetContext(gfx)->Draw(4, 0);

	gfx.CheckInfoManager();
}

void rave::Animation::StaticInitialize(Graphics& gfx, GraphicsMemory& memory)
{
	pLayout = memory.inputLayoutCodex.Get("texture");
	pPixelShader = memory.pixelShaderCodex.Get("texture");
	pVertexShader = memory.vertexShaderCodex.Get("texture");

	rave_assert_info(pLayout, L"Key \"texture\" not found in inputLayoutCodex");
	rave_assert_info(pPixelShader, L"Key \"texture\" not found in inputLayoutCodex");
	rave_assert_info(pVertexShader, L"Key \"texture\" not found in inputLayoutCodex");
}

void rave::Animation::SetState(const size_t state) noexcept
{
	index = state;
}

void rave::Animation::ResetTimer() noexcept
{
	timer.Mark();
}

bool rave::Animation::IsInitialized() noexcept
{
	return pPixelShader && pLayout && pVertexShader;
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

	Vertex size = 1;
	const float frameWidth = 1.0f / (float)nFrames;

	vertices.reserve(nFrames);
	for (size_t i = 0; i < nFrames; i++)
	{
		vertices.push_back(
			VertexBuffer<TVertex>(
				gfx,
				{
					{ {-size.x / 2,  size.y / 2}, { ((float)i + 0) * frameWidth, 0 } },
					{ { size.x / 2,  size.y / 2}, { ((float)i + 1) * frameWidth, 0 } },
					{ {-size.x / 2, -size.y / 2}, { ((float)i + 0) * frameWidth, 1 } },
					{ { size.x / 2, -size.y / 2}, { ((float)i + 1) * frameWidth, 1 } }
				},
				false
				)
		);
	}
}

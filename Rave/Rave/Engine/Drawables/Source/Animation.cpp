#include "Engine/Drawables/Include/Animation.h"

rave::InputLayout*  rave::Animation::pLayout = nullptr;
rave::PixelShader*  rave::Animation::pPixelShader = nullptr;
rave::VertexShader* rave::Animation::pVertexShader = nullptr;

rave::Animation::Animation(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const Transform& transform, const size_t nFrames, const float fps, const bool write)
	:
	transform(gfx, transform.viewMatrix),
	pTexture(memory.textureCodex.Get(textureKey)),
	spf(1.0f / fps)
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

void rave::Animation::Bind(Graphics& gfx)
{
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

bool rave::Animation::IsInitialized() noexcept
{
	return false;
}

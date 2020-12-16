#include "Engine/Drawables/Include/Sprite.h"

rave::InputLayout* rave::Sprite::pLayout = nullptr;
rave::PixelShader* rave::Sprite::pPixelShader = nullptr;
rave::VertexShader* rave::Sprite::pVertexShader = nullptr;

rave::Sprite& rave::Sprite::Load(Graphics& gfx, GraphicsMemory& memory, const char* textureKey, const Transform& transform_, const bool pixel, const bool write)
{
	pTexture = memory.textureCodex.Get(textureKey);
	pSampler = memory.samplerCodex.Get(pixel ? "pixel" : "linear");

	transform.Load(gfx, transform_.viewMatrix, write);

#ifndef NDEBUG
	if (!pTexture)
	{
		std::wstringstream error;
		error << L"Key \"";
		error << textureKey;
		error << L"\" not found in textureCodex";

		rave_throw_message(error.str().c_str());
	}
	if (!pSampler)
	{
		std::wstringstream error;
		error << L"Key \"";
		error << pixel ? "pixel" : "linear";
		error << L"\" not found in textureCodex";

		rave_throw_message(error.str().c_str());
	}
#endif

	Vector2 size = *memory.sizeCodex.Get(textureKey);
	size /= std::max(size.x, size.y);
	vertices.Load(
		gfx,
		{
			{ {-size.x / 2,  size.y / 2}, { 0, 0 } },
			{ { size.x / 2,  size.y / 2}, { 1, 0 } },
			{ {-size.x / 2, -size.y / 2}, { 0, 1 } },
			{ { size.x / 2, -size.y / 2}, { 1, 1 } }
		},
		false
	);

	return *this;
}

void rave::Sprite::Bind(Graphics& gfx)
{
	rave_assert_info(IsInitialized(), L"rave::Shape has not been staticaly initialized yet, have you called rave::Shape::StaticInitialize?");

	gfx.ClearInfoManager();

	pLayout->Bind(gfx);
	pPixelShader->Bind(gfx);
	pVertexShader->Bind(gfx);

	vertices.Bind(gfx);
	pSampler->Bind(gfx);
	pTexture->Bind(gfx);
	transform.BindToVertexShader(gfx);

	GetContext(gfx)->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	GetContext(gfx)->Draw(4, 0);

	gfx.CheckInfoManager();
}

void rave::Sprite::StaticInitialize(Graphics& gfx, GraphicsMemory& memory)
{
	pLayout = memory.inputLayoutCodex.Get("texture");
	pPixelShader = memory.pixelShaderCodex.Get("texture");
	pVertexShader = memory.vertexShaderCodex.Get("texture");

	rave_assert_info(pLayout, L"Key \"texture\" not found in inputLayoutCodex");
	rave_assert_info(pPixelShader, L"Key \"texture\" not found in inputLayoutCodex");
	rave_assert_info(pVertexShader, L"Key \"texture\" not found in inputLayoutCodex");
}

bool rave::Sprite::IsInitialized() noexcept
{
	return pPixelShader && pLayout && pVertexShader;
}

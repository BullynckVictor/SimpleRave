#include "Engine/Drawables/Include/Sprite.h"

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

void rave::Sprite::Bind(Graphics& gfx) const
{
	gfx.ClearInfoManager();

	vertices.Bind(gfx);
	pSampler->Bind(gfx);
	pTexture->Bind(gfx);
	transform.BindToVertexShader(gfx);

	GetContext(gfx)->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	GetContext(gfx)->Draw(4, 0);

	gfx.CheckInfoManager();
}
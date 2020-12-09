#pragma once
#include "Engine/Utilities/Include/Codex.h"
#include "Engine/Graphics/Include/VertexShader.h"
#include "Engine/Graphics/Include/PixelShader.h"
#include "Engine/Graphics/Include/InputLayout.h"
#include "Engine/Graphics/Include/TextureView.h"
#include "Engine/Graphics/Include/Sampler.h"
#include "Engine/Utilities/Include/Vector2D.h"

namespace rave
{
	class GraphicsMemory
	{
	public:
		Codex<InputLayout>  inputLayoutCodex;
		Codex<PixelShader>  pixelShaderCodex;
		Codex<VertexShader> vertexShaderCodex;
		Codex<TextureView>  textureCodex;
		Codex<Sampler>		samplerCodex;
		Codex<Vector2>		sizeCodex;
	};
}
#pragma once
#include "Engine/Utilities/Include/Codex.h"
#include "Engine/Graphics/Include/VertexShader.h"
#include "Engine/Graphics/Include/PixelShader.h"
#include "Engine/Graphics/Include/InputLayout.h"

namespace rave
{
	class GraphicsMemory
	{
	public:
		Codex<InputLayout>  inputLayoutCodex;
		Codex<PixelShader>  pixelShaderCodex;
		Codex<VertexShader> vertexShaderCodex;
	};
}
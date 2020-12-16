#include "Engine/Drawables/Include/FlatRenderer.h"

std::wstring FormatCodexError(const char* name, const wchar_t* codex)
{
	std::wstringstream wss;
	wss << L"Key \"" << name << L"\" not found in " << codex;
	return wss.str();
}

rave::FlatRenderer& rave::FlatRenderer::Load(Graphics& gfx, GraphicsMemory& memory, const char* layout, const char* pixelShader, const char* vertexShader)
{
	pLayout = memory.inputLayoutCodex.Get(layout);
	pPixelShader = memory.pixelShaderCodex.Get(pixelShader);
	pVertexShader = memory.vertexShaderCodex.Get(vertexShader);

	rave_assert_info(pLayout, FormatCodexError(layout, L"inputLayoutCodex").c_str());
	rave_assert_info(pPixelShader, FormatCodexError(pixelShader, L"pixelShaderCodex").c_str());
	rave_assert_info(pVertexShader, FormatCodexError(vertexShader, L"vertexShaderCodex").c_str());

	return *this;
}
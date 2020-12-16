#include "Engine/Graphics/Include/Blender.h"

rave::Blender& rave::Blender::Load(Graphics& gfx, const bool blendAlpha)
{
	SetAlpha(gfx, blendAlpha);
	return *this;
}

void rave::Blender::SetAlpha(Graphics& gfx, const bool blendAlpha)
{
	HRESULT hr;

	D3D11_BLEND_DESC blendDesc = {};
	auto& brt = blendDesc.RenderTarget[0];
	if (blendAlpha)
	{
		brt.BlendEnable = TRUE;
		brt.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		brt.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		brt.BlendOp = D3D11_BLEND_OP_ADD;
		brt.SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		brt.DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
		brt.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		brt.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	else
	{
		brt.BlendEnable = FALSE;
		brt.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	}
	rave_check_hr(GetDevice(gfx)->CreateBlendState(&blendDesc, &pBlendState));
}

void rave::Blender::Bind(Graphics& gfx) const noexcept
{
	GetContext(gfx)->OMSetBlendState(pBlendState.Get(), NULL, 0xFFFFFFFFu);
}

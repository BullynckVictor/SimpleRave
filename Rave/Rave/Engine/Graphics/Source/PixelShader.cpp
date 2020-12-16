#include "Engine/Graphics/Include/PixelShader.h"

rave::PixelShader& rave::PixelShader::Load(Graphics& gfx, const wchar_t* path)
{
	HRESULT hr;
	ComPtr<ID3DBlob> pBlob;
	rave_check_file(path);
	rave_check_hr(D3DReadFileToBlob(path, &pBlob));
	rave_check_hr(GetDevice(gfx)->CreatePixelShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		NULL,
		&pShader
	));

	return *this;
}

void rave::PixelShader::Bind(Graphics& gfx) const noexcept
{
	GetContext(gfx)->PSSetShader(pShader.Get(), NULL, 0);
}

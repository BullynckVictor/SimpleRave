#include "Engine/Graphics/Include/VertexShader.h"

rave::VertexShader::VertexShader(Graphics& gfx, const wchar_t* path)
{
	HRESULT hr;
	ComPtr<ID3DBlob> pBlob;
	rave_check_file(path);
	rave_check_hr(D3DReadFileToBlob(path, &pBlob));
	rave_check_hr(GetDevice(gfx)->CreateVertexShader(
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		NULL,
		&pShader
	));
}

void rave::VertexShader::Bind(Graphics& gfx) const noexcept
{
	GetContext(gfx)->VSSetShader(pShader.Get(), NULL, 0);
}

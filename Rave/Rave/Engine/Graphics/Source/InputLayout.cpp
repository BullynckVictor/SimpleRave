#include "Engine/Graphics/Include/InputLayout.h"

rave::InputLayout::InputLayout(Graphics& gfx, const wchar_t* path, const std::vector<InputLayoutElement>& elements)
{
	HRESULT hr;
	ComPtr<ID3DBlob> pBlob;
	rave_check_file(path);
	rave_check_hr(D3DReadFileToBlob(path, &pBlob));

	std::vector<D3D11_INPUT_ELEMENT_DESC> d3elements(elements.size());
	size_t offset = 0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		ZeroMemory(&d3elements[i], sizeof D3D11_INPUT_ELEMENT_DESC);
		d3elements[i].SemanticName = elements[i].semanticName.c_str();
		d3elements[i].Format = elements[i].format;
		d3elements[i].AlignedByteOffset = offset;
		offset += elements[i].byteSize;
	}

	rave_check_hr(GetDevice(gfx)->CreateInputLayout(
		d3elements.data(),
		d3elements.size(),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pLayout
	));
}

void rave::InputLayout::Bind(Graphics& gfx) const noexcept
{
	GetContext(gfx)->IASetInputLayout(pLayout.Get());
}

rave::InputLayoutElement::InputLayoutElement(const char* semanticName, const DXGI_FORMAT format, const size_t byteSize)
	:
	semanticName(semanticName),
	format(format),
	byteSize(byteSize)
{
}

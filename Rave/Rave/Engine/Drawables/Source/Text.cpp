#include "Engine/Drawables/Include/Text.h"

rave::Text::Text(const wchar_t* text, const Vector2& pos)
	:
	string(text),
	pos(pos)
{
}

rave::Text& rave::Text::Load(Graphics& gfx, RenderTarget& target, const wchar_t* font, const float size, const FColor& color, Vector2 boundingSize)
{
	HRESULT hr;

	float em = PixelToPoint(std::min((float)target.GetHeight(), (float)target.GetWidth()) * size);

	rave_check_hr(GetD2DTarget(target)->CreateSolidColorBrush(
		D2D1::ColorF(color.view.r, color.view.g, color.view.b, color.view.a),
		pBrush.ReleaseAndGetAddressOf()
	));

	rave_check_hr(GetDWFactory(gfx)->CreateTextFormat(
		font,
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		floor(em),
		L"en-us",
		&pFormat
	));

	Update(gfx, target, boundingSize);

	return *this;
}

void rave::Text::Update(Graphics& gfx, RenderTarget& target, Vector2 boundingSize)
{
	HRESULT hr;

	TargetSize ts = target.GetTargetSize();
	boundingSize /= ts.relative;
	boundingSize = (boundingSize + 1.0f) * (Vector2)ts.pixel / 2;
	boundingSize.view.y = (float)ts.pixel.view.y - boundingSize.view.y;

	rave_check_hr(GetDWFactory(gfx)->CreateTextLayout(
		string.c_str(),
		(uint32_t)string.size(),
		pFormat.Get(),
		boundingSize.view.x,
		boundingSize.view.y,
		&pLayout
	));
}

void rave::Text::Bind(RenderTarget& target) const
{
	TargetSize ts = target.GetTargetSize();
	D2D1_POINT_2F p = { pos.view.x, pos.view.y };
	
	p.x /= ts.relative.view.x;
	p.y /= ts.relative.view.y;
	p.x = (p.x + 1.0f) * (float)ts.pixel.view.x /  2;
	p.y = (p.y - 1.0f) * (float)ts.pixel.view.y / -2;

	GetD2DTarget(target)->DrawTextLayout(
		p,
		pLayout.Get(),
		pBrush.Get()
	);
}

float rave::Text::GetHeight(RenderTarget& target) const
{
	HRESULT hr;

	DWRITE_TEXT_METRICS metrics = {};
	rave_check_hr(pLayout->GetMetrics(&metrics));
	return PointToPixel( metrics.height + metrics.top ) / std::min((float)target.GetHeight(), (float)target.GetWidth());
}

rave::Vector2 rave::Text::GetTargetBoundingSize(RenderTarget& target) noexcept
{
	TargetSize ts = target.GetTargetSize();
	return Vector2({ ts.relative.view.x, -ts.relative.view.y });
}

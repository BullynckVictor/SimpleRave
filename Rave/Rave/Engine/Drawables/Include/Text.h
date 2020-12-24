#pragma once
#include "Engine/Drawables/Include/Drawable.h"
#include "Engine/Utilities/Include/Color.h"
#include "Engine/Graphics/Include/RenderTarget.h"

namespace rave
{
	class Text : public GraphicsFriend, public Direct2DObject
	{
	public:
		Text() = default;
		Text(const wchar_t* text, const Vector2& pos);

		Text& Load(Graphics& gfx, RenderTarget& target, const wchar_t* font, const float size, const FColor& color, Vector2 boundingSize = Vector2(targetSize.relative.x, -targetSize.relative.y ));
		void Update(Graphics& gfx, RenderTarget& target, Vector2 boundingSize = Vector2(targetSize.relative.x, -targetSize.relative.y));
		void Bind(RenderTarget& target) const;

		std::wstring string;
		Vector2 pos;

		static Vector2 GetTargetBoundingSize(RenderTarget& target) noexcept;

	private:
		ComPtr<IDWriteTextFormat> pFormat;
		ComPtr<IDWriteTextLayout> pLayout;
		ComPtr<ID2D1SolidColorBrush> pBrush;
	};
}
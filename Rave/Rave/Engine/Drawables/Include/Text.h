#pragma once
#include "Engine/Drawables/Include/Drawable.h"
#include "Engine/Utilities/Include/Vector.h"
#include "Engine/Graphics/Include/RenderTarget.h"

namespace rave
{
	class Text : public GraphicsFriend, public Direct2DObject
	{
	public:
		Text() = default;
		Text(const wchar_t* text, const Vector2& pos);

		Text& Load(Graphics& gfx, RenderTarget& target, const wchar_t* font, const float size, const FColor& color, Vector2 boundingSize = Vector2({ targetSize.relative.view.x, -targetSize.relative.view.y }));
		void Update(Graphics& gfx, RenderTarget& target, Vector2 boundingSize = Vector2({ targetSize.relative.view.x, -targetSize.relative.view.y }));
		void Bind(RenderTarget& target) const;

		std::wstring string;
		Vector2 pos;

		static Vector2 GetTargetBoundingSize(RenderTarget& target) noexcept;
		float GetHeight(RenderTarget& target) const;

	private:
		ComPtr<IDWriteTextFormat> pFormat;
		ComPtr<IDWriteTextLayout> pLayout;
		ComPtr<ID2D1SolidColorBrush> pBrush;
	};

	template<typename T>
	static constexpr T PixelToPoint(const T& a)
	{
		return (T)72 / (T)96 * a;
	}
	template<typename T>
	static constexpr T PointToPixel(const T& a)
	{
		return (T)96 / (T)72 * a;
	}
}
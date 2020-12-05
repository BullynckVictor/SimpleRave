#pragma once

namespace rave
{
	static constexpr long double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

	constexpr float Radian(const float degree) noexcept { return degree / 180.0f * (float)pi; }
	constexpr float Degree(const float radian) noexcept { return radian * 180.0f / (float)pi; }
}
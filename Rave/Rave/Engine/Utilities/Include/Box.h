#pragma once
#include "Engine/Utilities/Include/Vector2D.h"
#include <algorithm>

namespace rave
{
	template<typename T>
	struct Box_t
	{
		Box_t()
			:
			left	(0),
			top		(0),
			right	(0),
			bottom	(0)
		{}
		Box_t(const T& left, const T& top, const T& right, const T& bottom)
			:
			left	(left),
			top		(top),
			right	(right),
			bottom	(bottom)
		{}
		Box_t(const Vector2D_t<T>& p1, const Vector2D_t<T>& p2)
			:
			left	(p1.x),
			top		(p1.y),
			right	(p2.x),
			bottom	(p2.y)
		{}

		Box_t operator+ (const Vector2D_t<T>& rhs) const noexcept
		{
			return Box_t(*this) += rhs;
		}
		Box_t operator- (const Vector2D_t<T>& rhs) const noexcept
		{
			return Box_t(*this) -= rhs;
		}
		Box_t operator* (const Vector2D_t<T>& rhs) const noexcept
		{
			return Box_t(*this) *= rhs;
		}
		Box_t operator/ (const Vector2D_t<T>& rhs) const noexcept
		{
			return Box_t(*this) /= rhs;
		}

		Box_t operator+= (const Vector2D_t<T>& rhs) noexcept
		{
			left	+= rhs.x;
			right	+= rhs.x;
			top		+= rhs.y;
			bottom	+= rhs.y;
			return *this;
		}
		Box_t operator-= (const Vector2D_t<T>& rhs) noexcept
		{
			left	-= rhs.x;
			right	-= rhs.x;
			top		-= rhs.y;
			bottom	-= rhs.y;
			return *this;
		}
		Box_t operator*= (const Vector2D_t<T>& rhs) noexcept
		{
			left	*= rhs.x;
			right	*= rhs.x;
			top		*= rhs.y;
			bottom	*= rhs.y;
			return *this;
		}
		Box_t operator/= (const Vector2D_t<T>& rhs) noexcept
		{
			left	/= rhs.x;
			right	/= rhs.x;
			top		/= rhs.y;
			bottom	/= rhs.y;
			return *this;
		}

		bool Collides(const Vector2D_t<T>& p) const noexcept
		{
			if constexpr (std::is_integral<T>::value)
				return p.x < right && p.x > left && p.y > top && p.y < bottom;
			else
				return p.x < right && p.x > left && p.y < top && p.y > bottom;
		}

		T left;
		T top;
		T right;
		T bottom;
	};

	typedef Box_t<float>		Box;
	typedef Box_t<unsigned int>	BoxU;
	typedef Box_t<int>			BoxI;
	typedef Box_t<double>		BoxD;
}
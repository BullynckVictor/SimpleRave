#pragma once
#include "Engine/Utilities/Include/Vector.h"
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
		Box_t(const Vector<2, T>& p1, const Vector<2, T>& p2)
			:
			left	(p1.view.x),
			top		(p1.view.y),
			right	(p2.view.x),
			bottom	(p2.view.y)
		{}

		Box_t operator+ (const Vector<2, T>& rhs) const noexcept
		{
			return Box_t(*this) += rhs;
		}
		Box_t operator- (const Vector<2, T>& rhs) const noexcept
		{
			return Box_t(*this) -= rhs;
		}
		Box_t operator* (const Vector<2, T>& rhs) const noexcept
		{
			return Box_t(*this) *= rhs;
		}
		Box_t operator/ (const Vector<2, T>& rhs) const noexcept
		{
			return Box_t(*this) /= rhs;
		}

		Box_t operator+= (const Vector<2, T>& rhs) noexcept
		{
			left	+= rhs.view.x;
			right	+= rhs.view.x;
			top		+= rhs.view.y;
			bottom	+= rhs.view.y;
			return *this;
		}
		Box_t operator-= (const Vector<2, T>& rhs) noexcept
		{
			left	-= rhs.view.x;
			right	-= rhs.view.x;
			top		-= rhs.view.y;
			bottom	-= rhs.view.y;
			return *this;
		}
		Box_t operator*= (const Vector<2, T>& rhs) noexcept
		{
			left	*= rhs.view.x;
			right	*= rhs.view.x;
			top		*= rhs.view.y;
			bottom	*= rhs.view.y;
			return *this;
		}
		Box_t operator/= (const Vector<2, T>& rhs) noexcept
		{
			left	/= rhs.view.x;
			right	/= rhs.view.x;
			top		/= rhs.view.y;
			bottom	/= rhs.view.y;
			return *this;
		}

		bool Collides(const Vector<2, T>& p) const noexcept
		{
			if constexpr (std::is_integral<T>::value)
				return p.view.x < right && p.view.x > left && p.view.y > top && p.view.y < bottom;
			else
				return p.view.x < right && p.view.x > left && p.view.y < top && p.view.y > bottom;
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
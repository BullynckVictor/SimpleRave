#pragma once

namespace rave
{
	template<typename T>
	struct Vector2D_t
	{
		T x;
		T y;

		Vector2D_t()
			:
			x(0),
			y(0)
		{}
		Vector2D_t(const T x, const T y)
			:
			x(x),
			y(y)
		{}
		Vector2D_t(const T value)
			:
			x(value),
			y(value)
		{}
		Vector2D_t(const Vector2D_t& other)
			:
			x(other.x),
			y(other.y)
		{}
		Vector2D_t& operator=  (const Vector2D_t& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}
		Vector2D_t& operator=  (const Vector2D_t&& rhs) noexcept
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		const bool  operator== (const Vector2D_t& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
		const bool  operator!= (const Vector2D_t& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		}

		Vector2D_t  operator+  (const Vector2D_t& rhs) const
		{
			return { x + rhs.x, y + rhs.y };
		}
		Vector2D_t  operator-  (const Vector2D_t& rhs) const
		{
			return { x - rhs.x, y - rhs.y };
		}
		Vector2D_t& operator+= (const Vector2D_t& rhs)
		{
			*this = *this + rhs;
			return *this;
		}
		Vector2D_t& operator-= (const Vector2D_t& rhs)
		{
			*this = *this - rhs;
			return *this;
		}

		Vector2D_t  operator+  (const T rhs) const
		{
			return { x + rhs, y + rhs };
		}
		Vector2D_t  operator-  (const T rhs) const
		{
			return { x - rhs, y - rhs };
		}
		Vector2D_t  operator*  (const T rhs) const
		{
			return { x * rhs, y * rhs };
		}
		Vector2D_t  operator/  (const T rhs) const
		{
			return { x / rhs, y / rhs };
		}
		Vector2D_t& operator+= (const T rhs)
		{
			*this = *this + rhs;
			return *this;
		}
		Vector2D_t& operator-= (const T rhs)
		{
			*this = *this - rhs;
			return *this;
		}
		Vector2D_t& operator*= (const T rhs)
		{
			*this = *this * rhs;
			return *this;
		}
		Vector2D_t& operator/= (const T rhs)
		{
			*this = *this / rhs;
			return *this;
		}

		T Dot(const Vector2D_t& rhs) const
		{
			return x * rhs.x + y * rhs.y;
		}

		T LengthSq() const
		{
			return x * x + y * y;
		}
		T Length() const
		{
			return (T)sqrt((double)LengthSq());
		}

		Vector2D_t Normalized() const
		{
			T length = Length();
			return { x / length, y / length };
		}
		void Normalize()
		{
			*this = Normalized();
		}
	};

	typedef Vector2D_t<float>	Vector2;
	typedef Vector2D_t<float>	Vertex;
	typedef Vector2D_t<double>	Vector2_D;
	typedef Vector2D_t<int>		Vector2_I;
	typedef Vector2D_t<int>		Vector2_U;
}
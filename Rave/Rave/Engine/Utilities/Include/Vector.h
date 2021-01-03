#pragma once
#include <algorithm>
#include <array>

namespace rave
{
	template<size_t D, typename T>
	union VectorView {};

	template<typename T>
	union VectorView<1, T>
	{
		struct { T x; };
		struct { T r; };
		struct { T u; };
		struct { T width; };
	};

	template<typename T>
	union VectorView<2, T>
	{
		struct { T x, y; };
		struct { T r, g; };
		struct { T u, v; };
		struct { T width, height; };
	};

	template<typename T>
	union VectorView<3, T>
	{
		struct { T x, y, z; };
		struct { T r, g, b; };
		struct { T u, v; };
		struct { T width, height, depth; };
	};

	template<typename T>
	union VectorView<4, T>
	{
		struct { T x, y, z, w; };
		struct { T r, g, b, a; };
		struct { T u, v; };
		struct { T width, height, depth; };
	};

	namespace detail
	{
		template <typename T, std::size_t ... Is>
		constexpr std::array<T, sizeof...(Is)>
			create_array(T value, std::index_sequence<Is...>) noexcept
		{
			// cast Is to void to remove the warning: unused value
			return { {(static_cast<void>(Is), value)...} };
		}
	}

	template <std::size_t N, typename T>
	constexpr std::array<T, N> create_array(const T& value) noexcept
	{
		return detail::create_array(value, std::make_index_sequence<N>());
	}

	template<size_t D, typename T>
	union Vector
	{
		constexpr Vector() noexcept
			:
			data(create_array<D, T>(0))
		{}
		constexpr Vector(const T& value) noexcept
			:
			data(create_array<D, T>(value))
		{}
		constexpr Vector(const std::initializer_list<T>& values) noexcept
			:
			data()
		{
			std::copy_n(values.begin(), std::min(D, values.size()), data.begin());
		}
		constexpr Vector(const Vector& other) noexcept
			:
			data(other.data)
		{}

		template<size_t D2, typename T2>
		constexpr explicit operator Vector<D2, T2>() noexcept
		{
			Vector<D2, T2> ret;
			std::transform(data.begin(), data.begin() + std::min(data.size(), ret.data.size()), ret.data.begin(), [](const T& e) { return static_cast<T2>(e); });
			return ret;
		}

		Vector& operator= (const Vector& rhs) noexcept
		{
			data = rhs.data;
			return *this;
		}
		const bool  operator== (const Vector& rhs) const noexcept
		{
			return data == rhs.data;
		}
		const bool  operator!= (const Vector& rhs) const noexcept
		{
			return data != rhs.data;
		}

		Vector& operator+= (const Vector& rhs) noexcept
		{
			std::transform(data.begin(), data.end(), rhs.data.begin(), data.begin(), [](const T& a, const T& b) { return a + b; });
			return *this;
		}
		Vector& operator-= (const Vector& rhs) noexcept
		{
			std::transform(data.begin(), data.end(), rhs.data.begin(), data.begin(), [](const T& a, const T& b) { return a - b; });
			return *this;
		}
		Vector& operator*= (const Vector& rhs) noexcept
		{
			std::transform(data.begin(), data.end(), rhs.data.begin(), data.begin(), [](const T& a, const T& b) { return a * b; });
			return *this;
		}
		Vector& operator/= (const Vector& rhs) noexcept
		{
			std::transform(data.begin(), data.end(), rhs.data.begin(), data.begin(), [](const T& a, const T& b) { return a / b; });
			return *this;
		}

		Vector  operator+  (const Vector& rhs) const noexcept
		{
			return Vector(*this) += rhs;
		}
		Vector  operator-  (const Vector& rhs) const noexcept
		{
			return Vector(*this) -= rhs;
		}
		Vector  operator*  (const Vector& rhs) const noexcept
		{
			return Vector(*this) *= rhs;
		}
		Vector  operator/  (const Vector& rhs) const noexcept
		{
			return Vector(*this) /= rhs;
		}

		Vector& operator+= (const T& rhs) noexcept
		{
			std::for_each(data.begin(), data.end(), [rhs](T& e) { e += rhs; });
			return *this;
		}
		Vector& operator-= (const T& rhs) noexcept
		{
			std::for_each(data.begin(), data.end(), [rhs](T& e) { e -= rhs; });
			return *this;
		}
		Vector& operator*= (const T& rhs) noexcept
		{
			std::for_each(data.begin(), data.end(), [rhs](T& e) { e *= rhs; });
			return *this;
		}
		Vector& operator/= (const T& rhs) noexcept
		{
			std::for_each(data.begin(), data.end(), [rhs](T& e) { e /= rhs; });
			return *this;
		}

		Vector  operator+  (const T& rhs) const noexcept
		{
			return Vector(*this) += rhs;
		}
		Vector  operator-  (const T& rhs) const noexcept
		{
			return Vector(*this) -= rhs;
		}
		Vector  operator*  (const T& rhs) const noexcept
		{
			return Vector(*this) *= rhs;
		}
		Vector  operator/  (const T& rhs) const noexcept
		{
			return Vector(*this) /= rhs;
		}

		T Dot(const Vector& rhs) const
		{
			T dot = 0;
			auto i1 = data.begin();
			auto i2 = rhs.data.begin();
			for (; i1 < data.end(); i1++, i2++)
			{
				dot += *i1 * *i2;
			}
			return dot;
		}

		T LengthSq() const
		{
			T len = 0;
			for (const auto& e : data)
				len += e * e;
			return len;
		}
		T Length() const
		{
			return (T)sqrt((double)LengthSq());
		}

		Vector Normalized() const
		{
			Vector v = *this;
			v.Normalize();
			return v;
		}
		void Normalize()
		{
			T length = Length();
			if (length == 0)
			{
				*this = 0;
				return;
			}
			for (auto& e : data)
				e /= length;
		}

		std::array<T, D> data;
		VectorView<std::min(4u, D), T> view;
	};

	typedef Vector<2, size_t> Size;
	typedef Vector<2, float>  Vector2;
	typedef Vector<3, float>  Vector3;
	typedef Vector<4, float>  Vector4;
	typedef Vector<2, float>  Vertex2;
	typedef Vector<3, float>  Vertex3;
	typedef Vector<4, unsigned char> Color;
	typedef Vector<4, float>		 FColor;

	constexpr Color  ConvertColor(const FColor color)
	{
		return Color({
			unsigned char(color.data[0] * 255.0f),
			unsigned char(color.data[1] * 255.0f),
			unsigned char(color.data[2] * 255.0f),
			unsigned char(color.data[3] * 255.0f)
		});
	}
	constexpr FColor ConvertColor(const Color color)
	{
		return FColor({
			(float)color.data[0] / 255.0f,
			(float)color.data[1] / 255.0f,
			(float)color.data[2] / 255.0f,
			(float)color.data[3] / 255.0f
		});
	}

	namespace Colors
	{
		static constexpr Color Make(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a = 255) noexcept
		{
			return Color({ r, g, b, a });
		}
		static constexpr Color Transparent	= Make(   0,   0,   0,   0 );
		static constexpr Color White		= Make( 255, 255, 255 );
		static constexpr Color Black		= Make(   0,   0,   0 );
		static constexpr Color Red			= Make( 255,   0,   0 );
		static constexpr Color Green		= Make(   0, 255,   0 );
		static constexpr Color Blue			= Make(   0,   0, 255 );
		static constexpr Color Yellow		= Make( 255, 255,   0 );
		static constexpr Color Cyan			= Make(   0, 255, 255 );
		static constexpr Color Magenta		= Make( 255,   0, 255 );
		static constexpr Color Gray			= Make( 128, 128, 128 );
		static constexpr Color LightGray	= Make( 211, 211, 211 );
		static constexpr Color RaveBlue		= Make(  13,  30,  43 );
		static constexpr Color RaveYellow	= Make( 242, 213,  65 );
	}
	namespace FColors
	{
		static constexpr FColor Make(const float r, const float g, const float b, const float a = 1.0f) noexcept
		{
			return FColor({ r, g, b, a });
		}
		static constexpr FColor Transparent = Make( 0.0f, 0.0f, 0.0f );
		static constexpr FColor White		= Make( 1.0f, 1.0f, 1.0f );
		static constexpr FColor Black		= Make( 0.0f, 0.0f, 0.0f );
		static constexpr FColor Red			= Make( 1.0f, 0.0f, 0.0f );
		static constexpr FColor Green		= Make( 0.0f, 1.0f, 0.0f );
		static constexpr FColor Blue		= Make( 0.0f, 0.0f, 1.0f );
		static constexpr FColor Yellow		= Make( 1.0f, 1.0f, 0.0f );
		static constexpr FColor Cyan		= Make( 0.0f, 1.0f, 1.0f );
		static constexpr FColor Magenta		= Make( 1.0f, 0.0f, 1.0f );
		static constexpr FColor Gray		= ConvertColor( Colors::Make( 128, 128, 128 ) );
		static constexpr FColor LightGray	= ConvertColor( Colors::Make( 211, 211, 211 ) );
		static constexpr FColor RaveBlue	= Make( 0.051f, 0.118f, 0.169f );
		static constexpr FColor RaveYellow	= Make( 0.949f, 0.835f, 0.255f );
	}
}
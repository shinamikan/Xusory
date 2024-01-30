#include "../Vector2.h"
#include "../Vector4.h"

namespace XusoryEngine
{
	Float2::Float2(FLOAT x, FLOAT y) : x(x), y(y) { }

	Vector2::Vector2() : m_vector(_mm_setzero_ps()) { }
	Vector2::Vector2(FLOAT x, FLOAT y) : m_vector(_mm_setr_ps(x, y, 0.0f, 0.0f)) { }
	Vector2::Vector2(FLOAT scalar) : m_vector(_mm_setr_ps(scalar, scalar, 0.0f, 0.0f)) { }
	Vector2::Vector2(const Float2& v) : m_vector(_mm_setr_ps(v.x, v.y, 0.0f, 0.0f)) { }

	Vector2 Vector2::operator+(const Vector2& other) const
	{
		return Vector2(_mm_add_ps(m_vector, other.m_vector));
	}

	Vector2 Vector2::operator-(const Vector2& other) const
	{
		return Vector2(_mm_sub_ps(m_vector, other.m_vector));
	}

	Vector2 Vector2::operator*(FLOAT scalar) const
	{
		return Vector2(_mm_mul_ps(m_vector, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f)));
	}

	Vector2 Vector2::operator*(const Vector2& other) const
	{
		return Vector2(_mm_mul_ps(m_vector, other.m_vector));
	}

	Vector2 Vector2::operator/(FLOAT scalar) const
	{
		__m128 m128Temp = _mm_div_ps(m_vector, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f));
		m128Temp.m128_f32[2] = 0;
		m128Temp.m128_f32[3] = 0;

		return Vector2(m128Temp);
	}

	Vector2 Vector2::operator/(const Vector2& other) const
	{
		__m128 m128Temp = _mm_div_ps(m_vector, other.m_vector);
		m128Temp.m128_f32[2] = 0;
		m128Temp.m128_f32[3] = 0;

		return Vector2(m128Temp);
	}

	Vector2 Vector2::operator==(const Vector2& other) const
	{
		__m128 m128Temp = _mm_cmpeq_ps(m_vector, other.m_vector);
		m128Temp.m128_f32[2] = 0;
		m128Temp.m128_f32[3] = 0;

		return Vector2(m128Temp);
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		m_vector = _mm_add_ps(m_vector, other.m_vector);
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other)
	{
		m_vector = _mm_sub_ps(m_vector, other.m_vector);
		return *this;
	}

	Vector2& Vector2::operator*=(FLOAT scalar)
	{
		m_vector = _mm_mul_ps(m_vector, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f));
		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& other)
	{
		m_vector = _mm_mul_ps(m_vector, other.m_vector);
		return *this;
	}

	Vector2& Vector2::operator/=(FLOAT scalar)
	{
		m_vector = _mm_div_ps(m_vector, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f));
		m_vector.m128_f32[2] = 0;
		m_vector.m128_f32[3] = 0;

		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& other)
	{
		m_vector = _mm_div_ps(m_vector, other.m_vector);
		m_vector.m128_f32[2] = 0;
		m_vector.m128_f32[3] = 0;

		return *this;
	}

	FLOAT Vector2::X() const
	{
		return m_vector.m128_f32[0];
	}

	FLOAT Vector2::Y() const
	{
		return m_vector.m128_f32[1];
	}

	Float2 Vector2::GetVector() const
	{
		Float4 f4Temp;
		_mm_store_ps(reinterpret_cast<FLOAT*>(&f4Temp), m_vector);

		Float2 f2Result;
		memcpy(&f2Result, &f4Temp, sizeof(Float2));

		return f2Result;
	}

	void Vector2::SetVector(FLOAT x, FLOAT y)
	{
		m_vector = _mm_setr_ps(x, y, 0.0f, 0.0f);
	}

	FLOAT Vector2::Length() const
	{
		return std::sqrt(
			m_vector.m128_f32[0] * m_vector.m128_f32[0] +
			m_vector.m128_f32[1] * m_vector.m128_f32[1]);
	}

	FLOAT Vector2::LengthSq() const
	{
		return m_vector.m128_f32[0] * m_vector.m128_f32[0] +
			m_vector.m128_f32[1] * m_vector.m128_f32[1];
	}

	FLOAT Vector2::Dot(const Vector2& other) const
	{
		return _mm_dp_ps(m_vector, other.m_vector, 0xff).m128_f32[0];
	}

	Vector2 Vector2::Normalize() const
	{
		const FLOAT length = Length();
		return { m_vector.m128_f32[0] / length, m_vector.m128_f32[1] / length };
	}

	Vector2 Vector2::Sqrt() const
	{
		return Vector2(_mm_sqrt_ps(m_vector));
	}

	Vector2 Vector2::Max(const Vector2& other) const
	{
		return Vector2(_mm_max_ps(m_vector, other.m_vector));
	}

	Vector2 Vector2::Min(const Vector2& other) const
	{
		return Vector2(_mm_min_ps(m_vector, other.m_vector));
	}

	Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, FLOAT weight)
	{
		return start + (end - start) * weight;
	}

	const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
	const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
	const Vector2 Vector2::OneX = Vector2(1.0f, 0.0f);
	const Vector2 Vector2::OneY = Vector2(0.0f, 1.0f);

	Vector2::Vector2(const __m128& v) : m_vector(v) { }
}

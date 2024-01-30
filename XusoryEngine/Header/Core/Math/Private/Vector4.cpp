#include "../Vector4.h"

namespace XusoryEngine
{
	Float4::Float4(FLOAT x, FLOAT y, FLOAT z, FLOAT w) : x(x), y(y), z(z), w(w) { }

	Vector4::Vector4() : m_vector(_mm_setzero_ps()) { }
	Vector4::Vector4(FLOAT x, FLOAT y, FLOAT z, FLOAT w) : m_vector(_mm_setr_ps(x, y, z, w)) { }
	Vector4::Vector4(FLOAT scalar) : m_vector(_mm_set_ps1(scalar)) { }
	Vector4::Vector4(const Float4& v) : m_vector(_mm_setr_ps(v.x, v.y, v.z, v.w)) { }

	Vector4 Vector4::operator+(const Vector4& other) const
	{
		return Vector4(_mm_add_ps(m_vector, other.m_vector));
	}

	Vector4 Vector4::operator-(const Vector4& other) const
	{
		return Vector4(_mm_sub_ps(m_vector, other.m_vector));
	}

	Vector4 Vector4::operator*(FLOAT scalar) const
	{
		return Vector4(_mm_mul_ps(m_vector, _mm_set_ps1(scalar)));
	}

	Vector4 Vector4::operator*(const Vector4& other) const
	{
		return Vector4(_mm_mul_ps(m_vector, other.m_vector));
	}

	Vector4 Vector4::operator/(FLOAT scalar) const
	{
		return Vector4(_mm_div_ps(m_vector, _mm_set_ps1(scalar)));
	}

	Vector4 Vector4::operator/(const Vector4& other) const
	{
		return Vector4(_mm_div_ps(m_vector, other.m_vector));
	}

	Vector4 Vector4::operator==(const Vector4& other) const
	{
		return Vector4(_mm_cmpeq_ps(m_vector, other.m_vector));
	}

	Vector4& Vector4::operator+=(const Vector4& other)
	{
		m_vector = _mm_add_ps(m_vector, other.m_vector);
		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& other)
	{
		m_vector = _mm_sub_ps(m_vector, other.m_vector);
		return *this;
	}

	Vector4& Vector4::operator*=(FLOAT scalar)
	{
		m_vector = _mm_mul_ps(m_vector, _mm_set_ps1(scalar));
		return *this;
	}

	Vector4& Vector4::operator*=(const Vector4& other)
	{
		m_vector = _mm_mul_ps(m_vector, other.m_vector);
		return *this;
	}

	Vector4& Vector4::operator/=(FLOAT scalar)
	{
		m_vector = _mm_div_ps(m_vector, _mm_set_ps1(scalar));
		return *this;
	}

	Vector4& Vector4::operator/=(const Vector4& other)
	{
		m_vector = _mm_div_ps(m_vector, other.m_vector);
		return *this;
	}

	FLOAT Vector4::X() const
	{
		return m_vector.m128_f32[0];
	}

	FLOAT Vector4::Y() const
	{
		return m_vector.m128_f32[1];
	}

	FLOAT Vector4::Z() const
	{
		return m_vector.m128_f32[2];
	}

	FLOAT Vector4::W() const
	{
		return m_vector.m128_f32[3];
	}

	Float4 Vector4::GetVector() const
	{
		Float4 f4Temp;
		_mm_store_ps(reinterpret_cast<FLOAT*>(&f4Temp), m_vector);

		return f4Temp;
	}

	void Vector4::SetVector(FLOAT x, FLOAT y, FLOAT z, FLOAT w)
	{
		m_vector = _mm_setr_ps(x, y, z, w);
	}

	FLOAT Vector4::Length() const
	{
		return std::sqrt(
			m_vector.m128_f32[0] * m_vector.m128_f32[0] +
			m_vector.m128_f32[1] * m_vector.m128_f32[1] +
			m_vector.m128_f32[2] * m_vector.m128_f32[2] +
			m_vector.m128_f32[3] * m_vector.m128_f32[3]);
	}

	FLOAT Vector4::LengthSq() const
	{
		return m_vector.m128_f32[0] * m_vector.m128_f32[0] +
			m_vector.m128_f32[1] * m_vector.m128_f32[1] +
			m_vector.m128_f32[2] * m_vector.m128_f32[2] +
			m_vector.m128_f32[3] * m_vector.m128_f32[3];
	}

	FLOAT Vector4::Dot(const Vector4& other) const
	{
		return _mm_dp_ps(m_vector, other.m_vector, 0xff).m128_f32[0];
	}

	Vector4 Vector4::Normalize() const
	{
		const FLOAT length = Length();
		return { m_vector.m128_f32[0] / length, m_vector.m128_f32[1] / length,
			m_vector.m128_f32[2] / length, m_vector.m128_f32[3] / length };
	}

	Vector4 Vector4::Sqrt() const
	{
		return Vector4(_mm_sqrt_ps(m_vector));
	}

	Vector4 Vector4::Max(const Vector4& other) const
	{
		return Vector4(_mm_max_ps(m_vector, other.m_vector));
	}

	Vector4 Vector4::Min(const Vector4& other) const
	{
		return Vector4(_mm_min_ps(m_vector, other.m_vector));
	}

	Vector4 Vector4::Lerp(const Vector4& start, const Vector4& end, FLOAT weight)
	{
		return start + (end - start) * weight;
	}

	const Vector4 Vector4::Zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::One = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	const Vector4 Vector4::OneX = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::OneY = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	const Vector4 Vector4::OneZ = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
	const Vector4 Vector4::OneW = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

	Vector4::Vector4(const __m128& v) : m_vector(v) { }
}

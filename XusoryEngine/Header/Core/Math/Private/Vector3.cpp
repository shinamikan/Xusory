#include "../Vector3.h"
#include "../Vector4.h"
#include "../Common/MathDefine.h"

namespace XusoryEngine
{
	Float3::Float3(FLOAT x, FLOAT y, FLOAT z): x(x), y(y), z(z) { }

	Vector3::Vector3() : m_vector(_mm_setzero_ps()) { }
	Vector3::Vector3(FLOAT x, FLOAT y, FLOAT z) : m_vector(_mm_setr_ps(x, y, z, 0.0f)) { }
	Vector3::Vector3(FLOAT scalar) : m_vector(_mm_setr_ps(scalar, scalar, scalar, 0.0f)) { }
	Vector3::Vector3(const Float3& v) : m_vector(_mm_setr_ps(v.x, v.y, v.z, 0.0f)) { }

	Vector3 Vector3::operator+(const Vector3& other) const
	{
		return Vector3(_mm_add_ps(m_vector, other.m_vector));
	}

	Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(_mm_sub_ps(m_vector, other.m_vector));
	}

	Vector3 Vector3::operator*(FLOAT scalar) const
	{
		return Vector3(_mm_mul_ps(m_vector, _mm_setr_ps(scalar, scalar, scalar, 0.0f)));
	}

	Vector3 Vector3::operator*(const Vector3& other) const
	{
		return Vector3(_mm_mul_ps(m_vector, other.m_vector));
	}

	Vector3 Vector3::operator/(FLOAT scalar) const
	{
		__m128 vectorTemp = _mm_div_ps(m_vector, _mm_setr_ps(scalar, scalar, scalar, 0.0f));
		vectorTemp.m128_f32[3] = 0;

		return Vector3(vectorTemp);
	}

	Vector3 Vector3::operator/(const Vector3& other) const
	{
		__m128 vectorTemp = _mm_div_ps(m_vector, other.m_vector);
		vectorTemp.m128_f32[3] = 0;

		return Vector3(vectorTemp);
	}

	Vector3 Vector3::operator==(const Vector3& other) const
	{
		__m128 vectorTemp = _mm_cmpeq_ps(m_vector, other.m_vector);
		vectorTemp.m128_f32[3] = 0;

		return Vector3(vectorTemp);
	}

	Vector3& Vector3::operator+=(const Vector3& other)
	{
		m_vector = _mm_add_ps(m_vector, other.m_vector);
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& other)
	{
		m_vector = _mm_sub_ps(m_vector, other.m_vector);
		return *this;
	}

	Vector3& Vector3::operator*=(FLOAT scalar)
	{
		m_vector = _mm_mul_ps(m_vector, _mm_setr_ps(scalar, scalar, scalar, 0.0f));
		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& other)
	{
		m_vector = _mm_mul_ps(m_vector, other.m_vector);
		return *this;
	}

	Vector3& Vector3::operator/=(FLOAT scalar)
	{
		m_vector = _mm_div_ps(m_vector, _mm_setr_ps(scalar, scalar, scalar, 0.0f));
		m_vector.m128_f32[3] = 0;

		return *this;
	}

	Vector3& Vector3::operator/=(const Vector3& other)
	{
		m_vector = _mm_div_ps(m_vector, other.m_vector);
		m_vector.m128_f32[3] = 0;

		return *this;
	}

	FLOAT Vector3::X() const
	{
		return m_vector.m128_f32[0];
	}

	FLOAT Vector3::Y() const
	{
		return m_vector.m128_f32[1];
	}

	FLOAT Vector3::Z() const
	{
		return m_vector.m128_f32[2];
	}

	Float3 Vector3::GetVector() const
	{
		Float4 f4Temp;
		_mm_store_ps(reinterpret_cast<FLOAT*>(&f4Temp), m_vector);

		Float3 f3Result;
		memcpy(&f3Result, &f4Temp, sizeof(Float3));

		return f3Result;
	}

	void Vector3::SetVector(FLOAT x, FLOAT y, FLOAT z)
	{
		m_vector = _mm_setr_ps(x, y, z, 0.0f);
	}

	void Vector3::SetVector(const Float3& vector)
	{
		m_vector = _mm_setr_ps(vector.x, vector.y, vector.z, 0.0f);
	}

	FLOAT Vector3::Length() const
	{
		return std::sqrt(
			m_vector.m128_f32[0] * m_vector.m128_f32[0] +
			m_vector.m128_f32[1] * m_vector.m128_f32[1] +
			m_vector.m128_f32[2] * m_vector.m128_f32[2]);
	}

	FLOAT Vector3::LengthSq() const
	{
		return m_vector.m128_f32[0] * m_vector.m128_f32[0] +
			m_vector.m128_f32[1] * m_vector.m128_f32[1] +
			m_vector.m128_f32[2] * m_vector.m128_f32[2];
	}

	FLOAT Vector3::Dot(const Vector3& other) const
	{
		return _mm_dp_ps(m_vector, other.m_vector, 0xff).m128_f32[0];
	}

	Vector3 Vector3::Normalize() const
	{
		const FLOAT length = Length();
		return { m_vector.m128_f32[0] / length, m_vector.m128_f32[1] / length, m_vector.m128_f32[2] / length };
	}

	Vector3 Vector3::Sqrt() const
	{
		return Vector3(_mm_sqrt_ps(m_vector));
	}

	Vector3 Vector3::Max(const Vector3& other) const
	{
		return Vector3(_mm_max_ps(m_vector, other.m_vector));
	}

	Vector3 Vector3::Min(const Vector3& other) const
	{
		return Vector3(_mm_min_ps(m_vector, other.m_vector));
	}

	Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
	{
		const __m128 m128Temp1 = _mm_mul_ps(lhs.m_vector, SHUFFLE_VECTOR3(rhs.m_vector, 1, 2, 0));
		const __m128 m128Temp2 = _mm_mul_ps(SHUFFLE_VECTOR3(lhs.m_vector, 1, 2, 0), rhs.m_vector);
		const __m128 m128Temp3 = _mm_sub_ps(m128Temp1, m128Temp2);

		return Vector3(SHUFFLE_VECTOR3(m128Temp3, 1, 2, 0));
	}

	Vector3 Vector3::Lerp(const Vector3& start, const Vector3& end, FLOAT weight)
	{
		return start + (end - start) * weight;
	}

	const Vector3 Vector3::Zero = Vector3(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::One = Vector3(1.0f, 1.0f, 1.0f);
	const Vector3 Vector3::OneX = Vector3(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::OneY = Vector3(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::OneZ = Vector3(0.0f, 0.0f, 1.0f);

	Vector3::Vector3(const __m128& v) : m_vector(v) { }
}

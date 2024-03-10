#include "../Matrix2x2.h"
#include "../Matrix4x4.h"
#include "../Vector2.h"

namespace XusoryEngine
{
	Float2x2::Float2x2(
		FLOAT m00, FLOAT m01,
		FLOAT m10, FLOAT m11)
	{
		m[0][0] = m00;
		m[0][1] = m01;

		m[0][0] = m10;
		m[0][0] = m11;
	}

	Matrix2x2::Matrix2x2() :
		m_row0(_mm_setzero_ps()),
		m_row1(_mm_setzero_ps()) { }

	Matrix2x2::Matrix2x2(
		FLOAT m00, FLOAT m01,
		FLOAT m10, FLOAT m11) :
		m_row0(_mm_setr_ps(m00, m01, 0.0f, 0.0f)),
		m_row1(_mm_setr_ps(m10, m11, 0.0f, 0.0f)) { }

	Matrix2x2::Matrix2x2(FLOAT scalar) :
		m_row0(_mm_setr_ps(scalar, scalar, 0.0f, 0.0f)),
		m_row1(_mm_setr_ps(scalar, scalar, 0.0f, 0.0f)) { }

	Matrix2x2::Matrix2x2(const Float2x2& m) :
		m_row0(_mm_setr_ps(m.m[0][0], m.m[0][1], 0.0f, 0.0f)),
		m_row1(_mm_setr_ps(m.m[1][0], m.m[1][1], 0.0f, 0.0f)) { }

	Matrix2x2 Matrix2x2::operator+(const Matrix2x2& other) const
	{
		return {
			_mm_add_ps(m_row0, other.m_row0),
			_mm_add_ps(m_row1, other.m_row1)
		};
	}

	Matrix2x2 Matrix2x2::operator-(const Matrix2x2& other) const
	{
		return {
			_mm_sub_ps(m_row0, other.m_row0),
			_mm_sub_ps(m_row1, other.m_row1)
		};
	}

	Matrix2x2 Matrix2x2::operator*(FLOAT scalar) const
	{
		return {
			_mm_mul_ps(m_row0, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f)),
			_mm_mul_ps(m_row1, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f))
		};
	}

	Matrix2x2 Matrix2x2::operator*(const Matrix2x2& other) const
	{
		const __m128 m128Temp0 = _mm_setr_ps(other.m_row0.m128_f32[0], other.m_row1.m128_f32[0], 0.0f, 0.0f);
		const __m128 m128Temp1 = _mm_setr_ps(other.m_row0.m128_f32[1], other.m_row1.m128_f32[1], 0.0f, 0.0f);

		const FLOAT row00 = _mm_dp_ps(m_row0, m128Temp0, 0xff).m128_f32[0];
		const FLOAT row01 = _mm_dp_ps(m_row0, m128Temp1, 0xff).m128_f32[0];

		const FLOAT row10 = _mm_dp_ps(m_row1, m128Temp0, 0xff).m128_f32[0];
		const FLOAT row11 = _mm_dp_ps(m_row1, m128Temp1, 0xff).m128_f32[0];

		return {
			row00, row01,
			row10, row11
		};
	}

	Matrix2x2 Matrix2x2::operator/(FLOAT scalar) const
	{
		__m128 m128Temp0 = _mm_div_ps(m_row0, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f));
		__m128 m128Temp1 = _mm_div_ps(m_row1, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f));

		m128Temp0.m128_f32[2] = 0;
		m128Temp0.m128_f32[3] = 0;
		m128Temp1.m128_f32[2] = 0;
		m128Temp1.m128_f32[3] = 0;

		return { m128Temp0, m128Temp1 };
	}

	Matrix2x2 Matrix2x2::operator/(const Matrix2x2& other) const
	{
		__m128 m128Temp0 = _mm_div_ps(m_row0, other.m_row0);
		__m128 m128Temp1 = _mm_div_ps(m_row1, other.m_row1);

		m128Temp0.m128_f32[2] = 0;
		m128Temp0.m128_f32[3] = 0;
		m128Temp1.m128_f32[2] = 0;
		m128Temp1.m128_f32[3] = 0;

		return { m128Temp0, m128Temp1 };
	}

	Matrix2x2 Matrix2x2::operator==(const Matrix2x2& other) const
	{
		__m128 m128Temp0 = _mm_cmpeq_ps(m_row0, other.m_row0);
		__m128 m128Temp1 = _mm_cmpeq_ps(m_row1, other.m_row1);

		m128Temp0.m128_f32[2] = 0;
		m128Temp0.m128_f32[3] = 0;
		m128Temp1.m128_f32[2] = 0;
		m128Temp1.m128_f32[3] = 0;

		return { m128Temp0, m128Temp1 };
	}

	Matrix2x2& Matrix2x2::operator+=(const Matrix2x2& other)
	{
		m_row0 = _mm_add_ps(m_row0, other.m_row0);
		m_row1 = _mm_add_ps(m_row1, other.m_row1);

		return *this;
	}

	Matrix2x2& Matrix2x2::operator-=(const Matrix2x2& other)
	{
		m_row0 = _mm_sub_ps(m_row0, other.m_row0);
		m_row1 = _mm_sub_ps(m_row1, other.m_row1);

		return *this;
	}

	Matrix2x2& Matrix2x2::operator*=(FLOAT scalar)
	{
		m_row0 = _mm_mul_ps(m_row0, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f));
		m_row1 = _mm_mul_ps(m_row1, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f));

		return *this;
	}

	Matrix2x2& Matrix2x2::operator*=(const Matrix2x2& other)
	{
		*this = *this * other;
		return *this;
	}

	Matrix2x2& Matrix2x2::operator/=(FLOAT scalar)
	{
		m_row0 = _mm_div_ps(m_row0, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f));
		m_row1 = _mm_div_ps(m_row1, _mm_setr_ps(scalar, scalar, 0.0f, 0.0f));

		m_row0.m128_f32[2] = 0;
		m_row0.m128_f32[3] = 0;
		m_row1.m128_f32[2] = 0;
		m_row1.m128_f32[3] = 0;

		return *this;
	}

	Matrix2x2& Matrix2x2::operator/=(const Matrix2x2& other)
	{
		m_row0 = _mm_div_ps(m_row0, other.m_row0);
		m_row1 = _mm_div_ps(m_row1, other.m_row1);

		m_row0.m128_f32[2] = 0;
		m_row0.m128_f32[3] = 0;
		m_row1.m128_f32[2] = 0;
		m_row1.m128_f32[3] = 0;

		return *this;
	}

	Float2x2 Matrix2x2::GetMatrix() const
	{
		Float4x4 f4x4Temp;
		_mm_store_ps(&f4x4Temp.m[0][0], m_row0);
		_mm_store_ps(&f4x4Temp.m[1][0], m_row1);

		Float2x2 f2x2Result;
		memcpy(&f2x2Result.m[0][0], &f4x4Temp.m[0][0], 8);
		memcpy(&f2x2Result.m[1][0], &f4x4Temp.m[1][0], 8);

		return f2x2Result;
	}

	void Matrix2x2::SetMatrix(
		FLOAT m00, FLOAT m01,
		FLOAT m10, FLOAT m11)
	{
		m_row0 = _mm_setr_ps(m00, m01, 0.0f, 0.0f);
		m_row1 = _mm_setr_ps(m10, m11, 0.0f, 0.0f);
	}

	FLOAT Matrix2x2::Determinant() const
	{
		const FLOAT f0 = m_row0.m128_f32[0] * m_row1.m128_f32[1];
		const FLOAT f1 = m_row0.m128_f32[1] * m_row1.m128_f32[0];

		return f0 - f1;
	}

	Matrix2x2 Matrix2x2::Inverse() const
	{
		const Matrix2x2 matrixTemp = Matrix2x2(
			m_row1.m128_f32[1], -m_row0.m128_f32[1],
			-m_row0.m128_f32[0], m_row0.m128_f32[0]);

		return matrixTemp * (1 / Determinant());
	}

	Matrix2x2 Matrix2x2::Transpose() const
	{
		const __m128 m128Temp0 = _mm_unpacklo_ps(m_row0, m_row1);
		const __m128 m128Temp1 = _mm_set_ps1(0.0f);

		return {
			_mm_movelh_ps(m128Temp0, m128Temp1),
			_mm_movehl_ps(m128Temp1, m128Temp0)
		};
	}

	const Matrix2x2 Matrix2x2::Identity = Matrix2x2(
		1.0f, 0.0f,
		0.0f, 1.0f);

	Vector2 Matrix2x2::PreMultiVector2(const Vector2& vector, const Matrix2x2& matrix)
	{
		const __m128 m128Temp0 = _mm_setr_ps(matrix.m_row0.m128_f32[0], matrix.m_row1.m128_f32[0], 0.0f, 0.0f);
		const __m128 m128Temp1 = _mm_setr_ps(matrix.m_row0.m128_f32[1], matrix.m_row1.m128_f32[1], 0.0f, 0.0f);

		const FLOAT x = _mm_dp_ps(vector.m_vector, m128Temp0, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(vector.m_vector, m128Temp1, 0xff).m128_f32[0];

		return { x, y };
	}

	Vector2 Matrix2x2::PostMultiVector2(const Matrix2x2& matrix, const Vector2& vector)
	{
		const FLOAT x = _mm_dp_ps(matrix.m_row0, vector.m_vector, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(matrix.m_row1, vector.m_vector, 0xff).m128_f32[0];

		return { x, y };
	}

	Matrix2x2 Matrix2x2::MultiMatrix(const Matrix2x2& lhs, const Matrix2x2& rhs)
	{
		return {
			_mm_mul_ps(lhs.m_row0, rhs.m_row0),
			_mm_mul_ps(lhs.m_row1, rhs.m_row1)
		};
	}

	Matrix2x2::Matrix2x2(const __m128& mRow0, const __m128& mRow1) :
		m_row0(mRow0), m_row1(mRow1) { }
}

#include "../Matrix3x3.h"
#include "../Matrix2x2.h"
#include "../Matrix4x4.h"
#include "../Vector3.h"

namespace XusoryEngine
{
	Float3x3::Float3x3(
		FLOAT m00, FLOAT m01, FLOAT m02,
		FLOAT m10, FLOAT m11, FLOAT m12,
		FLOAT m20, FLOAT m21, FLOAT m22)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;

		m[0][0] = m10;
		m[0][0] = m11;
		m[0][0] = m12;

		m[0][0] = m20;
		m[0][0] = m21;
		m[0][0] = m22;
	}

	Matrix3x3::Matrix3x3() :
		m_row0(_mm_setzero_ps()),
		m_row1(_mm_setzero_ps()),
		m_row2(_mm_setzero_ps()) { }

	Matrix3x3::Matrix3x3(
		FLOAT m00, FLOAT m01, FLOAT m02,
		FLOAT m10, FLOAT m11, FLOAT m12,
		FLOAT m20, FLOAT m21, FLOAT m22) :
		m_row0(_mm_setr_ps(m00, m01, m02, 0.0f)),
		m_row1(_mm_setr_ps(m10, m11, m12, 0.0f)),
		m_row2(_mm_setr_ps(m20, m21, m22, 0.0f)) { }

	Matrix3x3::Matrix3x3(FLOAT scalar) :
		m_row0(_mm_setr_ps(scalar, scalar, scalar, 0.0f)),
		m_row1(_mm_setr_ps(scalar, scalar, scalar, 0.0f)),
		m_row2(_mm_setr_ps(scalar, scalar, scalar, 0.0f)) { }

	Matrix3x3::Matrix3x3(const Float3x3& m) :
		m_row0(_mm_setr_ps(m.m[0][0], m.m[0][1], m.m[0][2], 0.0f)),
		m_row1(_mm_setr_ps(m.m[1][0], m.m[1][1], m.m[1][2], 0.0f)),
		m_row2(_mm_setr_ps(m.m[2][0], m.m[2][1], m.m[2][2], 0.0f)) { }

	Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const
	{
		return {
			_mm_add_ps(m_row0, other.m_row0),
			_mm_add_ps(m_row1, other.m_row1),
			_mm_add_ps(m_row2, other.m_row2)
		};
	}

	Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const
	{
		return {
			_mm_sub_ps(m_row0, other.m_row0),
			_mm_sub_ps(m_row1, other.m_row1),
			_mm_sub_ps(m_row2, other.m_row2)
		};
	}

	Matrix3x3 Matrix3x3::operator*(FLOAT scalar) const
	{
		return {
			_mm_mul_ps(m_row0, _mm_setr_ps(scalar, scalar, scalar, 0.0f)),
			_mm_mul_ps(m_row1, _mm_setr_ps(scalar, scalar, scalar, 0.0f)),
			_mm_mul_ps(m_row2, _mm_setr_ps(scalar, scalar, scalar, 0.0f))
		};
	}

	Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const
	{
		const __m128 m128Temp0 = _mm_setr_ps(other.m_row0.m128_f32[0], other.m_row1.m128_f32[0], other.m_row2.m128_f32[0], 0.0f);
		const __m128 m128Temp1 = _mm_setr_ps(other.m_row0.m128_f32[1], other.m_row1.m128_f32[1], other.m_row2.m128_f32[1], 0.0f);
		const __m128 m128Temp2 = _mm_setr_ps(other.m_row0.m128_f32[2], other.m_row1.m128_f32[2], other.m_row2.m128_f32[2], 0.0f);

		const FLOAT row00 = _mm_dp_ps(m_row0, m128Temp0, 0xff).m128_f32[0];
		const FLOAT row01 = _mm_dp_ps(m_row0, m128Temp1, 0xff).m128_f32[0];
		const FLOAT row02 = _mm_dp_ps(m_row0, m128Temp2, 0xff).m128_f32[0];

		const FLOAT row10 = _mm_dp_ps(m_row1, m128Temp0, 0xff).m128_f32[0];
		const FLOAT row11 = _mm_dp_ps(m_row1, m128Temp1, 0xff).m128_f32[0];
		const FLOAT row12 = _mm_dp_ps(m_row1, m128Temp2, 0xff).m128_f32[0];

		const FLOAT row20 = _mm_dp_ps(m_row2, m128Temp0, 0xff).m128_f32[0];
		const FLOAT row21 = _mm_dp_ps(m_row2, m128Temp1, 0xff).m128_f32[0];
		const FLOAT row22 = _mm_dp_ps(m_row2, m128Temp2, 0xff).m128_f32[0];

		return {
			row00, row01, row02,
			row10, row11, row12,
			row20, row21, row22
		};
	}

	Matrix3x3 Matrix3x3::operator/(FLOAT scalar) const
	{
		__m128 m128Temp0 = _mm_div_ps(m_row0, _mm_setr_ps(scalar, scalar, scalar, 0.0f));
		__m128 m128Temp1 = _mm_div_ps(m_row1, _mm_setr_ps(scalar, scalar, scalar, 0.0f));
		__m128 m128Temp2 = _mm_div_ps(m_row2, _mm_setr_ps(scalar, scalar, scalar, 0.0f));

		m128Temp0.m128_f32[3] = 0;
		m128Temp1.m128_f32[3] = 0;
		m128Temp2.m128_f32[3] = 0;

		return { m128Temp0, m128Temp1, m128Temp2 };
	}

	Matrix3x3 Matrix3x3::operator/(const Matrix3x3& other) const
	{
		__m128 m128Temp0 = _mm_div_ps(m_row0, other.m_row0);
		__m128 m128Temp1 = _mm_div_ps(m_row1, other.m_row1);
		__m128 m128Temp2 = _mm_div_ps(m_row2, other.m_row2);

		m128Temp0.m128_f32[3] = 0;
		m128Temp1.m128_f32[3] = 0;
		m128Temp2.m128_f32[3] = 0;

		return { m128Temp0, m128Temp1, m128Temp2 };
	}

	Matrix3x3 Matrix3x3::operator==(const Matrix3x3& other) const
	{
		__m128 m128Temp0 = _mm_cmpeq_ps(m_row0, other.m_row0);
		__m128 m128Temp1 = _mm_cmpeq_ps(m_row1, other.m_row1);
		__m128 m128Temp2 = _mm_cmpeq_ps(m_row2, other.m_row2);

		m128Temp0.m128_f32[3] = 0;
		m128Temp1.m128_f32[3] = 0;
		m128Temp2.m128_f32[3] = 0;

		return { m128Temp0, m128Temp1, m128Temp2 };
	}

	Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other)
	{
		m_row0 = _mm_add_ps(m_row0, other.m_row0);
		m_row1 = _mm_add_ps(m_row1, other.m_row1);
		m_row2 = _mm_add_ps(m_row2, other.m_row2);

		return *this;
	}

	Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other)
	{
		m_row0 = _mm_sub_ps(m_row0, other.m_row0);
		m_row1 = _mm_sub_ps(m_row1, other.m_row1);
		m_row2 = _mm_sub_ps(m_row2, other.m_row2);

		return *this;
	}

	Matrix3x3& Matrix3x3::operator*=(FLOAT scalar)
	{
		m_row0 = _mm_mul_ps(m_row0, _mm_setr_ps(scalar, scalar, scalar, 0.0f));
		m_row1 = _mm_mul_ps(m_row1, _mm_setr_ps(scalar, scalar, scalar, 0.0f));
		m_row2 = _mm_mul_ps(m_row2, _mm_setr_ps(scalar, scalar, scalar, 0.0f));

		return *this;
	}

	Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& other)
	{
		*this = *this * other;
		return *this;
	}

	Matrix3x3& Matrix3x3::operator/=(FLOAT scalar)
	{
		m_row0 = _mm_div_ps(m_row0, _mm_setr_ps(scalar, scalar, scalar, 0.0f));
		m_row1 = _mm_div_ps(m_row1, _mm_setr_ps(scalar, scalar, scalar, 0.0f));
		m_row2 = _mm_div_ps(m_row2, _mm_setr_ps(scalar, scalar, scalar, 0.0f));

		m_row0.m128_f32[3] = 0;
		m_row1.m128_f32[3] = 0;
		m_row2.m128_f32[3] = 0;

		return *this;
	}

	Matrix3x3& Matrix3x3::operator/=(const Matrix3x3& other)
	{
		m_row0 = _mm_div_ps(m_row0, other.m_row0);
		m_row1 = _mm_div_ps(m_row1, other.m_row1);
		m_row2 = _mm_div_ps(m_row2, other.m_row2);

		m_row0.m128_f32[3] = 0;
		m_row1.m128_f32[3] = 0;
		m_row2.m128_f32[3] = 0;

		return *this;
	}

	Float3x3 Matrix3x3::GetMatrix() const
	{
		Float4x4 f4x4Temp;
		_mm_store_ps(&f4x4Temp.m[0][0], m_row0);
		_mm_store_ps(&f4x4Temp.m[1][0], m_row1);
		_mm_store_ps(&f4x4Temp.m[2][0], m_row2);

		Float3x3 f3x3Result;
		memcpy(&f3x3Result.m[0][0], &f4x4Temp.m[0][0], 12);
		memcpy(&f3x3Result.m[1][0], &f4x4Temp.m[1][0], 12);
		memcpy(&f3x3Result.m[2][0], &f4x4Temp.m[2][0], 12);

		return f3x3Result;
	}

	void Matrix3x3::SetMatrix(
		FLOAT m00, FLOAT m01, FLOAT m02,
		FLOAT m10, FLOAT m11, FLOAT m12,
		FLOAT m20, FLOAT m21, FLOAT m22)
	{
		m_row0 = _mm_setr_ps(m00, m01, m02, 0.0f);
		m_row1 = _mm_setr_ps(m10, m11, m12, 0.0f);
		m_row2 = _mm_setr_ps(m20, m21, m22, 0.0f);
	}

	FLOAT Matrix3x3::Determinant() const
	{
		const FLOAT f0 = m_row0.m128_f32[0] * m_row1.m128_f32[1] * m_row2.m128_f32[2];
		const FLOAT f1 = m_row0.m128_f32[1] * m_row1.m128_f32[2] * m_row2.m128_f32[0];
		const FLOAT f2 = m_row0.m128_f32[2] * m_row1.m128_f32[0] * m_row2.m128_f32[1];

		const FLOAT f3 = m_row0.m128_f32[2] * m_row1.m128_f32[1] * m_row2.m128_f32[0];
		const FLOAT f4 = m_row0.m128_f32[0] * m_row1.m128_f32[2] * m_row2.m128_f32[1];
		const FLOAT f5 = m_row0.m128_f32[1] * m_row1.m128_f32[0] * m_row2.m128_f32[2];
		return f0 + f1 + f2 - f3 - f4 - f5;
	}

	Matrix3x3 Matrix3x3::Inverse() const
	{
		const FLOAT minor00 = m_row1.m128_f32[1] * m_row2.m128_f32[2] - m_row1.m128_f32[2] * m_row2.m128_f32[1];
		const FLOAT minor01 = m_row1.m128_f32[0] * m_row2.m128_f32[2] - m_row1.m128_f32[2] * m_row2.m128_f32[0];
		const FLOAT minor02 = m_row1.m128_f32[0] * m_row2.m128_f32[1] - m_row1.m128_f32[1] * m_row2.m128_f32[0];

		const FLOAT minor10 = m_row0.m128_f32[1] * m_row2.m128_f32[2] - m_row0.m128_f32[2] * m_row2.m128_f32[1];
		const FLOAT minor11 = m_row0.m128_f32[0] * m_row2.m128_f32[2] - m_row0.m128_f32[2] * m_row2.m128_f32[0];
		const FLOAT minor12 = m_row0.m128_f32[0] * m_row2.m128_f32[1] - m_row0.m128_f32[1] * m_row2.m128_f32[0];

		const FLOAT minor20 = m_row0.m128_f32[1] * m_row1.m128_f32[2] - m_row0.m128_f32[2] * m_row1.m128_f32[1];
		const FLOAT minor21 = m_row0.m128_f32[0] * m_row1.m128_f32[2] - m_row0.m128_f32[2] * m_row1.m128_f32[0];
		const FLOAT minor22 = m_row0.m128_f32[0] * m_row1.m128_f32[1] - m_row0.m128_f32[1] * m_row1.m128_f32[0];

		const Matrix3x3 adjMat = Matrix3x3(
			minor00, -minor10, minor20,
			-minor01, minor11, -minor21,
			minor02, -minor12, minor22);

		return adjMat * (1 / Determinant());
	}

	Matrix3x3 Matrix3x3::Transpose() const
	{
		const __m128 m128Temp0 = _mm_unpacklo_ps(m_row0, m_row1);
		const __m128 m128Temp1 = _mm_unpacklo_ps(m_row2, _mm_set_ps1(0.0f));
		const __m128 m128Temp2 = _mm_unpackhi_ps(m_row0, m_row1);
		const __m128 m128Temp3 = _mm_unpackhi_ps(m_row2, _mm_set_ps1(0.0f));

		return {
			_mm_movelh_ps(m128Temp0, m128Temp1),
			_mm_movehl_ps(m128Temp1, m128Temp0),
			_mm_movelh_ps(m128Temp2, m128Temp3)
		};
	}

	Vector3 Matrix3x3::PreMultiVector3(const Vector3& vector, const Matrix3x3& matrix)
	{
		const __m128 m128Temp0 = _mm_setr_ps(matrix.m_row0.m128_f32[0], matrix.m_row1.m128_f32[0], matrix.m_row2.m128_f32[0], 0.0f);
		const __m128 m128Temp1 = _mm_setr_ps(matrix.m_row0.m128_f32[1], matrix.m_row1.m128_f32[1], matrix.m_row2.m128_f32[1], 0.0f);
		const __m128 m128Temp2 = _mm_setr_ps(matrix.m_row0.m128_f32[2], matrix.m_row1.m128_f32[2], matrix.m_row2.m128_f32[2], 0.0f);

		const FLOAT x = _mm_dp_ps(vector.m_vector, m128Temp0, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(vector.m_vector, m128Temp1, 0xff).m128_f32[0];
		const FLOAT z = _mm_dp_ps(vector.m_vector, m128Temp2, 0xff).m128_f32[0];

		return { x, y, z };
	}

	Vector3 Matrix3x3::PostMultiVector3(const Matrix3x3& matrix, const Vector3& vector)
	{
		const FLOAT x = _mm_dp_ps(matrix.m_row0, vector.m_vector, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(matrix.m_row1, vector.m_vector, 0xff).m128_f32[0];
		const FLOAT z = _mm_dp_ps(matrix.m_row2, vector.m_vector, 0xff).m128_f32[0];

		return { x, y, z };
	}

	Matrix3x3 Matrix3x3::MultiMatrix(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		return {
			_mm_mul_ps(lhs.m_row0, rhs.m_row0),
			_mm_mul_ps(lhs.m_row1, rhs.m_row1),
			_mm_mul_ps(lhs.m_row2, rhs.m_row2)
		};
	}

	Matrix3x3::Matrix3x3(const __m128& mRow0, const __m128& mRow1, const __m128& mRow2) :
		m_row0(mRow0), m_row1(mRow1), m_row2(mRow2) { }
}

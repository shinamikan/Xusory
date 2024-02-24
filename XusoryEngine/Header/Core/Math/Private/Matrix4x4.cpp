#include <cmath>

#include "../Matrix4x4.h" 
#include "../Matrix3x3.h"
#include "../Vector3.h"
#include "../Vector4.h"

#define GetDet3(mat00, mat01, mat02,											\
				mat10, mat11, mat12,											\
				mat20, mat21, mat22)											\
	(mat00 * mat11 * mat22 + mat01 * mat12 * mat20 + mat02 * mat10 * mat21 -	\
	mat02 * mat11 * mat20 - mat00 * mat12 * mat21 - mat01 * mat10 * mat22)

namespace XusoryEngine
{
	Float4x4::Float4x4(
		FLOAT m00, FLOAT m01, FLOAT m02, FLOAT m03,
		FLOAT m10, FLOAT m11, FLOAT m12, FLOAT m13,
		FLOAT m20, FLOAT m21, FLOAT m22, FLOAT m23,
		FLOAT m30, FLOAT m31, FLOAT m32, FLOAT m33)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;

		m[0][0] = m10;
		m[0][0] = m11;
		m[0][0] = m12;
		m[0][0] = m13;

		m[0][0] = m20;
		m[0][0] = m21;
		m[0][0] = m22;
		m[0][0] = m23;

		m[0][0] = m30;
		m[0][0] = m31;
		m[0][0] = m32;
		m[0][0] = m33;
	}

	Matrix4x4::Matrix4x4() :
		m_row0(_mm_setzero_ps()), m_row1(_mm_setzero_ps()),
		m_row2(_mm_setzero_ps()), m_row3(_mm_setzero_ps()) { }

	Matrix4x4::Matrix4x4(
		FLOAT m00, FLOAT m01, FLOAT m02, FLOAT m03,
		FLOAT m10, FLOAT m11, FLOAT m12, FLOAT m13,
		FLOAT m20, FLOAT m21, FLOAT m22, FLOAT m23,
		FLOAT m30, FLOAT m31, FLOAT m32, FLOAT m33) :
		m_row0(_mm_setr_ps(m00, m01, m02, m03)),
		m_row1(_mm_setr_ps(m10, m11, m12, m13)),
		m_row2(_mm_setr_ps(m20, m21, m22, m23)),
		m_row3(_mm_setr_ps(m30, m31, m32, m33)) { }

	Matrix4x4::Matrix4x4(FLOAT scalar) :
		m_row0(_mm_set_ps1(scalar)), m_row1(_mm_set_ps1(scalar)),
		m_row2(_mm_set_ps1(scalar)), m_row3(_mm_set_ps1(scalar)) { }

	Matrix4x4::Matrix4x4(const Float4x4& m) :
		m_row0(_mm_setr_ps(m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3])),
		m_row1(_mm_setr_ps(m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3])),
		m_row2(_mm_setr_ps(m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3])),
		m_row3(_mm_setr_ps(m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3])) { }

	Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const
	{
		return { _mm_add_ps(m_row0, other.m_row0),
			_mm_add_ps(m_row1, other.m_row1),
			_mm_add_ps(m_row2, other.m_row2),
			_mm_add_ps(m_row3, other.m_row3)
		};
	}

	Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const
	{
		return {
			_mm_sub_ps(m_row0, other.m_row0),
			_mm_sub_ps(m_row1, other.m_row1),
			_mm_sub_ps(m_row2, other.m_row2),
			_mm_sub_ps(m_row3, other.m_row3)
		};
	}

	Matrix4x4 Matrix4x4::operator*(FLOAT scalar) const
	{
		return {
			_mm_mul_ps(m_row0, _mm_set_ps1(scalar)),
			_mm_mul_ps(m_row1, _mm_set_ps1(scalar)),
			_mm_mul_ps(m_row2, _mm_set_ps1(scalar)),
			_mm_mul_ps(m_row3, _mm_set_ps1(scalar))
		};
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const
	{
		const __m128 m128Temp0 = _mm_setr_ps(other.m_row0.m128_f32[0], other.m_row1.m128_f32[0], other.m_row2.m128_f32[0], other.m_row3.m128_f32[0]);
		const __m128 m128Temp1 = _mm_setr_ps(other.m_row0.m128_f32[1], other.m_row1.m128_f32[1], other.m_row2.m128_f32[1], other.m_row3.m128_f32[1]);
		const __m128 m128Temp2 = _mm_setr_ps(other.m_row0.m128_f32[2], other.m_row1.m128_f32[2], other.m_row2.m128_f32[2], other.m_row3.m128_f32[2]);
		const __m128 m128Temp3 = _mm_setr_ps(other.m_row0.m128_f32[2], other.m_row1.m128_f32[2], other.m_row2.m128_f32[2], other.m_row3.m128_f32[3]);

		const FLOAT row00 = _mm_dp_ps(m_row0, m128Temp0, 0xff).m128_f32[0];
		const FLOAT row01 = _mm_dp_ps(m_row0, m128Temp1, 0xff).m128_f32[0];
		const FLOAT row02 = _mm_dp_ps(m_row0, m128Temp2, 0xff).m128_f32[0];
		const FLOAT row03 = _mm_dp_ps(m_row0, m128Temp3, 0xff).m128_f32[0];

		const FLOAT row10 = _mm_dp_ps(m_row1, m128Temp0, 0xff).m128_f32[0];
		const FLOAT row11 = _mm_dp_ps(m_row1, m128Temp1, 0xff).m128_f32[0];
		const FLOAT row12 = _mm_dp_ps(m_row1, m128Temp2, 0xff).m128_f32[0];
		const FLOAT row13 = _mm_dp_ps(m_row1, m128Temp3, 0xff).m128_f32[0];

		const FLOAT row20 = _mm_dp_ps(m_row2, m128Temp0, 0xff).m128_f32[0];
		const FLOAT row21 = _mm_dp_ps(m_row2, m128Temp1, 0xff).m128_f32[0];
		const FLOAT row22 = _mm_dp_ps(m_row2, m128Temp2, 0xff).m128_f32[0];
		const FLOAT row23 = _mm_dp_ps(m_row2, m128Temp3, 0xff).m128_f32[0];

		const FLOAT row30 = _mm_dp_ps(m_row3, m128Temp0, 0xff).m128_f32[0];
		const FLOAT row31 = _mm_dp_ps(m_row3, m128Temp1, 0xff).m128_f32[0];
		const FLOAT row32 = _mm_dp_ps(m_row3, m128Temp2, 0xff).m128_f32[0];
		const FLOAT row33 = _mm_dp_ps(m_row3, m128Temp3, 0xff).m128_f32[0];

		return {
			row00, row01, row02, row03,
			row10, row11, row12, row13,
			row20, row21, row22, row23,
			row30, row31, row32, row33 };
	}

	Matrix4x4 Matrix4x4::operator/(FLOAT scalar) const
	{
		return {
			_mm_div_ps(m_row0, _mm_set_ps1(scalar)),
			_mm_div_ps(m_row1, _mm_set_ps1(scalar)),
			_mm_div_ps(m_row2, _mm_set_ps1(scalar)),
			_mm_div_ps(m_row3, _mm_set_ps1(scalar))
		};
	}

	Matrix4x4 Matrix4x4::operator/(const Matrix4x4& other) const
	{
		return {
			_mm_div_ps(m_row0, other.m_row0),
			_mm_div_ps(m_row1, other.m_row1),
			_mm_div_ps(m_row2, other.m_row2),
			_mm_div_ps(m_row3, other.m_row3)
		};
	}

	Matrix4x4 Matrix4x4::operator==(const Matrix4x4& other) const
	{
		return {
			_mm_cmpeq_ps(m_row0, other.m_row0),
			_mm_cmpeq_ps(m_row1, other.m_row1),
			_mm_cmpeq_ps(m_row2, other.m_row2),
			_mm_cmpeq_ps(m_row3, other.m_row3)
		};
	}

	Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other)
	{
		m_row0 = _mm_add_ps(m_row0, other.m_row0);
		m_row1 = _mm_add_ps(m_row1, other.m_row1);
		m_row2 = _mm_add_ps(m_row2, other.m_row2);
		m_row3 = _mm_add_ps(m_row3, other.m_row3);

		return *this;
	}

	Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other)
	{
		m_row0 = _mm_sub_ps(m_row0, other.m_row0);
		m_row1 = _mm_sub_ps(m_row1, other.m_row1);
		m_row2 = _mm_sub_ps(m_row2, other.m_row2);
		m_row3 = _mm_sub_ps(m_row3, other.m_row3);

		return *this;
	}

	Matrix4x4& Matrix4x4::operator*=(FLOAT scalar)
	{
		m_row0 = _mm_mul_ps(m_row0, _mm_set_ps1(scalar));
		m_row1 = _mm_mul_ps(m_row1, _mm_set_ps1(scalar));
		m_row2 = _mm_mul_ps(m_row2, _mm_set_ps1(scalar));
		m_row3 = _mm_mul_ps(m_row3, _mm_set_ps1(scalar));

		return *this;
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other)
	{
		*this = *this * other;
		return *this;
	}

	Matrix4x4& Matrix4x4::operator/=(FLOAT scalar)
	{
		m_row0 = _mm_div_ps(m_row0, _mm_set_ps1(scalar));
		m_row1 = _mm_div_ps(m_row1, _mm_set_ps1(scalar));
		m_row2 = _mm_div_ps(m_row2, _mm_set_ps1(scalar));
		m_row3 = _mm_div_ps(m_row3, _mm_set_ps1(scalar));

		return *this;
	}

	Matrix4x4& Matrix4x4::operator/=(const Matrix4x4& other)
	{
		m_row0 = _mm_div_ps(m_row0, other.m_row0);
		m_row1 = _mm_div_ps(m_row1, other.m_row1);
		m_row2 = _mm_div_ps(m_row2, other.m_row2);
		m_row3 = _mm_div_ps(m_row3, other.m_row3);

		return *this;
	}

	Float4x4 Matrix4x4::GetMatrix() const
	{
		Float4x4 f4x4Temp;
		_mm_store_ps(&f4x4Temp.m[0][0], m_row0);
		_mm_store_ps(&f4x4Temp.m[1][0], m_row1);
		_mm_store_ps(&f4x4Temp.m[2][0], m_row2);
		_mm_store_ps(&f4x4Temp.m[3][0], m_row3);

		return f4x4Temp;
	}

	void Matrix4x4::SetMatrix(
		FLOAT m00, FLOAT m01, FLOAT m02, FLOAT m03,
		FLOAT m10, FLOAT m11, FLOAT m12, FLOAT m13,
		FLOAT m20, FLOAT m21, FLOAT m22, FLOAT m23,
		FLOAT m30, FLOAT m31, FLOAT m32, FLOAT m33)
	{
		m_row0 = _mm_setr_ps(m00, m01, m02, m03);
		m_row1 = _mm_setr_ps(m10, m11, m12, m13);
		m_row2 = _mm_setr_ps(m20, m21, m22, m23);
		m_row3 = _mm_setr_ps(m30, m31, m32, m33);
	}

	FLOAT Matrix4x4::Determinant() const
	{
		const FLOAT m10 = m_row1.m128_f32[0];
		const FLOAT m11 = m_row1.m128_f32[1];
		const FLOAT m12 = m_row1.m128_f32[2];
		const FLOAT m13 = m_row1.m128_f32[3];

		const FLOAT m20 = m_row2.m128_f32[0];
		const FLOAT m21 = m_row2.m128_f32[1];
		const FLOAT m22 = m_row2.m128_f32[2];
		const FLOAT m23 = m_row2.m128_f32[3];

		const FLOAT m30 = m_row3.m128_f32[0];
		const FLOAT m31 = m_row3.m128_f32[1];
		const FLOAT m32 = m_row3.m128_f32[2];
		const FLOAT m33 = m_row3.m128_f32[3];

		const FLOAT f0 = m_row0.m128_f32[0] * GetDet3(m11, m12, m13, m21, m22, m23, m31, m32, m33);
		const FLOAT f1 = m_row0.m128_f32[1] * GetDet3(m10, m12, m13, m20, m22, m23, m30, m32, m33);
		const FLOAT f2 = m_row0.m128_f32[2] * GetDet3(m10, m11, m13, m20, m21, m23, m30, m31, m33);
		const FLOAT f3 = m_row0.m128_f32[3] * GetDet3(m10, m11, m12, m20, m21, m22, m30, m31, m32);

		return f0 - f1 + f2 - f3;
	}

	Matrix4x4 Matrix4x4::Inverse() const
	{
		const FLOAT m00 = m_row0.m128_f32[0];
		const FLOAT m01 = m_row0.m128_f32[1];
		const FLOAT m02 = m_row0.m128_f32[2];
		const FLOAT m03 = m_row0.m128_f32[3];

		const FLOAT m10 = m_row1.m128_f32[0];
		const FLOAT m11 = m_row1.m128_f32[1];
		const FLOAT m12 = m_row1.m128_f32[2];
		const FLOAT m13 = m_row1.m128_f32[3];

		const FLOAT m20 = m_row2.m128_f32[0];
		const FLOAT m21 = m_row2.m128_f32[1];
		const FLOAT m22 = m_row2.m128_f32[2];
		const FLOAT m23 = m_row2.m128_f32[3];

		const FLOAT m30 = m_row3.m128_f32[0];
		const FLOAT m31 = m_row3.m128_f32[1];
		const FLOAT m32 = m_row3.m128_f32[2];
		const FLOAT m33 = m_row3.m128_f32[3];

		const FLOAT minor00 = GetDet3(m11, m12, m13, m21, m22, m23, m31, m32, m33);
		const FLOAT minor01 = GetDet3(m10, m12, m13, m20, m22, m23, m30, m32, m33);
		const FLOAT minor02 = GetDet3(m10, m11, m13, m20, m21, m23, m30, m31, m33);
		const FLOAT minor03 = GetDet3(m10, m11, m12, m20, m21, m22, m30, m31, m32);

		const FLOAT minor10 = GetDet3(m01, m02, m03, m21, m22, m23, m31, m32, m33);
		const FLOAT minor11 = GetDet3(m00, m02, m03, m20, m22, m23, m30, m32, m33);
		const FLOAT minor12 = GetDet3(m00, m01, m03, m20, m21, m23, m30, m31, m33);
		const FLOAT minor13 = GetDet3(m00, m01, m02, m20, m21, m22, m30, m31, m32);

		const FLOAT minor20 = GetDet3(m01, m02, m03, m11, m12, m13, m31, m32, m33);
		const FLOAT minor21 = GetDet3(m00, m02, m03, m10, m12, m13, m30, m32, m33);
		const FLOAT minor22 = GetDet3(m00, m01, m03, m10, m11, m13, m30, m31, m33);
		const FLOAT minor23 = GetDet3(m00, m01, m02, m10, m11, m12, m30, m31, m32);

		const FLOAT minor30 = GetDet3(m01, m02, m03, m11, m12, m13, m21, m22, m23);
		const FLOAT minor31 = GetDet3(m00, m02, m03, m10, m12, m13, m20, m22, m23);
		const FLOAT minor32 = GetDet3(m00, m01, m03, m10, m11, m13, m20, m21, m23);
		const FLOAT minor33 = GetDet3(m00, m01, m02, m10, m11, m12, m20, m21, m22);

		const Matrix4x4 adjMat = Matrix4x4(
			minor00, -minor10, minor20, -minor30,
			-minor01, minor11, -minor21, minor31,
			minor02, -minor12, minor22, -minor32,
			-minor03, minor13, -minor23, minor33);

		return adjMat * (1 / (m00 * minor00 - m01 * minor01 + m02 * minor02 - m03 * minor03));
	}

	Matrix4x4 Matrix4x4::Transpose() const
	{
		const __m128 m128Temp0 = _mm_unpacklo_ps(m_row0, m_row1);
		const __m128 m128Temp1 = _mm_unpacklo_ps(m_row2, m_row3);
		const __m128 m128Temp2 = _mm_unpackhi_ps(m_row0, m_row1);
		const __m128 m128Temp3 = _mm_unpackhi_ps(m_row2, m_row3);

		return {
			_mm_movelh_ps(m128Temp0, m128Temp1),
			_mm_movehl_ps(m128Temp1, m128Temp0),
			_mm_movelh_ps(m128Temp2, m128Temp3),
			_mm_movehl_ps(m128Temp3, m128Temp2)
		};
	}

	Vector3 Matrix4x4::PreTransPoint3(const Vector3& vector, const Matrix4x4& matrix)
	{
		const __m128 m128Temp = _mm_setr_ps(vector.m_vector.m128_f32[0], vector.m_vector.m128_f32[1], vector.m_vector.m128_f32[2], 1.0f);

		const __m128 m128Temp0 = _mm_setr_ps(matrix.m_row0.m128_f32[0], matrix.m_row1.m128_f32[0], matrix.m_row2.m128_f32[0], matrix.m_row3.m128_f32[0]);
		const __m128 m128Temp1 = _mm_setr_ps(matrix.m_row0.m128_f32[1], matrix.m_row1.m128_f32[1], matrix.m_row2.m128_f32[1], matrix.m_row3.m128_f32[1]);
		const __m128 m128Temp2 = _mm_setr_ps(matrix.m_row0.m128_f32[2], matrix.m_row1.m128_f32[2], matrix.m_row2.m128_f32[2], matrix.m_row3.m128_f32[2]);

		const FLOAT x = _mm_dp_ps(m128Temp, m128Temp0, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(m128Temp, m128Temp1, 0xff).m128_f32[0];
		const FLOAT z = _mm_dp_ps(m128Temp, m128Temp2, 0xff).m128_f32[0];

		return { x, y, z };
	}

	Vector3 Matrix4x4::PreTransVector3(const Vector3& vector, const Matrix4x4& matrix)
	{
		const __m128 m128Temp0 = _mm_setr_ps(matrix.m_row0.m128_f32[0], matrix.m_row1.m128_f32[0], matrix.m_row2.m128_f32[0], matrix.m_row3.m128_f32[0]);
		const __m128 m128Temp1 = _mm_setr_ps(matrix.m_row0.m128_f32[1], matrix.m_row1.m128_f32[1], matrix.m_row2.m128_f32[1], matrix.m_row3.m128_f32[1]);
		const __m128 m128Temp2 = _mm_setr_ps(matrix.m_row0.m128_f32[2], matrix.m_row1.m128_f32[2], matrix.m_row2.m128_f32[2], matrix.m_row3.m128_f32[2]);

		const FLOAT x = _mm_dp_ps(vector.m_vector, m128Temp0, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(vector.m_vector, m128Temp1, 0xff).m128_f32[0];
		const FLOAT z = _mm_dp_ps(vector.m_vector, m128Temp2, 0xff).m128_f32[0];

		return { x, y, z };
	}

	Vector3 Matrix4x4::PostTransPoint3(const Matrix4x4& matrix, const Vector3& vector)
	{
		const __m128 m128Temp = _mm_setr_ps(vector.m_vector.m128_f32[0], vector.m_vector.m128_f32[1], vector.m_vector.m128_f32[2], 1.0f);

		const FLOAT x = _mm_dp_ps(matrix.m_row0, m128Temp, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(matrix.m_row1, m128Temp, 0xff).m128_f32[0];
		const FLOAT z = _mm_dp_ps(matrix.m_row2, m128Temp, 0xff).m128_f32[0];

		return { x, y, z };
	}

	Vector3 Matrix4x4::PostTransVector3(const Matrix4x4& matrix, const Vector3& vector)
	{
		const FLOAT x = _mm_dp_ps(matrix.m_row0, vector.m_vector, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(matrix.m_row1, vector.m_vector, 0xff).m128_f32[0];
		const FLOAT z = _mm_dp_ps(matrix.m_row2, vector.m_vector, 0xff).m128_f32[0];

		return { x, y, z };
	}

	Vector4 Matrix4x4::PreMultiVector4(const Vector4& vector, const Matrix4x4& matrix)
	{
		const __m128 m128Temp0 = _mm_setr_ps(matrix.m_row0.m128_f32[0], matrix.m_row1.m128_f32[0], matrix.m_row2.m128_f32[0], matrix.m_row3.m128_f32[0]);
		const __m128 m128Temp1 = _mm_setr_ps(matrix.m_row0.m128_f32[1], matrix.m_row1.m128_f32[1], matrix.m_row2.m128_f32[1], matrix.m_row3.m128_f32[1]);
		const __m128 m128Temp2 = _mm_setr_ps(matrix.m_row0.m128_f32[2], matrix.m_row1.m128_f32[2], matrix.m_row2.m128_f32[2], matrix.m_row3.m128_f32[2]);
		const __m128 m128Temp3 = _mm_setr_ps(matrix.m_row0.m128_f32[3], matrix.m_row1.m128_f32[3], matrix.m_row2.m128_f32[3], matrix.m_row3.m128_f32[3]);

		const FLOAT x = _mm_dp_ps(vector.m_vector, m128Temp0, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(vector.m_vector, m128Temp1, 0xff).m128_f32[0];
		const FLOAT z = _mm_dp_ps(vector.m_vector, m128Temp2, 0xff).m128_f32[0];
		const FLOAT w = _mm_dp_ps(vector.m_vector, m128Temp3, 0xff).m128_f32[0];

		return { x, y, z, w };
	}

	Vector4 Matrix4x4::PostMultiVector4(const Matrix4x4& matrix, const Vector4& vector)
	{
		const FLOAT x = _mm_dp_ps(matrix.m_row0, vector.m_vector, 0xff).m128_f32[0];
		const FLOAT y = _mm_dp_ps(matrix.m_row1, vector.m_vector, 0xff).m128_f32[0];
		const FLOAT z = _mm_dp_ps(matrix.m_row2, vector.m_vector, 0xff).m128_f32[0];
		const FLOAT w = _mm_dp_ps(matrix.m_row3, vector.m_vector, 0xff).m128_f32[0];

		return { x, y, z, w };
	}

	Matrix4x4 Matrix4x4::MultiMatrix(const Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		const __m128 row0 = _mm_mul_ps(lhs.m_row0, rhs.m_row0);
		const __m128 row1 = _mm_mul_ps(lhs.m_row1, rhs.m_row1);
		const __m128 row2 = _mm_mul_ps(lhs.m_row2, rhs.m_row2);
		const __m128 row3 = _mm_mul_ps(lhs.m_row3, rhs.m_row3);

		return { row0, row1, row2, row3 };
	}

	Matrix4x4 Matrix4x4::BuildScaleMatrix(FLOAT scalar)
	{
		return {
			scalar, 0.0f, 0.0f, 0.0f,
			0.0f, scalar, 0.0f, 0.0f,
			0.0f, 0.0f, scalar, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	Matrix4x4 Matrix4x4::BuildScaleMatrix(FLOAT x, FLOAT y, FLOAT z)
	{
		return {
			x, 0.0f, 0.0f, 0.0f,
			0.0f, y, 0.0f, 0.0f,
			0.0f, 0.0f, z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	Matrix4x4 Matrix4x4::BuildRotateXMatrix(FLOAT angle)
	{
		return {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos(angle), sin(angle), 0.0f,
			0.0f, -sin(angle), cos(angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	Matrix4x4 Matrix4x4::BuildRotateYMatrix(FLOAT angle)
	{
		return {
			cos(angle), 0.0f, -sin(angle), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sin(angle), 0.0f, cos(angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	Matrix4x4 Matrix4x4::BuildRotateZMatrix(FLOAT angle)
	{
		return {
			cos(angle), sin(angle), 0.0f, 0.0f,
			-sin(angle), cos(angle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	Matrix4x4 Matrix4x4::BuildTranslateMatrix(FLOAT x, FLOAT y, FLOAT z)
	{
		return {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			x, y, z, 1.0f
		};
	}

	const Matrix4x4 Matrix4x4::Identity = Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	Matrix4x4::Matrix4x4(const __m128& mRow0, const __m128& mRow1, const __m128& mRow2, const __m128& mRow3) :
		m_row0(mRow0), m_row1(mRow1), m_row2(mRow2), m_row3(mRow3) { }
}

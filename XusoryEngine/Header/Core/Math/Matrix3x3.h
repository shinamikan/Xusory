#pragma once

#include <immintrin.h>
#include "../../Platform/Platform.h"

namespace XusoryEngine
{
	struct Float3x3
	{
		Float3x3() = default;
		Float3x3(
			FLOAT m00, FLOAT m01, FLOAT m02,
			FLOAT m10, FLOAT m11, FLOAT m12,
			FLOAT m20, FLOAT m21, FLOAT m22);
		DEFAULT_COPY_OPERATOR(Float3x3);
		DEFAULT_MOVE_OPERATOR(Float3x3);
		~Float3x3() = default;

		FLOAT m[3][3];
	};

	class Vector3;
	DLL_CLASS(Matrix3x3)
	{
	public:
		Matrix3x3();
		Matrix3x3(
			FLOAT m00, FLOAT m01, FLOAT m02,
			FLOAT m10, FLOAT m11, FLOAT m12,
			FLOAT m20, FLOAT m21, FLOAT m22);
		explicit Matrix3x3(FLOAT scalar);
		explicit Matrix3x3(const Float3x3& m);
		DEFAULT_COPY_OPERATOR(Matrix3x3);
		DEFAULT_MOVE_OPERATOR(Matrix3x3);
		~Matrix3x3() = default;

		Matrix3x3 operator+(const Matrix3x3& other) const;
		Matrix3x3 operator-(const Matrix3x3& other) const;
		Matrix3x3 operator*(FLOAT scalar) const;
		Matrix3x3 operator*(const Matrix3x3& other) const;
		Matrix3x3 operator/(FLOAT scalar) const;
		Matrix3x3 operator/(const Matrix3x3& other) const;
		Matrix3x3 operator==(const Matrix3x3& other) const;
		Matrix3x3& operator+=(const Matrix3x3& other);
		Matrix3x3& operator-=(const Matrix3x3& other);
		Matrix3x3& operator*=(FLOAT scalar);
		Matrix3x3& operator*=(const Matrix3x3& other);
		Matrix3x3& operator/=(FLOAT scalar);
		Matrix3x3& operator/=(const Matrix3x3& other);

		Float3x3 GetMatrix() const;
		void SetMatrix(
			FLOAT m00, FLOAT m01, FLOAT m02,
			FLOAT m10, FLOAT m11, FLOAT m12,
			FLOAT m20, FLOAT m21, FLOAT m22);

		FLOAT Determinant() const;
		Matrix3x3 Inverse() const;
		Matrix3x3 Transpose() const;

		static Vector3 PreMultiVector3(const Vector3& vector, const Matrix3x3& matrix);
		static Vector3 PostMultiVector3(const Matrix3x3& matrix, const Vector3& vector);
		static Matrix3x3 MultiMatrix(const Matrix3x3& lhs, const Matrix3x3& rhs);

	private:
		explicit Matrix3x3(const __m128& mRow0, const __m128 & mRow1, const __m128& mRow2);

		__m128 m_row0;
		__m128 m_row1;
		__m128 m_row2;
	};
}

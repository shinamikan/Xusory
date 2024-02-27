#pragma once

#include <immintrin.h>
#include "../../Platform/Platform.h"

namespace XusoryEngine
{
	struct Float2x2
	{
		Float2x2() = default;
		Float2x2(
			FLOAT m00, FLOAT m01,
			FLOAT m10, FLOAT m11);
		DEFAULT_COPY_OPERATOR(Float2x2);
		DEFAULT_MOVE_OPERATOR(Float2x2);
		~Float2x2() = default;

		FLOAT m[2][2];
	};

	class Vector2;
	DLL_CLASS(Matrix2x2)
	{
	public:
		Matrix2x2();
		Matrix2x2(
			FLOAT m00, FLOAT m01,
			FLOAT m10, FLOAT m11);
		explicit Matrix2x2(FLOAT scalar);
		explicit Matrix2x2(const Float2x2& m);
		DEFAULT_COPY_OPERATOR(Matrix2x2);
		DEFAULT_MOVE_OPERATOR(Matrix2x2);
		~Matrix2x2() = default;

		Matrix2x2 operator+(const Matrix2x2& other) const;
		Matrix2x2 operator-(const Matrix2x2& other) const;
		Matrix2x2 operator*(FLOAT scalar) const;
		Matrix2x2 operator*(const Matrix2x2& other) const;
		Matrix2x2 operator/(FLOAT scalar) const;
		Matrix2x2 operator/(const Matrix2x2& other) const;
		Matrix2x2 operator==(const Matrix2x2& other) const;
		Matrix2x2& operator+=(const Matrix2x2& other);
		Matrix2x2& operator-=(const Matrix2x2& other);
		Matrix2x2& operator*=(FLOAT scalar);
		Matrix2x2& operator*=(const Matrix2x2& other);
		Matrix2x2& operator/=(FLOAT scalar);
		Matrix2x2& operator/=(const Matrix2x2& other);

		Float2x2 GetMatrix() const;
		void SetMatrix(
			FLOAT m00, FLOAT m01,
			FLOAT m10, FLOAT m11);

		FLOAT Determinant() const;
		Matrix2x2 Inverse() const;
		Matrix2x2 Transpose() const;

		static Vector2 PreMultiVector2(const Vector2& vector, const Matrix2x2& matrix);
		static Vector2 PostMultiVector2(const Matrix2x2& matrix, const Vector2& vector);
		static Matrix2x2 MultiMatrix(const Matrix2x2& lhs, const Matrix2x2& rhs);

	private:
		Matrix2x2(const __m128& mRow0, const __m128& mRow1);

		__m128 m_row0;
		__m128 m_row1;
	};
}

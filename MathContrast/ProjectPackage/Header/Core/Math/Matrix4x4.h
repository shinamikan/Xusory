#pragma once

#include <immintrin.h>
#include "../../Platform/Platform.h"

namespace XusoryEngine
{
	struct Float4x4
	{
		Float4x4() = default;
		Float4x4(
			FLOAT m00, FLOAT m01, FLOAT m02, FLOAT m03,
			FLOAT m10, FLOAT m11, FLOAT m12, FLOAT m13,
			FLOAT m20, FLOAT m21, FLOAT m22, FLOAT m23,
			FLOAT m30, FLOAT m31, FLOAT m32, FLOAT m33);
		DEFAULT_COPY_OPERATOR(Float4x4);
		DEFAULT_MOVE_OPERATOR(Float4x4);
		~Float4x4() = default;

		FLOAT m[4][4];
	};

	class Vector3;
	class Vector4;

	DLL_CLASS(Matrix4x4)
	{
	public:
		Matrix4x4();
		Matrix4x4(
			FLOAT m00, FLOAT m01, FLOAT m02, FLOAT m03,
			FLOAT m10, FLOAT m11, FLOAT m12, FLOAT m13,
			FLOAT m20, FLOAT m21, FLOAT m22, FLOAT m23,
			FLOAT m30, FLOAT m31, FLOAT m32, FLOAT m33);
		explicit Matrix4x4(FLOAT scalar);
		explicit Matrix4x4(const Float4x4& m);
		DEFAULT_COPY_OPERATOR(Matrix4x4);
		DEFAULT_MOVE_OPERATOR(Matrix4x4);
		~Matrix4x4() = default;

		Matrix4x4 operator+(const Matrix4x4& other) const;
		Matrix4x4 operator-(const Matrix4x4& other) const;
		Matrix4x4 operator*(FLOAT scalar) const;
		Matrix4x4 operator*(const Matrix4x4& other) const;
		Matrix4x4 operator/(FLOAT scalar) const;
		Matrix4x4 operator/(const Matrix4x4& other) const;
		Matrix4x4 operator==(const Matrix4x4& other) const;
		Matrix4x4& operator+=(const Matrix4x4& other);
		Matrix4x4& operator-=(const Matrix4x4& other);
		Matrix4x4& operator*=(FLOAT scalar);
		Matrix4x4& operator*=(const Matrix4x4& other);
		Matrix4x4& operator/=(FLOAT scalar);
		Matrix4x4& operator/=(const Matrix4x4& other);

		Float4x4 GetMatrix() const;
		void SetMatrix(
			FLOAT m00, FLOAT m01, FLOAT m02, FLOAT m03,
			FLOAT m10, FLOAT m11, FLOAT m12, FLOAT m13,
			FLOAT m20, FLOAT m21, FLOAT m22, FLOAT m23,
			FLOAT m30, FLOAT m31, FLOAT m32, FLOAT m33);

		FLOAT Determinant() const;
		Matrix4x4 Inverse() const;
		Matrix4x4 Transpose() const;

		static const Matrix4x4 Identity;

		static Vector3 PreTransPoint3(const Vector3& vector, const Matrix4x4& matrix);
		static Vector3 PreTransVector3(const Vector3& vector, const Matrix4x4& matrix);
		static Vector3 PostTransPoint3(const Matrix4x4& matrix, const Vector3& vector);
		static Vector3 PostTransVector3(const Matrix4x4& matrix, const Vector3& vector);
		static Vector4 PreMultiVector4(const Vector4& vector, const Matrix4x4& matrix);
		static Vector4 PostMultiVector4(const Matrix4x4& matrix, const Vector4& vector);
		static Matrix4x4 MultiMatrix(const Matrix4x4& lhs, const Matrix4x4& rhs);

		static Matrix4x4 BuildScaleMatrix(FLOAT scalar);
		static Matrix4x4 BuildScaleMatrix(FLOAT x, FLOAT y, FLOAT z);
		static Matrix4x4 BuildScaleMatrix(const Vector3& scale);
		static Matrix4x4 BuildRotateXMatrix(FLOAT angle);
		static Matrix4x4 BuildRotateYMatrix(FLOAT angle);
		static Matrix4x4 BuildRotateZMatrix(FLOAT angle);
		static Matrix4x4 BuildRotateAnyMatrix(FLOAT angle, const Vector3& anyAxis);
		static Matrix4x4 BuildTranslateMatrix(FLOAT x, FLOAT y, FLOAT z);
		static Matrix4x4 BuildTranslateMatrix(const Vector3& translation);

	private:
		Matrix4x4(const __m128& mRow0, const __m128& mRow1, const __m128& mRow2, const __m128& mRow3);

		__m128 m_row0;
		__m128 m_row1;
		__m128 m_row2;
		__m128 m_row3;
	};
}

#pragma once

#include <immintrin.h>
#include "../../Platform/Platform.h"

namespace XusoryEngine
{
	DLL_STRUCT(Float3)
	{
		Float3() = default;
		Float3(FLOAT x, FLOAT y, FLOAT z);
		DEFAULT_COPY_OPERATOR(Float3);
		DEFAULT_MOVE_OPERATOR(Float3);
		~Float3() = default;

		FLOAT x;
		FLOAT y;
		FLOAT z;
	};

	DLL_CLASS(Vector3)
	{
		friend class Matrix3x3;
		friend class Matrix4x4;

	public:
		Vector3();
		Vector3(FLOAT x, FLOAT y, FLOAT z);
		explicit Vector3(FLOAT scalar);
		explicit Vector3(const Float3& v);
		DEFAULT_COPY_OPERATOR(Vector3);
		DEFAULT_MOVE_OPERATOR(Vector3);
		~Vector3() = default;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3 operator*(FLOAT scalar) const;
		Vector3 operator*(const Vector3& other) const;
		Vector3 operator/(FLOAT scalar) const;
		Vector3 operator/(const Vector3& other) const;
		Vector3 operator==(const Vector3& other) const;
		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);
		Vector3& operator*=(FLOAT scalar);
		Vector3& operator*=(const Vector3& other);
		Vector3& operator/=(FLOAT scalar);
		Vector3& operator/=(const Vector3& other);

		FLOAT X() const;
		FLOAT Y() const;
		FLOAT Z() const;
		Float3 GetVector() const;
		void SetVector(FLOAT x, FLOAT y, FLOAT z);

		FLOAT Length() const;
		FLOAT LengthSq() const;
		FLOAT Dot(const Vector3& other) const;

		Vector3 Normalize() const;
		Vector3 Sqrt() const;
		Vector3 Max(const Vector3& other) const;
		Vector3 Min(const Vector3& other) const;

		static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
		static Vector3 Lerp(const Vector3& vec, const Vector3& end, FLOAT weight);

		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 OneX;
		static const Vector3 OneY;
		static const Vector3 OneZ;

	private:
		explicit Vector3(const __m128& v);
		__m128 m_vector;
	};
}

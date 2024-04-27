#pragma once

#include <immintrin.h>
#include "../../Platform/Platform.h"

namespace XusoryEngine
{
	DLL_STRUCT(Float4)
	{
		Float4() = default;
		Float4(FLOAT x, FLOAT y, FLOAT z, FLOAT w);
		DEFAULT_COPY_OPERATOR(Float4);
		DEFAULT_MOVE_OPERATOR(Float4);
		~Float4() = default;

		FLOAT x;
		FLOAT y;
		FLOAT z;
		FLOAT w;
	};

	DLL_CLASS(Vector4)
	{
		friend class Matrix4x4;

	public:
		Vector4();
		Vector4(FLOAT x, FLOAT y, FLOAT z, FLOAT w);
		explicit Vector4(FLOAT scalar);
		explicit Vector4(const Float4& v);
		DEFAULT_COPY_OPERATOR(Vector4);
		DEFAULT_MOVE_OPERATOR(Vector4);
		~Vector4() = default;

		Vector4 operator+(const Vector4& other) const;
		Vector4 operator-(const Vector4& other) const;
		Vector4 operator*(FLOAT scalar) const;
		Vector4 operator*(const Vector4& other) const;
		Vector4 operator/(FLOAT scalar) const;
		Vector4 operator/(const Vector4& other) const;
		Vector4 operator==(const Vector4& other) const;
		Vector4& operator+=(const Vector4& other);
		Vector4& operator-=(const Vector4& other);
		Vector4& operator*=(FLOAT scalar);
		Vector4& operator*=(const Vector4& other);
		Vector4& operator/=(FLOAT scalar);
		Vector4& operator/=(const Vector4& other);

		FLOAT X() const;
		FLOAT Y() const;
		FLOAT Z() const;
		FLOAT W() const;
		Float4 GetVector() const;

		void SetVector(FLOAT x, FLOAT y, FLOAT z, FLOAT w);
		void SetVector(const Float4& vector);

		FLOAT Length() const;
		FLOAT LengthSq() const;
		FLOAT Dot(const Vector4& other) const;

		Vector4 Normalize() const;
		Vector4 Sqrt() const;
		Vector4 Max(const Vector4& other) const;
		Vector4 Min(const Vector4& other) const;

		static Vector4 Lerp(const Vector4& start, const Vector4& end, FLOAT weight);

		static const Vector4 Zero;
		static const Vector4 One;
		static const Vector4 OneX;
		static const Vector4 OneY;
		static const Vector4 OneZ;
		static const Vector4 OneW;

	private:
		explicit Vector4(const __m128& v);
		__m128 m_vector;
	};
}

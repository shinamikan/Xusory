#pragma once

#include <immintrin.h>
#include "../../Platform/Platform.h"

namespace XusoryEngine
{
	struct Float2
	{
		Float2() = default;
		Float2(FLOAT x, FLOAT y);
		DEFAULT_COPY_OPERATOR(Float2);
		DEFAULT_MOVE_OPERATOR(Float2);
		~Float2() = default;

		FLOAT x;
		FLOAT y;
	};

	DLL_CLASS(Vector2)
	{
		friend class Matrix2x2;

	public:
		Vector2();
		Vector2(FLOAT x, FLOAT y);
		explicit Vector2(FLOAT scalar);
		explicit Vector2(const Float2& v);
		DEFAULT_COPY_OPERATOR(Vector2);
		DEFAULT_MOVE_OPERATOR(Vector2);
		~Vector2() = default;

		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator*(FLOAT scalar) const;
		Vector2 operator*(const Vector2& other) const;
		Vector2 operator/(FLOAT scalar) const;
		Vector2 operator/(const Vector2& other) const;
		Vector2 operator==(const Vector2& other) const;
		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator*=(FLOAT scalar);
		Vector2& operator*=(const Vector2& other);
		Vector2& operator/=(FLOAT scalar);
		Vector2& operator/=(const Vector2& other);

		FLOAT X() const;
		FLOAT Y() const;
		Float2 GetVector() const;
		void SetVector(FLOAT x, FLOAT y);

		FLOAT Length() const;
		FLOAT LengthSq() const;
		FLOAT Dot(const Vector2& other) const;

		Vector2 Normalize() const;
		Vector2 Sqrt() const;
		Vector2 Max(const Vector2& other) const;
		Vector2 Min(const Vector2& other) const;

		static Vector2 Lerp(const Vector2& start, const Vector2& end, FLOAT weight);

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 OneX;
		static const Vector2 OneY;

	private:
		explicit Vector2(const __m128& v);
		__m128 m_vector;
	};
}

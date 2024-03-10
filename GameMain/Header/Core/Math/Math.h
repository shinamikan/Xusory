#pragma once

#include <iostream>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

namespace XusoryEngine
{
	DLL_CLASS(Math)
	{
	public:
		static constexpr FLOAT Pi = 3.1415926535f;
	};

	inline std::ostream& operator<<(std::ostream& os, const Float2& v)
	{
		os << "(" << v.x << ", " << v.y << ")";
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector2& vector)
	{
		os << "(" << vector.X() << ", " << vector.Y() << ")";
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Float3& v)
	{
		os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector3& vector)
	{
		os << "(" << vector.X() << ", " << vector.Y() << ", " << vector.Z() << ")";
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Float4& v)
	{
		os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Vector4& vector)
	{
		os << "(" << vector.X() << ", " << vector.Y() << ", " << vector.Z() << ", " << vector.W() << ")";
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Float2x2& m)
	{
		os << m.m[0][0] << "\t" << m.m[0][1] << std::endl;
		os << m.m[1][0] << "\t" << m.m[1][1];

		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Matrix2x2& matrix)
	{
		const Float2x2 m = matrix.GetMatrix();
		os << m;

		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Float3x3& m)
	{
		os << m.m[0][0] << "\t" << m.m[0][1] << "\t" << m.m[0][2] << std::endl;
		os << m.m[1][0] << "\t" << m.m[1][1] << "\t" << m.m[1][2] << std::endl;
		os << m.m[2][0] << "\t" << m.m[2][1] << "\t" << m.m[2][2];

		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Matrix3x3& matrix)
	{
		const Float3x3 m = matrix.GetMatrix();
		os << m;

		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Float4x4& m)
	{
		os << m.m[0][0] << "\t" << m.m[0][1] << "\t" << m.m[0][2] << "\t" << m.m[0][3] << std::endl;
		os << m.m[1][0] << "\t" << m.m[1][1] << "\t" << m.m[1][2] << "\t" << m.m[1][3] << std::endl;
		os << m.m[2][0] << "\t" << m.m[2][1] << "\t" << m.m[2][2] << "\t" << m.m[2][3] << std::endl;
		os << m.m[3][0] << "\t" << m.m[3][1] << "\t" << m.m[3][2] << "\t" << m.m[3][3];

		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, const Matrix4x4& matrix)
	{
		const Float4x4 m = matrix.GetMatrix();
		os << m;

		return os;
	}
}

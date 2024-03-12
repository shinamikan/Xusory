#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	enum class Axis
	{
		X = 0, Y, Z
	};

	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(FLOAT x, FLOAT y, FLOAT z, FLOAT w);
		Quaternion(Axis axis, FLOAT eulerAngle);
		Quaternion(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ);
		explicit Quaternion(const Float4& quaternion);
		explicit Quaternion(const Vector4& quaternion);
		explicit Quaternion(const Float3& eulerAngles);
		DEFAULT_COPY_OPERATOR(Quaternion);
		DEFAULT_MOVE_OPERATOR(Quaternion);
		~Quaternion() = default;

		Quaternion operator*(FLOAT scalar) const;
		Quaternion operator*(const Quaternion& other) const;
		Quaternion& operator*=(FLOAT scalar);
		Quaternion& operator*=(const Quaternion& other);
		BOOL operator==(const Quaternion& other) const;

		FLOAT X() const;
		FLOAT Y() const;
		FLOAT Z() const;
		FLOAT W() const;

		Float3 GetEulerAngles() const;
		Float4 GetQuaternion() const;
		const Vector4& GetQuaternionVector() const;
		
		void SetWithEulerAngles(Axis axis, FLOAT eulerAngle);
		void SetWithEulerAngles(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ);
		void SetWithEulerAngles(const Float3& eulerAngles);

		void SetQuaternion(FLOAT x, FLOAT y, FLOAT z, FLOAT w);
		void SetQuaternion(const Float4& quaternion);
		void SetQuaternion(const Vector4& quaternion);

		FLOAT Norm() const;
		FLOAT NormSq() const;
		FLOAT Dot(const Quaternion& other) const;

		Quaternion Conjugate() const;
		Quaternion Inverse() const;
		Quaternion Normalize() const;

		Quaternion Multiply(FLOAT scalar) const;
		Quaternion Multiply(const Quaternion& other) const;

		static const Quaternion Identity;
		static Matrix4x4 BuildRotationMatrixByQuaternion(const Quaternion& quaternion);

	private:
		Vector4 m_quaternion;
	};

	inline std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion)
	{
		os << quaternion.GetQuaternionVector();
		return os;
	}
}

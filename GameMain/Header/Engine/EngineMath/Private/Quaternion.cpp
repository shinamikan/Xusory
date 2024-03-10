#include <cmath>
#include "../Quaternion.h"
#include "../EngineMath.h"

namespace XusoryEngine
{
	Quaternion::Quaternion() : m_quaternion(0.0f, 0.0f, 0.0f, 1.0f) { }
	Quaternion::Quaternion(FLOAT x, FLOAT y, FLOAT z, FLOAT w) : m_quaternion(x, y, z, w) { }
	Quaternion::Quaternion(Axis axis, FLOAT eulerAngle)
	{
		SetWithEulerAngles(axis, eulerAngle);
	}

	Quaternion::Quaternion(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ)
	{
		SetWithEulerAngles(eulerAngleX, eulerAngleY, eulerAngleZ);
	}

	Quaternion::Quaternion(const Float4& quaternion) : m_quaternion(quaternion) { }
	Quaternion::Quaternion(const Vector4& quaternion) : m_quaternion(quaternion) { }

	Quaternion::Quaternion(const Float3& eulerAngles)
	{
		SetWithEulerAngles(eulerAngles);
	}

	Quaternion Quaternion::operator*(FLOAT scalar) const
	{
		return Multiply(scalar);
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		return Multiply(other);
	}

	Quaternion& Quaternion::operator*=(FLOAT scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& other)
	{
		*this = *this * other;
		return *this;
	}

	BOOL Quaternion::operator==(const Quaternion& other) const
	{
		return X() == other.X() && Y() == other.Y() && Z() == other.Z() && W() == other.W();
	}

	FLOAT Quaternion::X() const
	{
		return m_quaternion.X();
	}

	FLOAT Quaternion::Y() const
	{
		return m_quaternion.Y();
	}

	FLOAT Quaternion::Z() const
	{
		return m_quaternion.Z();
	}

	FLOAT Quaternion::W() const
	{
		return m_quaternion.W();
	}

	Float4 Quaternion::GetQuaternion() const
	{
		return m_quaternion.GetVector();
	}

	const Vector4& Quaternion::GetQuaternionVector() const
	{
		return m_quaternion;
	}

	void Quaternion::SetQuaternion(FLOAT x, FLOAT y, FLOAT z, FLOAT w)
	{
		m_quaternion.SetVector(x, y, z, w);
	}

	void Quaternion::SetQuaternion(const Float4& quaternion)
	{
		m_quaternion.SetVector(quaternion);
	}

	void Quaternion::SetQuaternion(const Vector4& quaternion)
	{
		m_quaternion = quaternion;
	}

	FLOAT Quaternion::GetEulerAngles(Axis axis)
	{
		return FLOAT();
	}

	Float3 Quaternion::GetEulerAngles()
	{
		return Float3();
	}

	void Quaternion::SetWithEulerAngles(Axis axis, FLOAT eulerAngle)
	{
		const FLOAT radian = eulerAngle * Math::Pi / 180.0f;

		switch (axis)
		{
		case Axis::X:
			m_quaternion.SetVector(sin(radian / 2), 0.0f, 0.0f, cos(radian / 2));
			break;

		case Axis::Y:
			m_quaternion.SetVector(0.0f, sin(radian / 2), 0.0f, cos(radian / 2));
			break;

		case Axis::Z:
			m_quaternion.SetVector(0.0f, 0.0f, sin(radian / 2), cos(radian / 2));
			break;
		}
	}

	void Quaternion::SetWithEulerAngles(const Float3& eulerAngles)
	{
		const Quaternion quaX = Quaternion(Axis::X, eulerAngles.x);
		const Quaternion quaY = Quaternion(Axis::Y, eulerAngles.y);
		const Quaternion quaZ = Quaternion(Axis::Z, eulerAngles.z);

		*this = quaZ * quaX * quaY;
	}

	void Quaternion::SetWithEulerAngles(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ)
	{
		const Quaternion quaX = Quaternion(Axis::X, eulerAngleX);
		const Quaternion quaY = Quaternion(Axis::Y, eulerAngleY);
		const Quaternion quaZ = Quaternion(Axis::Z, eulerAngleZ);

		*this = quaZ * quaX * quaY;
	}

	FLOAT Quaternion::Norm() const
	{
		return  static_cast<FLOAT>(sqrt(pow(X(), 2) + pow(Y(), 2) + pow(Z(), 2) + pow(W(), 2)));
	}

	FLOAT Quaternion::NormSq() const
	{
		return static_cast<FLOAT>(pow(X(), 2) + pow(Y(), 2) + pow(Z(), 2) + pow(W(), 2));
	}

	FLOAT Quaternion::Dot(const Quaternion& other) const
	{
		return m_quaternion.Dot(other.m_quaternion);
	}

	Quaternion Quaternion::Conjugate() const
	{
		return { -X(), -Y(), -Z(), W() };
	}

	Quaternion Quaternion::Inverse() const
	{
		return Conjugate() * (1 / Norm());
	}

	Quaternion Quaternion::Normalize() const
	{
		Quaternion result;
		result.m_quaternion = m_quaternion.Normalize();

		return result;
	}

	Quaternion Quaternion::Multiply(FLOAT scalar) const
	{
		Quaternion result;
		result.m_quaternion = m_quaternion * scalar;

		return result;
	}

	Quaternion Quaternion::Multiply(const Quaternion& other) const
	{
		Quaternion result;
		const FLOAT a = X(); const FLOAT b = Y(); const FLOAT c = Z(); const FLOAT d = W();
		const FLOAT x = other.X(); const FLOAT y = other.Y(); const FLOAT z = other.Z(); const FLOAT w = other.W();

		result.SetQuaternion(
			d * x + a * w + b * z - c * y,
			d * y + b * w + c * x - a * z,
			d * z + c * w + a * y - b * x,
			d * w - a * x - b * y - c * z);

		return result;
	}

	const Quaternion Quaternion::Identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	Matrix4x4 Quaternion::BuildRotationMatrixByQuaternion(const Quaternion& quaternion)
	{
		const FLOAT q1 = quaternion.X(); const FLOAT q2 = quaternion.Y(); const FLOAT q3 = quaternion.Z(); const FLOAT q4 = quaternion.W();
		const auto q1Squ = static_cast<FLOAT>(pow(q1, 2));
		const auto q2Squ = static_cast<FLOAT>(pow(q2, 2));
		const auto q3Squ = static_cast<FLOAT>(pow(q3, 2));

		return {
			1 - 2 *	q2Squ - 2 * q3Squ, 2 * q1 * q2 + 2 * q3 * q4, 2 * q1 * q3 - 2 * q2 * q4, 0,
			2 * q1 * q2 - 2 * q3 * q4, 1 - 2 * q1Squ - 2 * q3Squ, 2 * q2 * q3 + 2 * q1 * q4, 0,
			2 * q1 * q3 + 2 * q2 * q4, 2 * q2 * q3 - 2 * q1 * q4, 1 - 2 * q1Squ - 2 * q2Squ, 0,
			0, 0, 0, 1
		};
	}
}

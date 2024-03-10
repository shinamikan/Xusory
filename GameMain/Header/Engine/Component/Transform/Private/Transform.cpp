#include "../Transform.h"
#include "../../../EngineMath/EngineMath.h"

namespace XusoryEngine
{
	Float3 Transform::GetPosition(Space space) const
	{
		if (space == Space::LOCAL)
		{
			return m_localPosition.GetVector();
		}
		return m_worldPosition.GetVector();
	}

	Float3 Transform::GetScale(Space space) const
	{
		if (space == Space::LOCAL)
		{
			return m_localScale.GetVector();
		}
		return m_worldScale.GetVector();
	}

	const Vector3& Transform::GetPositionVector(Space space) const
	{
		if (space == Space::LOCAL)
		{
			return m_localPosition;
		}
		return m_worldPosition;
	}

	Float4 Transform::GetRotation(Space space) const
	{
		return m_localRotation.GetQuaternion();
	}

	const Vector3& Transform::GetScaleVector(Space space) const
	{
		if (space == Space::LOCAL)
		{
			return m_localScale;
		}
		return m_worldScale;
	}

	const Quaternion& Transform::GetRotationQuaternion(Space space) const
	{
		return m_localRotation;
	}

	Matrix4x4 Transform::GetModelMatrix() const
	{
		return EngineMath::BuildModelMatrix(m_localPosition, m_localScale, m_localRotation);
	}

	void Transform::MoveTo(FLOAT x, FLOAT y, FLOAT z, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localPosition.SetVector(x, y, z);
		}
		else
		{
			m_worldPosition.SetVector(x, y, z);
		}
	}

	void Transform::MoveTo(const Vector3& translateValue, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localPosition = translateValue;
		}
		else
		{
			m_worldPosition = translateValue;
		}
	}

	void Transform::Translate(FLOAT x, FLOAT y, FLOAT z, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localPosition = Matrix4x4::PreTransPoint3(m_localPosition, Matrix4x4::BuildTranslateMatrix(x, y, z));
		}
		else
		{
			m_worldPosition = Matrix4x4::PreTransPoint3(m_worldPosition, Matrix4x4::BuildTranslateMatrix(x, y, z));
		}
	}

	void Transform::Translate(const Vector3& translateValue, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localPosition = Matrix4x4::PreTransPoint3(m_localPosition, Matrix4x4::BuildTranslateMatrix(translateValue.X(), translateValue.Y(), translateValue.Z()));
		}
		else
		{
			m_worldPosition = Matrix4x4::PreTransPoint3(m_worldPosition, Matrix4x4::BuildTranslateMatrix(translateValue.X(), translateValue.Y(), translateValue.Z()));
		}
	}

	void Transform::SetRulerAngles(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localRotation.SetWithEulerAngles(eulerAngleX, eulerAngleY, eulerAngleZ);
		}
		else
		{
			m_worldRotation.SetWithEulerAngles(eulerAngleX, eulerAngleY, eulerAngleZ);
		}
	}

	void Transform::SetRulerAngles(const Float3& eulerAngles, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localRotation.SetWithEulerAngles(eulerAngles);
		}
		else
		{
			m_worldRotation.SetWithEulerAngles(eulerAngles);
		}
	}

	void Transform::SetRotation(FLOAT x, FLOAT y, FLOAT z, FLOAT w, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localRotation.SetQuaternion(x, y, z, w);
		}
		else
		{
			m_worldRotation.SetQuaternion(x, y, z, w);
		}
	}

	void Transform::SetRotation(const Quaternion& quaternion, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localRotation = quaternion;
		}
		else
		{
			m_worldRotation = quaternion;
		}
	}

	void Transform::Rotate(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localRotation *= Quaternion(eulerAngleX, eulerAngleY, eulerAngleZ);
			m_localRotation = m_localRotation.Normalize();
		}
		else
		{
			m_worldRotation *= Quaternion(eulerAngleX, eulerAngleY, eulerAngleZ);
			m_worldRotation = m_localRotation.Normalize();
		}
	}

	void Transform::Rotate(const Float3& eulerAngles, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localRotation *= Quaternion(eulerAngles);
			m_localRotation = m_localRotation.Normalize();
		}
		else
		{
			m_worldRotation *= Quaternion(eulerAngles);
			m_worldRotation = m_worldRotation.Normalize();
		}
	}

	Transform::Transform(const std::string_view& componentName, GameObject* gameObject, const Float3& localPosition) : Component(componentName, gameObject), m_localPosition(localPosition) { }
	Transform::Transform(const std::string_view& componentName, GameObject* gameObject, const Float3& localPosition, const Float3& localScale) : Component(componentName, gameObject),
		m_localPosition(localPosition), m_localScale(localScale) { }

}

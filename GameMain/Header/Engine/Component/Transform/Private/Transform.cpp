#include "../Transform.h"
#include "../../../GameObject/GameObject.h"

namespace XusoryEngine
{
	Vector3 Transform::GetPosition(Space space) const
	{
		if (space == Space::LOCAL)
		{
			return m_localPosition;
		}

		Vector3 worldPositionTemp = m_localPosition;
		if (m_belongsGameObject->HasParent())
		{
			const GameObject* parentTemp = m_belongsGameObject->GetParent();
			while (true)
			{
				worldPositionTemp += parentTemp->GetTransform()->m_localPosition;
				if (parentTemp->HasParent())
				{
					parentTemp = parentTemp->GetParent();
				}
				else
				{
					break;
				}
			}
		}

		return worldPositionTemp;
	}

	Vector3 Transform::GetScale(Space space) const
	{
		if (space == Space::LOCAL)
		{
			return m_localScale;
		}

		Vector3 worldScaleTemp = m_localScale;
		if (m_belongsGameObject->HasParent())
		{
			const GameObject* parentTemp = m_belongsGameObject->GetParent();
			while (true)
			{
				worldScaleTemp *= parentTemp->GetTransform()->m_localScale;
				if (parentTemp->HasParent())
				{
					parentTemp = parentTemp->GetParent();
				}
				else
				{
					break;
				}
			}
		}

		return worldScaleTemp;
	}

	Vector3 Transform::GetEulerAngles(Space space) const
	{
		return GetRotation(space).GetEulerAngles();
	}

	Quaternion Transform::GetRotation(Space space) const
	{
		if (space == Space::LOCAL)
		{
			return m_localRotation;
		}

		Quaternion worldRotationTemp = m_localRotation;
		if (m_belongsGameObject->HasParent())
		{
			const GameObject* parentTemp = m_belongsGameObject->GetParent();
			while (true)
			{
				worldRotationTemp *= parentTemp->GetTransform()->m_localRotation;
				if (parentTemp->HasParent())
				{
					parentTemp = parentTemp->GetParent();
				}
				else
				{
					break;
				}
			}
		}

		return worldRotationTemp;
	}

	Matrix4x4 Transform::GetModelMatrix() const
	{
		const auto translateMat = Matrix4x4::BuildTranslateMatrix(GetPosition(Space::WORLD));
		const auto scaleMat = Matrix4x4::BuildScaleMatrix(GetScale(Space::WORLD));
		const auto rotateMat = Quaternion::BuildRotationMatrixByQuaternion(GetRotation(Space::WORLD));
		
		return scaleMat * rotateMat * translateMat;
	}

	Vector3 Transform::Up() const
	{
		const auto up = Vector3(0.0f, 1.0f, 0.0f);
		const auto rotateMat = Quaternion::BuildRotationMatrixByQuaternion(GetRotation(Space::WORLD));

		return Matrix4x4::PreTransPoint3(up, rotateMat);
	}

	Vector3 Transform::Down() const
	{
		const auto down = Vector3(0.0f, -1.0f, 0.0f);
		const auto rotateMat = Quaternion::BuildRotationMatrixByQuaternion(GetRotation(Space::WORLD));

		return Matrix4x4::PreTransPoint3(down, rotateMat);
	}

	Vector3 Transform::Forward() const
	{
		const auto forward = Vector3(0.0f, 0.0f, 1.0f);
		const auto rotateMat = Quaternion::BuildRotationMatrixByQuaternion(GetRotation(Space::WORLD));

		return Matrix4x4::PreTransPoint3(forward, rotateMat);
	}

	Vector3 Transform::Back() const
	{
		const auto back = Vector3(0.0f, 0.0f, -1.0f);
		const auto rotateMat = Quaternion::BuildRotationMatrixByQuaternion(GetRotation(Space::WORLD));

		return Matrix4x4::PreTransPoint3(back, rotateMat);
	}

	Vector3 Transform::Left() const
	{
		const auto left = Vector3(1.0f, 0.0f, 0.0f);

		const auto rotateMat = Quaternion::BuildRotationMatrixByQuaternion(GetRotation(Space::WORLD));
		return Matrix4x4::PreTransPoint3(left, rotateMat);
	}

	Vector3 Transform::Right() const
	{
		const auto right = Vector3(-1.0f, 0.0f, 0.0f);
		const auto rotateMat = Quaternion::BuildRotationMatrixByQuaternion(GetRotation(Space::WORLD));

		return Matrix4x4::PreTransPoint3(right, rotateMat);
	}

	void Transform::MoveTo(FLOAT x, FLOAT y, FLOAT z, Space space)
	{
		MoveTo(Vector3(x, y, z), space);
	}

	void Transform::MoveTo(const Vector3& translateValue, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localPosition = translateValue;
		}
		else
		{
			Vector3 localPositionTemp = translateValue;

			if (m_belongsGameObject->HasParent())
			{
				const GameObject* parentTemp = m_belongsGameObject->GetParent();
				while (true)
				{
					localPositionTemp -= parentTemp->GetTransform()->m_localPosition;
					if (parentTemp->HasParent())
					{
						parentTemp = parentTemp->GetParent();
					}
					else
					{
						break;
					}
				}
			}

			m_localPosition = localPositionTemp;
		}
	}

	void Transform::Translate(FLOAT x, FLOAT y, FLOAT z, Space space)
	{
		Translate(Vector3(x, y, z), space);
	}

	void Transform::Translate(const Vector3& translateValue, Space space)
	{
		if (space == Space::LOCAL)
		{
			const auto localRotateMat = Quaternion::BuildRotationMatrixByQuaternion(GetRotation());
			m_localPosition += Matrix4x4::PreTransPoint3(translateValue, localRotateMat);
		}
		else
		{
			MoveTo(GetPosition(Space::WORLD) + translateValue, Space::WORLD);
		}
	}

	void Transform::SetScale(FLOAT x, FLOAT y, FLOAT z, Space space)
	{
		SetScale(Vector3(x, y, z), space);
	}

	void Transform::SetScale(const Vector3& scaleValue, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localScale = scaleValue;
		}
		else
		{
			Vector3 localScaleTemp = scaleValue;

			if (m_belongsGameObject->HasParent())
			{
				const GameObject* parentTemp = m_belongsGameObject->GetParent();
				while (true)
				{
					localScaleTemp /= parentTemp->GetTransform()->m_localPosition;
					if (parentTemp->HasParent())
					{
						parentTemp = parentTemp->GetParent();
					}
					else
					{
						break;
					}
				}
			}

			m_localPosition = localScaleTemp;
		}
	}

	void Transform::Scale(FLOAT x, FLOAT y, FLOAT z, Space space)
	{
		Scale(Vector3(x, y, z), space);
	}

	void Transform::Scale(const Vector3& scaleValue, Space space)
	{
		if (space == Space::LOCAL)
		{
			const auto localRotateMat = Quaternion::BuildRotationMatrixByQuaternion(GetRotation());
			m_localScale += Matrix4x4::PreTransPoint3(scaleValue, localRotateMat);
		}
		else
		{
			SetScale(GetScale(Space::WORLD) + scaleValue, Space::WORLD);
		}
	}

	void Transform::SetRulerAngles(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ, Space space)
	{
		SetRulerAngles(Vector3(eulerAngleX, eulerAngleY, eulerAngleZ), space);
	}

	void Transform::SetRulerAngles(const Vector3& eulerAngles, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localRotation.SetWithEulerAngles(eulerAngles);
		}
		else
		{
			Vector3 localEulerAnglesTemp = eulerAngles;

			if (m_belongsGameObject->HasParent())
			{
				const GameObject* parentTemp = m_belongsGameObject->GetParent();
				while (true)
				{
					localEulerAnglesTemp -= parentTemp->GetTransform()->m_localRotation.GetEulerAngles();
					if (parentTemp->HasParent())
					{
						parentTemp = parentTemp->GetParent();
					}
					else
					{
						break;
					}
				}
			}

			m_localRotation.SetWithEulerAngles(localEulerAnglesTemp);
		}
	}

	void Transform::SetRotation(FLOAT x, FLOAT y, FLOAT z, FLOAT w, Space space)
	{
		SetRotation(Quaternion(x, y, z, w), space);
	}

	void Transform::SetRotation(const Quaternion& rotationValue, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localRotation = rotationValue;
		}
		else
		{
			Quaternion localRotationTemp = rotationValue;

			if (m_belongsGameObject->HasParent())
			{
				const GameObject* parentTemp = m_belongsGameObject->GetParent();
				while (true)
				{
					localRotationTemp *= parentTemp->GetTransform()->m_localRotation.Inverse();
					if (parentTemp->HasParent())
					{
						parentTemp = parentTemp->GetParent();
					}
					else
					{
						break;
					}
				}
			}

			m_localRotation = localRotationTemp;
		}
	}

	void Transform::Rotate(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ, Space space)
	{
		Rotate(Vector3(eulerAngleX, eulerAngleY, eulerAngleZ), space);
	}

	void Transform::Rotate(const Vector3& eulerAngles, Space space)
	{
		if (space == Space::LOCAL)
		{
			m_localRotation *= Quaternion(eulerAngles);
			m_localRotation = m_localRotation.Normalize();
		}
		else
		{
			const Quaternion worldEulerAngles = Quaternion(eulerAngles) * m_localRotation;
			m_localRotation = worldEulerAngles.Normalize();
		}
	}

	void Transform::RotateAround(const Vector3& point, Axis axis, FLOAT eulerAngle)
	{
		auto worldPositionDiff = GetPosition(Space::WORLD) - point;
		MoveTo(point, Space::WORLD);

		Quaternion rotation;
		switch (axis)
		{
		case Axis::X:
			Rotate(eulerAngle, 0.0f, 0.0f, Space::WORLD);
			rotation = Quaternion(eulerAngle, 0.0f, 0.0f);
			break;

		case Axis::Y:
			Rotate(0.0f, eulerAngle, 0.0f, Space::WORLD);
			rotation = Quaternion(0.0f, eulerAngle, 0.0f);
			break;

		case Axis::Z:
			Rotate(0.0f, 0.0f, eulerAngle, Space::WORLD);
			rotation = Quaternion(0.0f, 0.0f, eulerAngle);
			break;
		}
		
		const auto rotateMat = Quaternion::BuildRotationMatrixByQuaternion(rotation);
		worldPositionDiff = Matrix4x4::PreTransPoint3(worldPositionDiff, rotateMat);

		Translate(worldPositionDiff, Space::WORLD);
	}

	void Transform::RotateAround(const GameObject* targetGameObject, Axis axis, FLOAT eulerAngle)
	{
		RotateAround(targetGameObject->GetTransform()->GetPosition(Space::WORLD), axis, eulerAngle);
	}

	Transform::Transform(const std::string_view& componentName, GameObject* gameObject, const Vector3& localPosition) : Component(componentName, gameObject), m_localPosition(localPosition) { }
	Transform::Transform(const std::string_view& componentName, GameObject* gameObject, const Vector3& localPosition, const Vector3& localScale, const Vector3& localEulerAngle)
		: Component(componentName, gameObject), m_localPosition(localPosition), m_localScale(localScale)
	{
		m_localRotation = Quaternion(localEulerAngle);
	}
}

#pragma once

#include "../Component.h"
#include "../../EngineMath/Quaternion.h"

namespace XusoryEngine
{
	enum class Space
	{
		LOCAL = 0,
		WORLD
	};

	DLL_CLASS(Transform) : public Component
	{
		friend class GameObject;

	public:
		Vector3 GetPosition(Space space = Space::LOCAL) const;
		Vector3 GetScale(Space space = Space::LOCAL) const;
		Vector3 GetEulerAngles(Space space = Space::LOCAL) const;
		Quaternion GetRotation(Space space = Space::LOCAL) const;

		Matrix4x4 GetModelMatrix() const;

		Vector3 Up() const;
		Vector3 Down() const;
		Vector3 Forward() const;
		Vector3 Back() const;
		Vector3 Left() const;
		Vector3 Right() const;

		void MoveTo(FLOAT x, FLOAT y, FLOAT z, Space space = Space::LOCAL);
		void MoveTo(const Vector3& translateValue, Space space = Space::LOCAL);
		void Translate(FLOAT x, FLOAT y, FLOAT z, Space space = Space::LOCAL);
		void Translate(const Vector3& translateValue, Space space = Space::LOCAL);

		void SetScale(FLOAT x, FLOAT y, FLOAT z, Space space = Space::LOCAL);
		void SetScale(const Vector3& scaleValue, Space space = Space::LOCAL);
		void Scale(FLOAT x, FLOAT y, FLOAT z, Space space = Space::LOCAL);
		void Scale(const Vector3& scaleValue, Space space = Space::LOCAL);

		void SetRulerAngles(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ, Space space = Space::LOCAL);
		void SetRulerAngles(const Vector3& eulerAngles, Space space = Space::LOCAL);
		void SetRotation(FLOAT x, FLOAT y, FLOAT z, FLOAT w, Space space = Space::LOCAL);
		void SetRotation(const Quaternion& rotationValue, Space space = Space::LOCAL);
		void Rotate(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ, Space space = Space::LOCAL);
		void Rotate(const Vector3& eulerAngles, Space space = Space::LOCAL);
		void RotateAround(const Vector3& point, Axis axis, FLOAT eulerAngle, Space space = Space::LOCAL);
		void RotateAround(const GameObject* targetGameObject, Axis axis, FLOAT eulerAngle, Space space = Space::LOCAL);

	private:
		using Component::Component;
		Transform(const std::string_view& componentName, GameObject* gameObject, const Vector3& localPosition);
		Transform(const std::string_view& componentName, GameObject* gameObject, const Vector3& localPosition, const Vector3& localScale, const Vector3& localEulerAngle);

		Vector3 m_localPosition{ 0.0f, 0.0f, 0.0f };
		Vector3 m_localScale{ 1.0f, 1.0f, 1.0f };
		Quaternion m_localRotation;
	};
}

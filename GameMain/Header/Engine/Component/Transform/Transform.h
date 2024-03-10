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

	class Transform : public Component
	{
		friend class GameObject;

	public:
		Float3 GetPosition(Space space = Space::LOCAL) const;
		Float3 GetScale(Space space = Space::LOCAL) const;
		Float4 GetRotation(Space space = Space::LOCAL) const;

		const Vector3& GetPositionVector(Space space = Space::LOCAL) const;
		const Vector3& GetScaleVector(Space space = Space::LOCAL) const;
		const Quaternion& GetRotationQuaternion(Space space = Space::LOCAL) const;

		Matrix4x4 GetModelMatrix() const;

		void MoveTo(FLOAT x, FLOAT y, FLOAT z, Space space = Space::LOCAL);
		void MoveTo(const Vector3& translateValue, Space space = Space::LOCAL);
		void Translate(FLOAT x, FLOAT y, FLOAT z, Space space = Space::LOCAL);
		void Translate(const Vector3& translateValue, Space space = Space::LOCAL);

		void SetRulerAngles(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ, Space space = Space::LOCAL);
		void SetRulerAngles(const Float3& eulerAngles, Space space = Space::LOCAL);
		void SetRotation(FLOAT x, FLOAT y, FLOAT z, FLOAT w, Space space = Space::LOCAL);
		void SetRotation(const Quaternion& quaternion, Space space = Space::LOCAL);
		void Rotate(FLOAT eulerAngleX, FLOAT eulerAngleY, FLOAT eulerAngleZ, Space space = Space::LOCAL);
		void Rotate(const Float3& eulerAngles, Space space = Space::LOCAL);

	private:
		using Component::Component;
		Transform(const std::string_view& componentName, GameObject* gameObject, const Float3& localPosition);
		Transform(const std::string_view& componentName, GameObject* gameObject, const Float3& localPosition, const Float3& localScale);

		Vector3 m_localPosition{ 0.0f, 0.0f, 0.0f };
		Vector3 m_localScale{ 1.0f, 1.0f, 1.0f };
		Quaternion m_localRotation;

		Vector3 m_worldPosition{ 0.0f, 0.0f, 0.0f };
		Vector3 m_worldScale{ 1.0f, 1.0f, 1.0f };
		Quaternion m_worldRotation;
	};
}

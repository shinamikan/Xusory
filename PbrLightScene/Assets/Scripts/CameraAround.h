#pragma once

#include "../XusoryEngine.h"

using namespace XusoryEngine;

class CameraAround : public Actor
{
	XS_OBJECT;

public:
	void OnStart() override
	{
		camera = GameObject::FindGameObjectByName("Main Camera");
	}

	void OnUpdate() override
	{
		if (Input::GetMouseKeyDown(MouseKeyCode::LEFT) || Input::GetMouseKeyDown(MouseKeyCode::RIGHT))
		{
			m_lastMousePos = Input::GetMousePosition();
		}

		if (Input::GetMouseKey(MouseKeyCode::LEFT))
		{
			const Point nowPos = Input::GetMousePosition();

			const auto posDiffX = static_cast<FLOAT>(nowPos.x - m_lastMousePos.x);
			const auto posDiffY = static_cast<FLOAT>(nowPos.y - m_lastMousePos.y);

			camera->GetTransform()->RotateAround(cameraAroundPoint, Axis::Y, -posDiffX * 20.0f * GameTimer::GetDeltaTime(), Space::WORLD);
			camera->GetTransform()->RotateAround(cameraAroundPoint, Axis::X, posDiffY * 20.0f * GameTimer::GetDeltaTime());

			m_lastMousePos = Input::GetMousePosition();
		}
		else if (Input::GetMouseKey(MouseKeyCode::RIGHT))
		{
			const Point nowPos = Input::GetMousePosition();

			const auto posDiffX = static_cast<FLOAT>(nowPos.x - m_lastMousePos.x);
			const auto posDiffY = static_cast<FLOAT>(nowPos.y - m_lastMousePos.y);

			const auto translateDisX = posDiffX * GameTimer::GetDeltaTime() * 8.0f;
			const auto translateDisY = posDiffY * GameTimer::GetDeltaTime() * 8.0f;

			Vector3 translateValue = Vector3(translateDisX, translateDisY, 0.0f);
			camera->GetTransform()->Translate(translateValue);

			const auto localRotateMat = Quaternion::BuildRotationMatrixByQuaternion(belongsGameObject->GetTransform()->GetRotation());
			cameraAroundPoint += Matrix4x4::PreTransPoint3(translateValue, localRotateMat);

			m_lastMousePos = Input::GetMousePosition();
		}

		if (Input::GetKey(KeyCode::KEY_W))
		{
			camera->GetTransform()->Translate(Vector3(0.0f, 0.0f, 1.0f) * 65.0f * GameTimer::GetDeltaTime());
		}
		if (Input::GetKey(KeyCode::KEY_S))
		{
			camera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -1.0f) * 65.0f * GameTimer::GetDeltaTime());
		}

		const auto mouseWheelDis = Input::GetMouseWheelDistance();
		if (mouseWheelDis != 0)
		{
			camera->GetTransform()->Translate(Vector3(0.0f, 0.0f, mouseWheelDis > 0 ? 1.0f : -1.0f) * 350.0f * GameTimer::GetDeltaTime());
		}
	}

private:
	Point m_lastMousePos;
	Vector3 cameraAroundPoint;

	GameObject* camera = nullptr;
};

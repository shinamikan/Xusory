#pragma once

#include "../ProjectPackage/XusoryEngine.h"
#include "Assets.h"

#include "../Assets/Scripts/CameraAround.h"

using namespace std;
using namespace XusoryEngine;

class SceneMain
{
	friend class GameMain;

public:
	void InitMaterial() const;
	void InitGlobalGameObjects();
	void InitGameObjects();

	Assets assets;

	std::shared_ptr<GameObject> camera;
	std::shared_ptr<GameObject> mainLight;

	std::vector<std::shared_ptr<GameObject>> sphereList;
};

inline void SceneMain::InitMaterial() const
{
	float color = 0.0f;
	for (auto& mat : assets.matSphereList)
	{
		mat->SetFloat3ByName("diffuse", Float3(color, color, color));
		mat->SetFloat3ByName("specular", Float3(0.0f, 0.0f, 0.0f));
		mat->SetFloatByName("gloss", 80.0f);

		color += 0.125f;
	}
}

inline void SceneMain::InitGlobalGameObjects()
{
	camera = std::make_shared<GameObject>("Main Camera");
	camera->GetTransform()->MoveTo(0.0f, 0.0f, -80.0f);
	camera->AddComponent<CameraAround>();
	Camera* cameraPtr = camera->AddComponent<Camera>();
	Camera::mainCamera = cameraPtr;

	mainLight = std::make_shared<GameObject>("Main Light");
	mainLight->GetTransform()->MoveTo(0.0f, 7.5f, 0.0f);
	mainLight->GetTransform()->SetRulerAngles(50.0f, -30.0f, 0.0f);
	Light* light = mainLight->AddComponent<Light>();
	light->lightType = LightType::DIRECTIONAL;
	light->color = Vector3(1.0f, 0.9568f, 0.8392f);
	light->intensity = 1.0f;

	Light::ambient = Vector3(0.12f, 0.12f, 0.12f);
}

inline void SceneMain::InitGameObjects()
{
	float x = 70.0f;
	for (UINT i = 0; i < 8; i++)
	{
		auto sphere = std::make_shared<GameObject>("Sphere");
		sphere->GetTransform()->MoveTo(x, 0.0f, 0.0f);
		sphere->GetTransform()->SetScale(0.3f, 0.3f, 0.3f);
		MeshRenderer* rendererSphere = sphere->AddComponent<MeshRenderer>();
		rendererSphere->mesh = assets.sphereMesh.get();
		rendererSphere->SetMaterial(assets.matSphereList.at(i).get());

		sphereList.push_back(std::move(sphere));
		x -= 20.0f;
	}
}

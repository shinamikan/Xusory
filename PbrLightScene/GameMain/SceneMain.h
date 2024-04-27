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
	std::vector<std::shared_ptr<GameObject>> sphereList1;
	std::vector<std::shared_ptr<GameObject>> sphereList2;
	std::vector<std::shared_ptr<GameObject>> sphereList3;
	std::vector<std::shared_ptr<GameObject>> sphereList4;
};

inline void SceneMain::InitMaterial() const
{
	float roughness = 0.1f;
	for (auto& mat : assets.matSphereList)
	{
		mat->SetFloat3ByName("albedo", Float3(0.5754716f, 0.2202958f, 0.1758988f));
		mat->SetFloatByName("roughness", roughness);
		mat->SetFloatByName("metallic", 0.0f);

		roughness += 0.1f;
	}

	roughness = 0.1f;
	for (auto& mat : assets.matSphereList1)
	{
		mat->SetFloat3ByName("albedo", Float3(0.5754716f, 0.2202958f, 0.1758988f));
		mat->SetFloatByName("roughness", roughness);
		mat->SetFloatByName("metallic", 0.25f);

		roughness += 0.1f;
	}

	roughness = 0.1f;
	for (auto& mat : assets.matSphereList2)
	{
		mat->SetFloat3ByName("albedo", Float3(0.5754716f, 0.2202958f, 0.1758988f));
		mat->SetFloatByName("roughness", roughness);
		mat->SetFloatByName("metallic", 0.5f);

		roughness += 0.1f;
	}

	roughness = 0.1f;
	for (auto& mat : assets.matSphereList3)
	{
		mat->SetFloat3ByName("albedo", Float3(0.5754716f, 0.2202958f, 0.1758988f));
		mat->SetFloatByName("roughness", roughness);
		mat->SetFloatByName("metallic", 0.75f);

		roughness += 0.1f;
	}

	roughness = 0.1f;
	for (auto& mat : assets.matSphereList4)
	{
		mat->SetFloat3ByName("albedo", Float3(0.5754716f, 0.2202958f, 0.1758988f));
		mat->SetFloatByName("roughness", roughness);
		mat->SetFloatByName("metallic", 1.0f);

		roughness += 0.1f;
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
	light->color = Vector3(1.0f, 1.0f, 1.0f);
	light->intensity = 0.8f;

	Light::ambient = Vector3(0.2118f, 0.2275f, 0.2933f);
}

inline void SceneMain::InitGameObjects()
{
	float x = 70.0f;
	for (UINT i = 0; i < 8; i++)
	{
		auto sphere = std::make_shared<GameObject>("Sphere");
		sphere->GetTransform()->MoveTo(x, 40.0f, 0.0f);
		sphere->GetTransform()->SetScale(0.3f, 0.3f, 0.3f);
		MeshRenderer* rendererSphere = sphere->AddComponent<MeshRenderer>();
		rendererSphere->mesh = assets.sphereMesh.get();
		rendererSphere->SetMaterial(assets.matSphereList.at(i).get());

		sphereList.push_back(std::move(sphere));
		x -= 20.0f;
	}

	x = 70.0f;
	for (UINT i = 0; i < 8; i++)
	{
		auto sphere = std::make_shared<GameObject>("Sphere");
		sphere->GetTransform()->MoveTo(x, 20.0f, 0.0f);
		sphere->GetTransform()->SetScale(0.3f, 0.3f, 0.3f);
		MeshRenderer* rendererSphere = sphere->AddComponent<MeshRenderer>();
		rendererSphere->mesh = assets.sphereMesh.get();
		rendererSphere->SetMaterial(assets.matSphereList1.at(i).get());

		sphereList1.push_back(std::move(sphere));
		x -= 20.0f;
	}

	x = 70.0f;
	for (UINT i = 0; i < 8; i++)
	{
		auto sphere = std::make_shared<GameObject>("Sphere");
		sphere->GetTransform()->MoveTo(x, 0.0f, 0.0f);
		sphere->GetTransform()->SetScale(0.3f, 0.3f, 0.3f);
		MeshRenderer* rendererSphere = sphere->AddComponent<MeshRenderer>();
		rendererSphere->mesh = assets.sphereMesh.get();
		rendererSphere->SetMaterial(assets.matSphereList2.at(i).get());

		sphereList2.push_back(std::move(sphere));
		x -= 20.0f;
	}

	x = 70.0f;
	for (UINT i = 0; i < 8; i++)
	{
		auto sphere = std::make_shared<GameObject>("Sphere");
		sphere->GetTransform()->MoveTo(x, -20.0f, 0.0f);
		sphere->GetTransform()->SetScale(0.3f, 0.3f, 0.3f);
		MeshRenderer* rendererSphere = sphere->AddComponent<MeshRenderer>();
		rendererSphere->mesh = assets.sphereMesh.get();
		rendererSphere->SetMaterial(assets.matSphereList3.at(i).get());

		sphereList3.push_back(std::move(sphere));
		x -= 20.0f;
	}

	x = 70.0f;
	for (UINT i = 0; i < 8; i++)
	{
		auto sphere = std::make_shared<GameObject>("Sphere");
		sphere->GetTransform()->MoveTo(x, -40.0f, 0.0f);
		sphere->GetTransform()->SetScale(0.3f, 0.3f, 0.3f);
		MeshRenderer* rendererSphere = sphere->AddComponent<MeshRenderer>();
		rendererSphere->mesh = assets.sphereMesh.get();
		rendererSphere->SetMaterial(assets.matSphereList4.at(i).get());

		sphereList4.push_back(std::move(sphere));
		x -= 20.0f;
	}
}

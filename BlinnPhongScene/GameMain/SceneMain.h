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

	std::shared_ptr<GameObject> sphere;
	std::shared_ptr<GameObject> cube;
	std::shared_ptr<GameObject> teapot;
	std::shared_ptr<GameObject> plane;
};

inline void SceneMain::InitMaterial() const
{
	assets.matSphere->SetFloat3ByName("diffuse", Float3(1.0f, 1.0f, 1.0f));
	assets.matSphere->SetFloat3ByName("specular", Float3(1.0f, 1.0f, 1.0f));
	assets.matSphere->SetFloatByName("gloss", 80.0f);

	assets.matCube->SetFloat3ByName("diffuse", Float3(1.0f, 1.0f, 1.0f));
	assets.matCube->SetFloat3ByName("specular", Float3(1.0f, 1.0f, 1.0f));
	assets.matCube->SetFloatByName("gloss", 80.0f);

	assets.matTeapot->SetFloat3ByName("diffuse", Float3(1.0f, 1.0f, 1.0f));
	assets.matTeapot->SetFloat3ByName("specular", Float3(1.0f, 1.0f, 1.0f));
	assets.matTeapot->SetFloatByName("gloss", 80.0f);

	assets.matPlane->SetFloat3ByName("diffuse", Float3(1.0f, 1.0f, 1.0f));
	assets.matPlane->SetFloat3ByName("specular", Float3(1.0f, 1.0f, 1.0f));
	assets.matPlane->SetFloatByName("gloss", 80.0f);
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
	sphere = std::make_shared<GameObject>("Sphere");
	sphere->GetTransform()->MoveTo(20.0f, 7.5f, 0.0f);
	sphere->GetTransform()->SetScale(0.3f, 0.3f, 0.3f);
	MeshRenderer* rendererSphere = sphere->AddComponent<MeshRenderer>();
	rendererSphere->mesh = assets.sphereMesh.get();
	rendererSphere->SetMaterial(assets.matSphere.get());

	cube = std::make_shared<GameObject>("Cube");
	cube->GetTransform()->MoveTo(0.0f, 3.0f, 0.0f);
	MeshRenderer* rendererCube = cube->AddComponent<MeshRenderer>();
	rendererCube->mesh = assets.cubeMesh.get();
	rendererCube->SetMaterial(assets.matCube.get());

	teapot = std::make_shared<GameObject>("Teapot");
	teapot->GetTransform()->MoveTo(-25.0f, 3.0f, 0.0f);
	teapot->GetTransform()->SetScale(0.8f, 0.8f, 0.8f);
	MeshRenderer* rendererTeapot = teapot->AddComponent<MeshRenderer>();
	rendererTeapot->mesh = assets.teapotMesh.get();
	rendererTeapot->SetMaterial(assets.matTeapot.get());

	plane = std::make_shared<GameObject>("Plane");
	plane->GetTransform()->MoveTo(0.0f, 0.0f, 0.0f);
	plane->GetTransform()->SetScale(4.0f, 4.0f, 4.0f);
	MeshRenderer* rendererPlane = plane->AddComponent<MeshRenderer>();
	rendererPlane->mesh = assets.planeMesh.get();
	rendererPlane->SetMaterial(assets.matPlane.get());
}

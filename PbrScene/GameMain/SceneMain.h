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

	std::shared_ptr<GameObject> plane;
	std::shared_ptr<GameObject> chair1;
	std::shared_ptr<GameObject> chair2;
	std::shared_ptr<GameObject> box1;
	std::shared_ptr<GameObject> box2;
	std::shared_ptr<GameObject> box3;
};

inline void SceneMain::InitMaterial() const
{
	assets.planeMat->SetFloat3ByName("albedo", Float3(0.2f, 0.2f, 0.2f));
	assets.planeMat->SetFloatByName("roughness", 0.6f);
	assets.planeMat->SetFloatByName("metallic", 0.5f);

	assets.chairMat1->SetTextureByName("albedoTex", assets.chairTex1.get());
	assets.chairMat1->SetFloatByName("roughness", 0.5f);
	assets.chairMat1->SetFloatByName("metallic", 0.8f);

	assets.chairMat2->SetTextureByName("albedoTex", assets.chairTex2.get());
	assets.chairMat2->SetFloatByName("roughness", 0.5f);
	assets.chairMat2->SetFloatByName("metallic", 0.8f);

	assets.boxMat1->SetTextureByName("albedoTex", assets.boxTex.get());
	assets.boxMat1->SetFloatByName("roughness", 0.8f);
	assets.boxMat1->SetFloatByName("metallic", 0.2f);

	assets.boxMat2->SetTextureByName("albedoTex", assets.boxTex.get());
	assets.boxMat2->SetFloatByName("roughness", 0.8f);
	assets.boxMat2->SetFloatByName("metallic", 0.2f);

	assets.boxMat3->SetTextureByName("albedoTex", assets.boxTex.get());
	assets.boxMat3->SetFloatByName("roughness", 0.8f);
	assets.boxMat3->SetFloatByName("metallic", 0.2f);
}

inline void SceneMain::InitGlobalGameObjects()
{
	camera = std::make_shared<GameObject>("Main Camera");
	camera->GetTransform()->MoveTo(0.0f, 0.0f, 160.0f);
	camera->GetTransform()->SetRulerAngles(0.0f, 180.0f, 0.0f);
	camera->AddComponent<CameraAround>();
	Camera* cameraPtr = camera->AddComponent<Camera>();
	Camera::mainCamera = cameraPtr;

	mainLight = std::make_shared<GameObject>("Main Light");
	mainLight->GetTransform()->MoveTo(0.0f, 7.5f, 0.0f);
	mainLight->GetTransform()->SetRulerAngles(50.0f, -30.0f, 0.0f);
	Light* light = mainLight->AddComponent<Light>();
	light->lightType = LightType::DIRECTIONAL;
	light->color = Vector3(1.0f, 1.0f, 1.0f);
	light->intensity = 1.2f;

	Light::ambient = Vector3(0.2118f, 0.2275f, 0.2933f);
}

inline void SceneMain::InitGameObjects()
{
	plane = std::make_shared<GameObject>("Plane");
	plane->GetTransform()->MoveTo(0.0f, -20.0f, 0.0f);
	plane->GetTransform()->SetScale(7.0f, 7.0f, 7.0f);
	MeshRenderer* rendererPlane = plane->AddComponent<MeshRenderer>();
	rendererPlane->mesh = assets.planeMesh.get();
	rendererPlane->SetMaterial(assets.planeMat.get());

	chair1 = std::make_shared<GameObject>("Chair1");
	chair1->GetTransform()->MoveTo(-20.0f, -20.0f, 15.0f);
	chair1->GetTransform()->SetRulerAngles(0.0f, 20.0f, 0.0f);
	MeshRenderer* rendererChair1 = chair1->AddComponent<MeshRenderer>();
	rendererChair1->mesh = assets.chairMesh.get();
	rendererChair1->SetMaterial(assets.chairMat1.get());

	chair2 = std::make_shared<GameObject>("Chair2");
	chair2->GetTransform()->MoveTo(20.0f, -20.0f, 15.0f);
	chair2->GetTransform()->SetRulerAngles(0.0f, -20.0f, 0.0f);
	MeshRenderer* rendererChair2 = chair2->AddComponent<MeshRenderer>();
	rendererChair2->mesh = assets.chairMesh.get();
	rendererChair2->SetMaterial(assets.chairMat2.get());

	box1 = std::make_shared<GameObject>("Box1");
	box1->GetTransform()->MoveTo(17.0f, -20.0f, -32.0f);
	box1->GetTransform()->SetScale(0.7f, 0.7f, 0.7f);
	box1->GetTransform()->SetRulerAngles(0.0f, 10.0f, 0.0f);
	MeshRenderer* rendererBox1 = box1->AddComponent<MeshRenderer>();
	rendererBox1->mesh = assets.boxMesh.get();
	rendererBox1->SetMaterial(assets.boxMat1.get());

	box2 = std::make_shared<GameObject>("Box2");
	box2->GetTransform()->MoveTo(-7.0f, -20.0f, -32.0f);
	box2->GetTransform()->SetScale(0.7f, 0.7f, 0.7f);
	box2->GetTransform()->SetRulerAngles(0.0f, 0.0f, 0.0f);
	MeshRenderer* rendererBox2 = box2->AddComponent<MeshRenderer>();
	rendererBox2->mesh = assets.boxMesh.get();
	rendererBox2->SetMaterial(assets.boxMat2.get());

	box3 = std::make_shared<GameObject>("Box2");
	box3->GetTransform()->MoveTo(5.0f, 1.3f, -30.0f);
	box3->GetTransform()->SetScale(0.7f, 0.7f, 0.7f);
	box3->GetTransform()->SetRulerAngles(0.0f, -12.0f, 0.0f);
	MeshRenderer* rendererBox3 = box3->AddComponent<MeshRenderer>();
	rendererBox3->mesh = assets.boxMesh.get();
	rendererBox3->SetMaterial(assets.boxMat3.get());
}

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
	std::vector<std::shared_ptr<GameObject>> mikuObj;
};

inline void SceneMain::InitMaterial() const
{
	assets.matBody->SetTextureByName("diffuse", assets.texBody.get());
	assets.matHead->SetTextureByName("diffuse", assets.texHead.get());
}

inline void SceneMain::InitGlobalGameObjects()
{
	camera = std::make_shared<GameObject>("Main Camera");
	camera->GetTransform()->MoveTo(0.0f, 0.0f, -150.0f);
	camera->AddComponent<CameraAround>();
	Camera* cameraPtr = camera->AddComponent<Camera>();
	Camera::mainCamera = cameraPtr;
}

inline void SceneMain::InitGameObjects()
{
	for (const auto& roleMesh : assets.mikuMesh)
	{
		auto gameObj = std::make_shared<GameObject>(roleMesh->GetName());
		gameObj->GetTransform()->SetRulerAngles(0.0f, -180.0f, 0.0f);
		MeshRenderer* renderer = gameObj->AddComponent<MeshRenderer>();
		renderer->mesh = roleMesh.get();

		mikuObj.emplace_back(gameObj);
	}

	mikuObj.at(0)->GetComponent<MeshRenderer>()->SetMaterial(assets.matHead.get()); //eyes
	mikuObj.at(1)->GetComponent<MeshRenderer>()->SetMaterial(assets.matHead.get()); //face
	mikuObj.at(2)->GetComponent<MeshRenderer>()->SetMaterial(assets.matHead.get()); //head
	mikuObj.at(3)->GetComponent<MeshRenderer>()->SetMaterial(assets.matHead.get()); //bangs
	mikuObj.at(4)->GetComponent<MeshRenderer>()->SetMaterial(assets.matHead.get()); //hair
	mikuObj.at(5)->GetComponent<MeshRenderer>()->SetMaterial(assets.matHead.get()); //headwear

	mikuObj.at(6)->GetComponent<MeshRenderer>()->SetMaterial(assets.matBody.get()); //body
	mikuObj.at(7)->GetComponent<MeshRenderer>()->SetMaterial(assets.matBody.get()); //hands
	mikuObj.at(8)->GetComponent<MeshRenderer>()->SetMaterial(assets.matBody.get()); //legs
	mikuObj.at(9)->GetComponent<MeshRenderer>()->SetMaterial(assets.matBody.get()); //skirt
	mikuObj.at(10)->GetComponent<MeshRenderer>()->SetMaterial(assets.matBody.get()); //tie
}

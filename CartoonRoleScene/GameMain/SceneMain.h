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

	std::vector<std::shared_ptr<GameObject>> ruanMei;
	std::shared_ptr<GameObject> ruan;
};

inline void SceneMain::InitMaterial() const
{
	assets.clothesMat->SetTextureByName("diffuse", assets.clothesTex.get());
	assets.faceMat->SetTextureByName("diffuse", assets.faceTex.get());
	assets.hairMat->SetTextureByName("diffuse", assets.hairTex.get());
	assets.ruanMat->SetTextureByName("diffuse", assets.ruanTex.get());
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
	for (const auto& roleMesh : assets.ruanMeiMesh)
	{
		auto gameObj = std::make_shared<GameObject>(roleMesh->GetName());
		gameObj->GetTransform()->MoveTo(0.0f, -50.0f, 0.0f);
		gameObj->GetTransform()->SetScale(5.0f, 5.0f, 5.0f);
		gameObj->GetTransform()->SetRulerAngles(0.0f, -180.0f, 0.0f);
		MeshRenderer* renderer = gameObj->AddComponent<MeshRenderer>();
		renderer->mesh = roleMesh.get();

		ruanMei.emplace_back(gameObj);
	}

	ruanMei.at(0)->GetComponent<MeshRenderer>()->SetMaterial(assets.hairMat.get());
	ruanMei.at(1)->GetComponent<MeshRenderer>()->SetMaterial(assets.hairMat.get());

	ruanMei.at(2)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(3)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(4)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(5)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(6)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(7)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(8)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(9)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(10)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(11)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(12)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(13)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(14)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(15)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(16)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(17)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(18)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());
	ruanMei.at(19)->GetComponent<MeshRenderer>()->SetMaterial(assets.clothesMat.get());

	ruanMei.at(20)->GetComponent<MeshRenderer>()->SetMaterial(assets.faceMat.get());
	ruanMei.at(21)->GetComponent<MeshRenderer>()->SetMaterial(assets.faceMat.get());
	ruanMei.at(22)->GetComponent<MeshRenderer>()->SetMaterial(assets.faceMat.get());
	ruanMei.at(23)->GetComponent<MeshRenderer>()->SetMaterial(assets.faceMat.get());
	ruanMei.at(24)->GetComponent<MeshRenderer>()->SetMaterial(assets.faceMat.get());
	ruanMei.at(25)->GetComponent<MeshRenderer>()->SetMaterial(assets.faceMat.get());
	ruanMei.at(26)->GetComponent<MeshRenderer>()->SetMaterial(assets.faceMat.get());

	ruan = std::make_shared<GameObject>("ruan");
	ruan->GetTransform()->MoveTo(0.0f, -50.0f, 0.0f);
	ruan->GetTransform()->SetScale(5.0f, 5.0f, 5.0f);
	ruan->GetTransform()->SetRulerAngles(0.0f, -180.0f, 0.0f);
	MeshRenderer* renderer = ruan->AddComponent<MeshRenderer>();
	renderer->mesh = assets.ruanMesh.get();
	renderer->SetMaterial(assets.ruanMat.get());
}

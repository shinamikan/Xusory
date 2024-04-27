#pragma once

#include "../ProjectPackage/XusoryEngine.h"

using namespace std;
using namespace XusoryEngine;

class Assets
{
	friend class GameMain;

public:
	void LoadMesh();
	void LoadTexture();
	void LoadShader();
	void LoadMaterial();

	std::shared_ptr<Mesh> planeMesh;
	std::shared_ptr<Mesh> chairMesh;
	std::shared_ptr<Mesh> boxMesh;

	std::shared_ptr<Texture> chairTex1;
	std::shared_ptr<Texture> chairTex2;
	std::shared_ptr<Texture> boxTex;

	std::shared_ptr<Shader> pbrShader;
	std::shared_ptr<Shader> pbrTexShader;

	std::shared_ptr<Material> planeMat;
	std::shared_ptr<Material> chairMat1;
	std::shared_ptr<Material> chairMat2;
	std::shared_ptr<Material> boxMat1;
	std::shared_ptr<Material> boxMat2;
	std::shared_ptr<Material> boxMat3;
};

inline void Assets::LoadMesh()
{
	planeMesh = ResourceLoader::Load<Mesh>(TEXT("Assets/Models/Plane.obj"), true);
	chairMesh = ResourceLoader::Load<Mesh>(TEXT("Assets/Models/Chair/Chair.obj"), true);
	boxMesh = ResourceLoader::Load<Mesh>(TEXT("Assets/Models/Box/Box.obj"), true);
}

inline void Assets::LoadTexture()
{
	chairTex1 = ResourceLoader::Load<Texture>(TEXT("Assets/Models/Chair/Texture/Albedo.dds"), true);
	chairTex2 = ResourceLoader::Load<Texture>(TEXT("Assets/Models/Chair/Texture/Albedo1.dds"), true);
	boxTex = ResourceLoader::Load<Texture>(TEXT("Assets/Models/Box/Texture/Albedo.dds"), true);
}

inline void Assets::LoadShader()
{
	pbrShader = ResourceLoader::Load<Shader>(TEXT("ProjectPackage/XsShaders/Standard/Pbr.hlsl"), true);
	pbrTexShader = ResourceLoader::Load<Shader>(TEXT("ProjectPackage/XsShaders/Standard/PbrTex.hlsl"), true);
}

inline void Assets::LoadMaterial()
{
	planeMat = std::make_shared<Material>(pbrShader.get());
	chairMat1 = std::make_shared<Material>(pbrTexShader.get());
	chairMat2 = std::make_shared<Material>(pbrTexShader.get());
	boxMat1 = std::make_shared<Material>(pbrTexShader.get());
	boxMat2 = std::make_shared<Material>(pbrTexShader.get());
	boxMat3 = std::make_shared<Material>(pbrTexShader.get());

	GraphicsManager::AddMaterial(planeMat.get());
	GraphicsManager::AddMaterial(chairMat1.get());
	GraphicsManager::AddMaterial(chairMat2.get());
	GraphicsManager::AddMaterial(boxMat1.get());
	GraphicsManager::AddMaterial(boxMat2.get());
	GraphicsManager::AddMaterial(boxMat3.get());
}

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

	std::vector<std::shared_ptr<Mesh>> ruanMeiMesh;
	std::shared_ptr<Mesh> ruanMesh;

	std::shared_ptr<Texture> clothesTex;
	std::shared_ptr<Texture> faceTex;
	std::shared_ptr<Texture> hairTex;
	std::shared_ptr<Texture> ruanTex;

	std::shared_ptr<Shader> unlitShader;

	std::shared_ptr<Material> clothesMat;
	std::shared_ptr<Material> faceMat;
	std::shared_ptr<Material> hairMat;
	std::shared_ptr<Material> ruanMat;
};

inline void Assets::LoadMesh()
{
	ruanMeiMesh = ResourceLoader::LoadSeveral<Mesh>(TEXT("Assets/Models/RuanMei/Ruan Mei.obj"), true);
	ruanMesh = ResourceLoader::Load<Mesh>(TEXT("Assets/Models/RuanMei/Ruan.obj"), true);
}

inline void Assets::LoadTexture()
{
	clothesTex = ResourceLoader::Load<Texture>(TEXT("Assets/Models/RuanMei/Texture/clothes.dds"), true);
	faceTex = ResourceLoader::Load<Texture>(TEXT("Assets/Models/RuanMei/Texture/face.dds"), true);
	hairTex = ResourceLoader::Load<Texture>(TEXT("Assets/Models/RuanMei/Texture/hair.dds"), true);
	ruanTex = ResourceLoader::Load<Texture>(TEXT("Assets/Models/RuanMei/Texture/ruan.dds"), true);
}

inline void Assets::LoadShader()
{
	unlitShader = ResourceLoader::Load<Shader>(TEXT("ProjectPackage/XsShaders/Standard/Unlit.hlsl"), true);
}

inline void Assets::LoadMaterial()
{
	clothesMat = std::make_shared<Material>(unlitShader.get());
	faceMat = std::make_shared<Material>(unlitShader.get());
	hairMat = std::make_shared<Material>(unlitShader.get());
	ruanMat = std::make_shared<Material>(unlitShader.get());

	GraphicsManager::AddMaterial(clothesMat.get());
	GraphicsManager::AddMaterial(faceMat.get());
	GraphicsManager::AddMaterial(hairMat.get());
	GraphicsManager::AddMaterial(ruanMat.get());
}

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

	std::vector<std::shared_ptr<Mesh>> mikuMesh;

	std::shared_ptr<Texture> texBody;
	std::shared_ptr<Texture> texHead;

	std::shared_ptr<Shader> shader;

	std::shared_ptr<Material> matBody;
	std::shared_ptr<Material> matHead;
};

inline void Assets::LoadMesh()
{
	mikuMesh = ResourceLoader::LoadSeveral<Mesh>(TEXT("Assets/Models/Miku/miku.obj"), true);
}

inline void Assets::LoadTexture()
{
	texBody = ResourceLoader::Load<Texture>(TEXT("Assets/Models/Miku/Miku_body.dds"), true);
	texHead = ResourceLoader::Load<Texture>(TEXT("Assets/Models/Miku/Miku_head.dds"), true);
}

inline void Assets::LoadShader()
{
	shader = ResourceLoader::Load<Shader>(TEXT("ProjectPackage/XsShaders/Standard/Unlit.hlsl"), true);
}

inline void Assets::LoadMaterial()
{
	matBody = std::make_shared<Material>(shader.get());
	matHead = std::make_shared<Material>(shader.get());

	GraphicsManager::AddMaterial(matBody.get());
	GraphicsManager::AddMaterial(matHead.get());
}

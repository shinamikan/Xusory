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

	std::shared_ptr<Mesh> sphereMesh;

	std::shared_ptr<Shader> blinnPhongShader;

	std::vector<std::shared_ptr<Material>> matSphereList;
};

inline void Assets::LoadMesh()
{
	sphereMesh = ResourceLoader::Load<Mesh>(TEXT("Assets/Models/Sphere.obj"), true);
}

inline void Assets::LoadTexture()
{

}

inline void Assets::LoadShader()
{
	blinnPhongShader = ResourceLoader::Load<Shader>(TEXT("ProjectPackage/XsShaders/Standard/BlinnPhong.hlsl"), true);
}

inline void Assets::LoadMaterial()
{
	for (UINT i = 0; i < 8; i++)
	{
		matSphereList.push_back(std::make_shared<Material>(blinnPhongShader.get()));
		GraphicsManager::AddMaterial((matSphereList.end() - 1)->get());
	}
}

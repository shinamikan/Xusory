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

	std::shared_ptr<Shader> pbrShader;

	std::vector<std::shared_ptr<Material>> matSphereList;
	std::vector<std::shared_ptr<Material>> matSphereList1;
	std::vector<std::shared_ptr<Material>> matSphereList2;
	std::vector<std::shared_ptr<Material>> matSphereList3;
	std::vector<std::shared_ptr<Material>> matSphereList4;
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
	pbrShader = ResourceLoader::Load<Shader>(TEXT("ProjectPackage/XsShaders/Standard/Pbr.hlsl"), true);
}

inline void Assets::LoadMaterial()
{
	for (UINT i = 0; i < 8; i++)
	{
		matSphereList.push_back(std::make_shared<Material>(pbrShader.get()));
		GraphicsManager::AddMaterial((matSphereList.end() - 1)->get());
	}
	for (UINT i = 0; i < 8; i++)
	{
		matSphereList1.push_back(std::make_shared<Material>(pbrShader.get()));
		GraphicsManager::AddMaterial((matSphereList1.end() - 1)->get());
	}
	for (UINT i = 0; i < 8; i++)
	{
		matSphereList2.push_back(std::make_shared<Material>(pbrShader.get()));
		GraphicsManager::AddMaterial((matSphereList2.end() - 1)->get());
	}
	for (UINT i = 0; i < 8; i++)
	{
		matSphereList3.push_back(std::make_shared<Material>(pbrShader.get()));
		GraphicsManager::AddMaterial((matSphereList3.end() - 1)->get());
	}
	for (UINT i = 0; i < 8; i++)
	{
		matSphereList4.push_back(std::make_shared<Material>(pbrShader.get()));
		GraphicsManager::AddMaterial((matSphereList4.end() - 1)->get());
	}
}

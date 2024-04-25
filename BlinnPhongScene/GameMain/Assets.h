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
	std::shared_ptr<Mesh> cubeMesh;
	std::shared_ptr<Mesh> teapotMesh;
	std::shared_ptr<Mesh> planeMesh;

	std::shared_ptr<Shader> blinnPhongShader;

	std::shared_ptr<Material> matSphere;
	std::shared_ptr<Material> matTeapot;
	std::shared_ptr<Material> matCube;
	std::shared_ptr<Material> matPlane;
};

inline void Assets::LoadMesh()
{
	sphereMesh = ResourceLoader::Load<Mesh>(TEXT("Assets/Models/Sphere.obj"), true);
	cubeMesh = ResourceLoader::Load<Mesh>(TEXT("Assets/Models/Cube.obj"), true);
	teapotMesh = ResourceLoader::Load<Mesh>(TEXT("Assets/Models/Teapot.obj"), true);
	planeMesh = ResourceLoader::Load<Mesh>(TEXT("Assets/Models/Plane.obj"), true);
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
	matSphere = std::make_shared<Material>(blinnPhongShader.get());
	matCube = std::make_shared<Material>(blinnPhongShader.get());
	matTeapot = std::make_shared<Material>(blinnPhongShader.get());
	matPlane = std::make_shared<Material>(blinnPhongShader.get());

	GraphicsManager::AddMaterial(matSphere.get());
	GraphicsManager::AddMaterial(matCube.get());
	GraphicsManager::AddMaterial(matTeapot.get());
	GraphicsManager::AddMaterial(matPlane.get());
}

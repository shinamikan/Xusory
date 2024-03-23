#include <iostream>
#include <string>
#include <vector>
#include <future>

#define DLL_IMPORT

#include "GameWindow.h"

//#include "pix3.h"

#pragma comment(lib, "XusoryEngine.lib")

using namespace std;
using namespace XusoryEngine;

//std::shared_ptr<Mesh> meshList;
//std::shared_ptr<Texture> texture;
//std::shared_ptr<Texture> texture1;
//std::shared_ptr<Texture> texture2;

std::vector<std::shared_ptr<Mesh>> meshList;

std::shared_ptr<Texture> texBody;
std::shared_ptr<Texture> texHead;

std::shared_ptr<Shader> shader;
std::shared_ptr<Material> matBody;
std::shared_ptr<Material> matHead;

//std::shared_ptr<GameObject> gameObj;
//std::shared_ptr<GameObject> gameObj1;

std::vector<std::shared_ptr<GameObject>> mikuObj;

std::shared_ptr<GameObject> camera;

typedef void(*IntFunc)();
class TestClass
{
	REFLECT_CLASS;

	REFLECT_FUNCTION(TestClass, public, void, TestFunc);
	REFLECT_VARIABLE_WITH_VALUE(private, int, num, 5);
};
INIT_STATIC_REFLECTOR(TestClass);

void TestClass::TestFunc()
{
	Debug::LogInfo(999);
}

TestClass test;

class UserActor : public Actor
{
	XS_OBJECT;

public:
	void OnAwake() override
	{
		Debug::LogInfo("OnAwake");
	}

	void OnUpdate() override
	{
		//gameObj1->GetTransform()->RotateAround(Vector3::Zero, Axis::Y, 20.0f * GameTimer::GetDeltaTime());

		//Debug::LogInfo(GameTimer::GetDeltaTime());

		if (Input::GetKeyDown(KeyCode::KEY_G))
		{
			Debug::LogInfo(test.GetField<int>("num"));
			Debug::LogInfo(TestClass::GetFieldInfo("num").access);
			Debug::LogInfo(TestClass::GetFieldInfo("num").type);

			auto func = test.GetField<TestClass::TestFuncType>("TestFunc");
			(test.*func)();
		}

		if (Input::GetKey(KeyCode::KEY_W))
		{
			camera->GetTransform()->Translate(Vector3(0.0f, 0.0f, 1.0f) * 0.4f);
		}
		if (Input::GetKey(KeyCode::KEY_S))
		{
			camera->GetTransform()->Translate(Vector3(0.0f, 0.0f, -1.0f) * 0.4f);
		}
		if (Input::GetKey(KeyCode::KEY_A))
		{
			camera->GetTransform()->Translate(Vector3(0.0f, 1.0f, 0.0f) * 0.4f);
		}
		if (Input::GetKey(KeyCode::KEY_D))
		{
			camera->GetTransform()->Translate(Vector3(0.0f, -1.0f, 0.0f) * 0.4f);
		}

		if (Input::GetMouseKeyDown(MouseKeyCode::LEFT))
		{
			m_lastMousePos = Input::GetMousePosition();
		}
		if (Input::GetMouseKey(MouseKeyCode::LEFT))
		{
			Point nowPos = Input::GetMousePosition();

			const auto posDiffX = static_cast<FLOAT>(nowPos.x - m_lastMousePos.x);
			const auto posDiffY = static_cast<FLOAT>(nowPos.y - m_lastMousePos.y);

			Debug::LogInfo("posDiffX: ", posDiffX, "  posDiffY: ", posDiffY);

			camera->GetTransform()->Rotate(-posDiffY * 0.05f, posDiffX * 0.05f, 0.0f);
			m_lastMousePos = Input::GetMousePosition();
		}
	}

private:
	Point m_lastMousePos;
};

int WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(8);

	//PIXLoadLatestWinPixGpuCapturerLibrary();

	Window* gameWindow = nullptr;
	BOOL isInitError = false;

	try
	{
		Console::CreateConsole();
		Console::RedirectToStd();
		Console::SetTitle(TEXT("Xusory Console"));

		GraphicsManager::BuildGraphicsManager(GraphicsLibrary::Direct3D_12);

		WindowFactory::StartNewWindowClass();
		WindowFactory::SetWindowCursor(SysCursor::ARROW);
		WindowFactory::SetWindowIcon(SysIcon::APPLICATION);
		WindowFactory::RegisterWindowClass(hIns, TEXT("MainWindow"));

		gameWindow = WindowFactory::CreateWindowInstance<GameWindow>(TEXT("MainWindow"), TEXT("Application"), 800, 600, true);

		SceneManager::LoadScene(TEXT(""));

		/*meshList = ResourceLoader::Load<Mesh>(TEXT("Resource/Model/cube.obj"), true);
		texture = ResourceLoader::Load<Texture>(TEXT("Texture/kasukasu.dds"), true);
		texture1 = ResourceLoader::Load<Texture>(TEXT("Texture/kunkun.dds"), true);
		texture2 = ResourceLoader::Load<Texture>(TEXT("Texture/csk.dds"), true);*/

		meshList = ResourceLoader::LoadSeveral<Mesh>(TEXT("miku/miku.obj"), true);
		texBody = ResourceLoader::Load<Texture>(TEXT("miku/miku_body.dds"), true);
		texHead = ResourceLoader::Load<Texture>(TEXT("miku/miku_head.dds"), true);
		
		shader = ResourceLoader::Load<Shader>(TEXT("Shaders/color2.hlsl"), true);

		matBody = std::make_shared<Material>(shader.get());
		matHead = std::make_shared<Material>(shader.get());

		GraphicsManager::AddMaterial(matBody.get());
		GraphicsManager::AddMaterial(matHead.get());
		GraphicsManager::BuildAllGraphicsObject();

		matBody->SetTextureByName("Diffuse", texBody.get());
		matHead->SetTextureByName("Diffuse", texHead.get());

		/*gameObj = std::make_shared<GameObject>("Go");
		MeshRenderer* renderer = gameObj->AddComponent<MeshRenderer>();
		renderer->mesh = meshList.at(0).get();
		renderer->material = matBody.get();
		gameObj->AddComponent<UserActor>();

		gameObj1 = std::make_shared<GameObject>("Go1");
		MeshRenderer* renderer1 = gameObj1->AddComponent<MeshRenderer>();
		renderer1->mesh = meshList.at(0).get();
		renderer1->material = matHead.get();
		gameObj1->GetTransform()->MoveTo(-50.0f, 0.0f, 0.0f);*/

		for (const auto& roleMesh : meshList)
		{
			auto gameObj = std::make_shared<GameObject>(roleMesh->GetName());
			MeshRenderer* renderer = gameObj->AddComponent<MeshRenderer>();
			renderer->mesh = roleMesh.get();

			mikuObj.emplace_back(gameObj);
		}

		mikuObj.at(0)->GetComponent<MeshRenderer>()->material = matHead.get(); //eyes
		mikuObj.at(1)->GetComponent<MeshRenderer>()->material = matHead.get(); //face
		mikuObj.at(2)->GetComponent<MeshRenderer>()->material = matHead.get(); //head
		mikuObj.at(3)->GetComponent<MeshRenderer>()->material = matHead.get(); //bangs
		mikuObj.at(4)->GetComponent<MeshRenderer>()->material = matHead.get(); //hair
		mikuObj.at(5)->GetComponent<MeshRenderer>()->material = matHead.get(); //headwear

		mikuObj.at(6)->GetComponent<MeshRenderer>()->material = matBody.get(); //body
		mikuObj.at(7)->GetComponent<MeshRenderer>()->material = matBody.get(); //hands
		mikuObj.at(8)->GetComponent<MeshRenderer>()->material = matBody.get(); //legs
		mikuObj.at(9)->GetComponent<MeshRenderer>()->material = matBody.get(); //skirt
		mikuObj.at(10)->GetComponent<MeshRenderer>()->material = matBody.get(); //tie

		camera = std::make_shared<GameObject>("Main Camera");
		Camera* cameraPtr = camera->AddComponent<Camera>();
		camera->GetTransform()->MoveTo(0.0f, 0.0f, -70.0f);
		camera->AddComponent<UserActor>();
		Camera::mainCamera = cameraPtr;

		gameWindow->Show();
	}
	catch (const std::exception& e)
	{
		StdErrorOutput(e);
		isInitError = true;
	}

	if (!isInitError)
	{
		gameWindow->MessageLoop();
	}

	Console::SetTextColor(ConsoleTextColor::COLOR_WHITE);
	system("pause");
	return 0;
}

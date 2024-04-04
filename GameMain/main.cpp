#include <iostream>
#include <string>
#include <vector>
#include <future>

#define DLL_IMPORT

#include "GameWindow.h"

#include "pix3.h"

#pragma comment(lib, "XusoryEngine.lib")

using namespace std;
using namespace XusoryEngine;

std::vector<std::shared_ptr<Mesh>> mikuMesh;

std::shared_ptr<Texture> texBody;
std::shared_ptr<Texture> texHead;

std::shared_ptr<Shader> shader;
std::shared_ptr<Material> matBody;
std::shared_ptr<Material> matHead;

std::shared_ptr<GameObject> miku;
std::vector<std::shared_ptr<GameObject>> mikuObj;

std::shared_ptr<GameObject> camera;
std::shared_ptr<GameObject> mainLight;

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
		//Debug::LogInfo(GameTimer::GetDeltaTime());
		if (Input::GetKeyDown(KeyCode::ALPHA_0))
		{
			std::cout << 1;
		}

		if (Input::GetKey(KeyCode::KEY_Q))
		{
			miku->GetTransform()->Translate(Vector3(1.0f, 0.0f, 0.0f) * 0.4f);
		}
		if (Input::GetKey(KeyCode::KEY_E))
		{
			miku->GetTransform()->Translate(Vector3(-1.0f, 0.0f, 0.0f) * 0.4f);
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

	PIXLoadLatestWinPixGpuCapturerLibrary();

#if defined(DEBUG) || defined(_DEBUG) 
	// Enable the D3D12 debug layer.
	{
		Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
		D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
		debugController->EnableDebugLayer();
	}
#endif

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

		mikuMesh = ResourceLoader::LoadSeveral<Mesh>(TEXT("miku/miku.obj"), true);
		texBody = ResourceLoader::Load<Texture>(TEXT("miku/miku_body.dds"), true);
		texHead = ResourceLoader::Load<Texture>(TEXT("miku/miku_head.dds"), true);
		
		shader = ResourceLoader::Load<Shader>(TEXT("Shaders/color2.hlsl"), true);

		matBody = std::make_shared<Material>(shader.get());
		matHead = std::make_shared<Material>(shader.get());

		GraphicsManager::AddMaterial(matBody.get());
		GraphicsManager::AddMaterial(matHead.get());
		GraphicsManager::BuildAllGraphicsObject();

		matBody->SetTextureByName("diffuse", texBody.get());
		matHead->SetTextureByName("diffuse", texHead.get());

		miku = std::make_shared<GameObject>("miku");

		for (const auto& roleMesh : mikuMesh)
		{
			auto gameObj = std::make_shared<GameObject>(roleMesh->GetName());
			gameObj->GetTransform()->SetRulerAngles(0.0f, -180.0f, 0.0f);

			MeshRenderer* renderer = gameObj->AddComponent<MeshRenderer>();
			renderer->mesh = roleMesh.get();

			miku->AddChildGameObject(gameObj.get());
			mikuObj.emplace_back(gameObj);
		}

		mikuObj.at(0)->GetComponent<MeshRenderer>()->SetMaterial(matHead.get()); //eyes
		mikuObj.at(1)->GetComponent<MeshRenderer>()->SetMaterial(matHead.get()); //face
		mikuObj.at(2)->GetComponent<MeshRenderer>()->SetMaterial(matHead.get()); //head
		mikuObj.at(3)->GetComponent<MeshRenderer>()->SetMaterial(matHead.get()); //bangs
		mikuObj.at(4)->GetComponent<MeshRenderer>()->SetMaterial(matHead.get()); //hair
		mikuObj.at(5)->GetComponent<MeshRenderer>()->SetMaterial(matHead.get()); //headwear

		mikuObj.at(6)->GetComponent<MeshRenderer>()->SetMaterial(matBody.get()); //body
		mikuObj.at(7)->GetComponent<MeshRenderer>()->SetMaterial(matBody.get()); //hands
		mikuObj.at(8)->GetComponent<MeshRenderer>()->SetMaterial(matBody.get()); //legs
		mikuObj.at(9)->GetComponent<MeshRenderer>()->SetMaterial(matBody.get()); //skirt
		mikuObj.at(10)->GetComponent<MeshRenderer>()->SetMaterial(matBody.get()); //tie

		camera = std::make_shared<GameObject>("Main Camera");
		Camera* cameraPtr = camera->AddComponent<Camera>();
		camera->GetTransform()->MoveTo(0.0f, 0.0f, -70.0f);
		camera->AddComponent<UserActor>();
		Camera::mainCamera = cameraPtr;

		mainLight = std::make_shared<GameObject>("Main Light");
		Light* light = mainLight->AddComponent<Light>();
		light->color = Vector3(1.0f, 1.0f, 1.0f);

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

#include <iostream>
#include <string>
#include <vector>
#include <future>

#define DLL_IMPORT

#include "Header/XusoryEngine.h"
#include "GameMainDefine.h"

#include "pix3.h"
#include "Header/Core/Graphics/Texture.h"

#pragma comment(lib, "XusoryEngine.lib")

using namespace std;
using namespace XusoryEngine;

std::shared_ptr<Mesh> mesh;
std::shared_ptr<Texture> texture;
std::shared_ptr<Shader> shader;
std::shared_ptr<Material> material;

std::shared_ptr<GameObject> gameObj;
std::shared_ptr<GameObject> camera;

class UserRenderPipeline : public RenderPipeline
{
public:
	UserRenderPipeline() = default;

	void Render(CommandContext* commandContext) override
	{
		commandContext->BeginCommand();
		commandContext->ClearRenderTarget({ 0.235294133f, 0.701960802f, 0.443137288f, 1.f });
		//commandContext->ClearRenderTarget({ 0.0f, 0.0f, 0.0f, 1.f });
		commandContext->ClearDepth(1.0f);
		commandContext->ClearStencil(0);

		const MeshRenderer* meshRenderer = gameObj->GetComponent<MeshRenderer>();
		
		commandContext->SetMaterial(meshRenderer->material);
		commandContext->SetMesh(meshRenderer->mesh);
		commandContext->DrawMesh();
		commandContext->EndCommand();
	}
};

class UserActor : public Actor
{
public:
	void OnAwake() override
	{
		Debug::LogInfo("OnAwake");
	}

	void OnUpdate() override
	{
		//Debug::LogInfo("OnUpdate");
	}

private:
	using Actor::Actor;
};

std::shared_ptr<UserRenderPipeline> renderPipeline;

Vector3 cameraPosition{ 0.0f, 0.0f, 40.0f };
Vector3 targetPosition{ 0.0f, 0.0f, 0.0f };
Vector3 worldUp{ 0.0f, 1.0f, 0.0f };

typedef void(*IntFunc)();

class TestClass
{
	REFLECT_CLASS;

	REFLECT_FUNC_FIELD(TestClass, public, void, TestFunc);
	REFLECT_FIELD_WITH_VALUE(private, int, m_int, 5);
};
INIT_STATIC_REFLECTOR(TestClass);

void TestClass::TestFunc()
{
	Debug::LogInfo(999);
}

TestClass test;

class GameWindow : public Window
{
public:
	void InitGraphicsManager(GraphicsLibrary graphicsLibrary)
	{
		switch (graphicsLibrary)
		{
		case GraphicsLibrary::Direct3D_12:
			m_graphicsManager = std::make_unique<GiDx12GraphicsManager>();
			m_commandContext = std::make_unique<GiDx12CommandContext>();
			break;

		default:
			break;
		}
	}

	void OnDestroy() override
	{
		PostQuitMessage(0);
	}

	void OnShow() override
	{
		try
		{
			m_graphicsManager->InitGraphicsObject(GetWinId());
			m_commandContext->InitCommandContext(m_graphicsManager.get());

			m_graphicsManager->ReSetCommandList();
			m_graphicsManager->BuildMesh(mesh.get());
			m_graphicsManager->BuildTexture(texture.get());
			m_graphicsManager->BuildShader(shader.get());
			m_graphicsManager->BuildMaterial(material.get());
			m_graphicsManager->ExecuteCommandAndWait();

			//material->SetTextureByName("Diffuse", texture.get());
		}
		catch (const std::exception& e)
		{
			StdErrorOutput(e);
			WindowFactory::DestroyAllWindowInstance();
		}
	}

	void OnResize(const ResizeEvent& event) override
	{
		try
		{
			Camera::mainCamera->aspect = static_cast<FLOAT>(event.sizeX) / static_cast<FLOAT>(event.sizeY);
			m_projMat = Camera::mainCamera->GetProjectionMatrix();

			m_graphicsManager->Resize(event.sizeX, event.sizeY);
		}
		catch (const std::exception& e)
		{
			StdErrorOutput(e);
			WindowFactory::DestroyAllWindowInstance();
		}
	}

	void OnKeyPress(const KeyEvent& event) override
	{
		if (event.keyCode == KeyCode::UP)
		{
			gameObj->GetTransform()->Rotate(0.0f, 0.0f, 5.0f);
			Debug::LogInfo(gameObj->GetTransform()->GetRotation());
			Debug::LogInfo(gameObj->GetTransform()->GetRotationQuaternion().GetEulerAngles());
		}
		else if (event.keyCode == KeyCode::DOWN)
		{
			gameObj->GetTransform()->Rotate(0.0f, 0.0f, -5.0f);
			Debug::LogInfo(gameObj->GetTransform()->GetRotation());
			Debug::LogInfo(gameObj->GetTransform()->GetRotationQuaternion().GetEulerAngles());
		}
		else if (event.keyCode == KeyCode::LEFT)
		{
			gameObj->GetTransform()->Rotate(0.0f, 5.0f, 0.0f);
			Debug::LogInfo(gameObj->GetTransform()->GetRotation());
			Debug::LogInfo(gameObj->GetTransform()->GetRotationQuaternion().GetEulerAngles());
		}
		else if (event.keyCode == KeyCode::RIGHT)
		{
			gameObj->GetTransform()->Rotate(0.0f, -5.0f, 0.0f);
			Debug::LogInfo(gameObj->GetTransform()->GetRotation());
			Debug::LogInfo(gameObj->GetTransform()->GetRotationQuaternion().GetEulerAngles());
		}
		else if (event.keyCode == KeyCode::ENTER)
		{
			gameObj->GetTransform()->SetRulerAngles(90.0f, 0.0f, 0.0f);
		}
		else if (event.keyCode == KeyCode::KEY_A)
		{
			JsonDocument jsonDocument = JsonDocument(TEXT("Resource/demo.json"));

			JsonNode& rootNode = jsonDocument.GetRootNode();
			Debug::LogInfo(rootNode["age"].asInt());

			rootNode["age"] = 999;

			jsonDocument.SaveJson(TEXT("Resource/demo1.json"));
		}
		else if (event.keyCode == KeyCode::KEY_B)
		{
			Debug::LogInfo(StringEx::BeginWith<std::string>("123", "19"));
		}
		else if (event.keyCode == KeyCode::KEY_C)
		{
			Debug::LogInfo(GetTypeName<Material>());
		}
		else if (event.keyCode == KeyCode::KEY_D)
		{
			Debug::LogInfo(test.GetField<int>("m_int"));
			Debug::LogInfo(TestClass::GetFieldInfo("m_int").access);
			Debug::LogInfo(TestClass::GetFieldInfo("m_int").type);
			auto func = test.GetField<TestClass::TestFuncType>("TestFunc");
			(test.*func)();
		}
	}

	void OnLoop() override
	{
		try
		{
			auto modelMatrix = gameObj->GetTransform()->GetModelMatrix();
			auto viewMatrix = Camera::mainCamera->GetViewMatrix();

			auto modelToProj = modelMatrix * viewMatrix * m_projMat;
			material->SetMatrix4ByName("gWorldViewProj", modelToProj.Transpose());

			m_graphicsManager->ReSetRuntimeResourceHeap(1);
			renderPipeline->Render(m_commandContext.get());

			const auto& actorMap = gameObj->GetActorMap();
			for (const auto& actorPair : actorMap)
			{
				actorPair.second->OnUpdate();
			}
			for (const auto& actorPair : actorMap)
			{
				actorPair.second->OnLateUpdate();
			}
		}
		catch (const std::exception& e)
		{
			StdErrorOutput(e);
		}
	}

private:
	std::unique_ptr<GraphicsManager> m_graphicsManager = nullptr;
	std::unique_ptr<CommandContext> m_commandContext = nullptr;

	Matrix4x4 m_projMat;
};

int WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(8);

	//PIXLoadLatestWinPixGpuCapturerLibrary();

	GameWindow* gameWindow = nullptr;

	try
	{
		Console::CreateConsole();
		Console::RedirectToStd();
		Console::SetTitle(TEXT("Xusory Console"));

		WindowFactory::StartNewWindowClass();
		WindowFactory::SetWindowCursor(SysCursor::ARROW);
		WindowFactory::SetWindowIcon(SysIcon::APPLICATION);
		WindowFactory::RegisterWindowClass(hIns, TEXT("MainWindow"));

		/*const std::vector position =
		{
			Float3(-5.0f, 0.0f, 0.0f),
			Float3(0.0f, 8.0f, 0.0f),
			Float3(5.0f, 0.0f, 0.0f),
		};

		const std::vector color =
		{
			Float4(1.0f, 0.0f, 0.0f, 0.0f),
			Float4(0.0f, 1.0f, 0.0f, 0.0f),
			Float4(0.0f, 0.0f, 1.0f, 0.0f),
		};

		std::vector<UINT> indices =
		{
			0, 1, 2,
		};*/

		const std::vector position =
		{
			Float3(10.0f, -10.0f, 10.0f),
			Float3(10.0f, 10.0f, 10.0f),
			Float3(-10.0f, 10.0f, 10.0f),
			Float3(-10.0f, -10.0f, 10.0f),
			Float3(10.0f, -10.0f, -10.0f),
			Float3(10.0f, 10.0f, -10.0f),
			Float3(-10.0f, 10.0f,- 10.0f),
			Float3(-10.0f, -10.0f, -10.0f),
		};


		const std::vector color =
		{
			Float4(1.0f, 0.0f, 0.0f, 0.0f),
			Float4(0.0f, 1.0f, 0.0f, 0.0f),
			Float4(0.0f, 0.0f, 1.0f, 0.0f),
			Float4(1.0f, 1.0f, 1.0f, 0.0f),
			Float4(1.0f, 0.0f, 0.0f, 0.0f),
			Float4(0.0f, 1.0f, 0.0f, 0.0f),
			Float4(0.0f, 0.0f, 1.0f, 0.0f),
			Float4(0.0f, 0.0f, 0.0f, 0.0f)
		};

		/*const std::vector uv0 =
		{
			Float2(0.0f, 1.0f),
			Float2(0.0f, 0.0f),
			Float2(1.0f, 0.0f),
			Float2(1.0f, 1.0f)
		};*/

		std::vector<UINT> indices =
		{
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7
		};

		mesh = std::make_shared<Mesh>();
		mesh->SetPosition(position);
		mesh->SetColor(color);
		mesh->SetIndices(indices);

		texture = std::make_shared<Texture>(TEXT("Texture/kasukasu.dds"));

		shader = std::make_shared<Shader>(TEXT("Shaders/color1.hlsl"));
		shader->SetVertexShaderEntryPoint("VS");
		shader->SetPixelShaderEntryPoint("PS");

		material = std::make_shared<Material>(shader.get());
		renderPipeline = std::make_shared<UserRenderPipeline>();

		gameObj = std::make_shared<GameObject>();
		MeshRenderer* renderer = gameObj->AddComponent<MeshRenderer>();
		renderer->mesh = mesh.get();
		renderer->material = material.get();
		gameObj->AddComponent<UserActor>();

		camera = std::make_shared<GameObject>();
		Camera* cameraPtr = camera->AddComponent<Camera>();
		camera->GetTransform()->MoveTo(0.0f, 0.0f, 70.0f);
		cameraPtr->targetPosition = Vector3(0.0f, 0.0f, 0.0f);

		Camera::mainCamera = cameraPtr;

		gameWindow = dynamic_cast<GameWindow*>(WindowFactory::CreateWindowInstance<GameWindow>(TEXT("MainWindow"), TEXT("Application"), 800, 600, true));
		gameWindow->InitGraphicsManager(GraphicsLibrary::Direct3D_12);

		gameWindow->Show();
	}
	catch (const std::exception& e)
	{
		StdErrorOutput(e);
	}

	gameWindow->MessageLoop();

	Console::SetTextColor(ConsoleTextColor::COLOR_WHITE);
	system("pause");
	return 0;
}

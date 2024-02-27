#include <iostream>
#include <string>
#include <vector>
#include <future>

#define DLL_IMPORT

#include "Header/XusoryEngine.h"
#include "GameMainDefine.h"

#include "pix3.h"

#pragma comment(lib, "XusoryEngine.lib")

using namespace std;
using namespace XusoryEngine;

constexpr float PI = 3.1415926535f;

std::shared_ptr<Mesh> mesh;
std::shared_ptr<Shader> shader;
std::shared_ptr<Material> material;

class UserRenderPipeline : public RenderPipeline
{
public:
	UserRenderPipeline() = default;

	void Render(CommandContext* commandContext) override
	{
		commandContext->BeginCommand();
		commandContext->ClearRenderTarget(true, true, { 0.235294133f, 0.701960802f, 0.443137288f, 1.f }, 1.0f);
		commandContext->DrawRenderer(material.get(), mesh.get());
		commandContext->EndCommand();
	}
};

std::shared_ptr<UserRenderPipeline> renderPipeline;

Vector3 position{ 0.0f, 0.0f, 0.0f };
Vector3 scale{ 1.0f, 1.0f, 1.0f };

Vector3 cameraPosition{ 0.0f, 0.0f, 40.0f };
Vector3 targetPosition{ 0.0f, 0.0f, 0.0f };
Vector3 worldUp{ 0.0f, 1.0f, 0.0f };

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
			m_graphicsManager->BuildShader(shader.get());
			m_graphicsManager->BuildMaterial(material.get());
			m_graphicsManager->ExecuteCommandAndWait();
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
			const FLOAT aspect = static_cast<FLOAT>(event.sizeX) / static_cast<FLOAT>(event.sizeY);
			m_projMat = XsMath::BuildPerspectiveMatrixFov(0.25f * PI, aspect, 1.0f, 1000.0f);

			m_graphicsManager->Resize(event.sizeX, event.sizeY);
		}
		catch (const std::exception& e)
		{
			StdErrorOutput(e);
		}
	}

	void OnKeyPress(const KeyEvent& event) override
	{
		if (event.keyCode == KeyCode::KEY_A)
		{
			Debug::LogInfo("Test Press");
		}
	}

	void OnLoop() override
	{
		try
		{
			auto modelMatrix = XsMath::BuildModelMatrix(position, scale);
			auto viewMatrix = XsMath::BuildViewMatrixLookUp(cameraPosition, targetPosition, worldUp);
			auto modelToProj = modelMatrix * viewMatrix * m_projMat;
			material->SetMatrix4ByIndex(0, modelToProj.Transpose());

			renderPipeline->Render(m_commandContext.get());
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
	cout.precision(4);

	PIXLoadLatestWinPixGpuCapturerLibrary();

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

		const std::vector position =
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
		};

		mesh = std::make_shared<Mesh>();
		mesh->SetPosition(position);
		mesh->SetColor(color);
		mesh->SetIndices(indices);

		shader = std::make_shared<Shader>(TEXT("Shaders/color1.hlsl"));
		shader->SetVertexShaderEntryPoint("VS");
		shader->SetPixelShaderEntryPoint("PS");

		material = std::make_shared<Material>(shader.get());
		renderPipeline = std::make_shared<UserRenderPipeline>();

		gameWindow = dynamic_cast<GameWindow*>(WindowFactory::CreateWindowInstance<GameWindow>(TEXT("MainWindow"), TEXT("Application"), 800, 600, true));
		gameWindow->InitGraphicsManager(GraphicsLibrary::Direct3D_12);
	}
	catch (const std::exception& e)
	{
		StdErrorOutput(e);
	}

	gameWindow->Show();
	gameWindow->MessageLoop();

	Console::SetTextColor(ConsoleTextColor::COLOR_WHITE);
	system("pause");
	return 0;
}

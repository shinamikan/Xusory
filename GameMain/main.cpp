#include <iostream>
#include <vector>
#include <future>
#include <DirectXMath.h>

#define DLL_IMPORT

#include "Header/XusoryEngine.h"
#include "GameWindow.h"

#pragma comment(lib, "XusoryEngine.lib")

using namespace std;
using namespace XusoryEngine;

std::shared_ptr<Mesh> mesh;
std::shared_ptr<Shader> shader;

class UserRenderPipeline : public RenderPipeline
{
public:
	UserRenderPipeline() = default;

	void Render(CommandContext* commandContext) override
	{
		
	}
};

int WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(4);

	GameWindow* gameWindow = nullptr;
	std::shared_ptr<UserRenderPipeline> renderPipeline;

	try
	{
		Console::CreateConsole();
		Console::RedirectToStd();
		Console::SetTitle(TEXT("Xusory Console"));

		WindowFactory::StartNewWindowClass();
		WindowFactory::SetWindowIcon(SYS_ICON_INFORMATION);
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
			Float4(0.0f, 0.0f, 2.0f, 0.0f),
		};

		std::vector<UINT> indices =
		{
			0, 1, 2,
		};

		mesh = std::make_shared<Mesh>();
		mesh->SetPosition(position);
		mesh->SetColor(color);
		mesh->SetIndices(indices);

		shader = std::make_shared<Shader>(TEXT("Shaders/color2.hlsl"));
		shader->SetVertexShaderEntryPoint("VS");
		shader->SetPixelShaderEntryPoint("PS");

		renderPipeline = std::make_shared<UserRenderPipeline>();

		gameWindow = dynamic_cast<GameWindow*>(WindowFactory::CreateWindowInstance<GameWindow>(TEXT("MainWindow"), TEXT("Application"), 400, 400, true));
		gameWindow->InitGraphicsManager(GraphicsLibrary::Direct3D_12);
		gameWindow->BindShaderList({ shader.get() });
		gameWindow->BindRenderPipeline({ renderPipeline.get() });
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

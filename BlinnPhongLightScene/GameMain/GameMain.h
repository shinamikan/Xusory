#pragma once

#include "../ProjectPackage/XusoryEngine.h"
#include "../ProjectPackage/Game/GameWindow.h"

#include "SceneMain.h"

using namespace std;
using namespace XusoryEngine;

class GameMain
{
public:
	void InitConsole() const;
	void InitGameWindow(HINSTANCE hInstance);
	void InitAssets();
	void InitScene();

	wstring consoleTitle = TEXT("Xusory Console");

	Window* gameWindow = nullptr;
	wstring gameWindowTitle = TEXT("Xusory Application");
	Point gameWindowSize = { 800, 600 };

	SceneMain sceneMain;
};

inline void GameMain::InitConsole() const
{
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.precision(8);

	Console::CreateConsole();
	Console::RedirectToStd();
	Console::SetTitle(consoleTitle);
}

inline void GameMain::InitGameWindow(HINSTANCE hInstance)
{
	WindowFactory::StartNewWindowClass();
	WindowFactory::SetWindowCursor(SysCursor::ARROW);
	WindowFactory::SetWindowIcon(SysIcon::APPLICATION);
	WindowFactory::RegisterWindowClass(hInstance, TEXT("MainWindow"));

	gameWindow = WindowFactory::CreateWindowInstance<GameWindow>(TEXT("MainWindow"), gameWindowTitle,
		gameWindowSize.x, gameWindowSize.y, true);
}

inline void GameMain::InitAssets()
{
	sceneMain.assets.LoadMesh();
	sceneMain.assets.LoadTexture();
	sceneMain.assets.LoadShader();
	sceneMain.assets.LoadMaterial();
}

inline void GameMain::InitScene()
{
	sceneMain.InitMaterial();
	sceneMain.InitGlobalGameObjects();
	sceneMain.InitGameObjects();
}

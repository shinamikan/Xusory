#define DLL_IMPORT

#include "GameMain/GameMain.h"

#pragma comment(lib, "XusoryEngine.lib")

using namespace std;
using namespace XusoryEngine;

int WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lpCmdLine, int nCmdShow)
{
	GameMain game;
	BOOL isInitError = false;

	try
	{
		//game.InitConsole();

		GraphicsManager::BuildGraphicsManager(GraphicsLibrary::Direct3D_12);
		game.InitGameWindow(hIns);

		SceneManager::LoadScene(TEXT(""));
		game.InitAssets();

		GraphicsManager::BuildAllGraphicsObject();
		game.InitScene();
		game.gameWindow->Show();
	}
	catch (const std::exception& e)
	{
		StdErrorOutput(e);
		isInitError = true;
	}

	if (!isInitError)
	{
		game.gameWindow->MessageLoop();
	}

	//Console::SetTextColor(ConsoleTextColor::COLOR_WHITE);
	//system("pause");
	return 0;
}

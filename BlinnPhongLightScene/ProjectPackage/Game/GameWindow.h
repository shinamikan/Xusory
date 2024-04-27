#pragma once

#include "../XusoryEngine.h"
#include "../RenderPipeline/BuiltInRenderPipeline.h"

using namespace XusoryEngine;

inline void StdErrorOutput(const std::exception& e)
{
	std::string completeErrorMsg;

	if (!TraceBack::GetTraceBackInfoList().empty())
	{
		completeErrorMsg = "C++ Exception TraceBack :\n";
		for (auto& info : TraceBack::GetTraceBackInfoList())
		{
			completeErrorMsg += "    " + info + "\n";
		}
	}

	completeErrorMsg = completeErrorMsg + e.what() + "\n";
	Debug::LogError(completeErrorMsg);
	TraceBack::ClearStack();
}

class GameWindow : public Window
{
public:
	void OnCreate() override
	{
		GraphicsManager::InitGraphicsManager(GetWinId());
		m_renderPipeline = std::make_shared<BuiltInRenderPipeline>();
	}

	void OnDestroy() override
	{
		PostQuitMessage(0);
	}

	void OnShow() override
	{
		try
		{
			for (const auto* gameObject : SceneManager::GetActiveScene()->GetGameObjectList())
			{
				const auto& actorMap = gameObject->GetActorMap();
				if (actorMap.empty())
				{
					continue;
				}
				for (const auto& actorPair : actorMap)
				{
					actorPair.second->OnStart();
				}
			}
		}
		catch (const std::exception& e)
		{
			StdErrorOutput(e);
			WindowFactory::DestroyAllWindowInstance();
		}
	}

	void OnMinimize() override
	{
		m_isMinimize = true;
	}

	void OnRestore() override
	{
		m_isMinimize = false;
	}

	void OnResize(const ResizeEvent& event) override
	{
		try
		{
			if (!m_isMinimize)
			{
				GameManager::ProcessMainAspect(static_cast<FLOAT>(event.sizeX) / static_cast<FLOAT>(event.sizeY));
				GraphicsManager::GetGraphicsManager()->Resize(event.sizeX, event.sizeY);
			}
		}
		catch (const std::exception& e)
		{
			StdErrorOutput(e);
			WindowFactory::DestroyAllWindowInstance();
		}
	}

	void OnMouseMove(const MouseMoveEvent& event) override
	{
		GameManager::ProcessMousePosition({ event.mouseMovePosX, event.mouseMovePosY });
	}

	void OnMousePress(const MouseClickEvent& event) override
	{
		GameManager::ProcessMouseKeyDownInput(event.mouseKeyCode);
		SetCapture(GetWinId());
	}

	void OnMouseRelease(const MouseClickEvent& event) override
	{
		GameManager::ProcessMouseKeyUpInput(event.mouseKeyCode);
		ReleaseCapture();
	}

	void OnMouseWheel(const MouseWheelEvent& event) override
	{
		GameManager::ProcessMouseWheel(event.mouseWheelDis);
	}

	void OnKeyPress(const KeyEvent& event) override
	{
		GameManager::ProcessKeyDownInput(event.keyCode);
	}

	void OnKeyRelease(const KeyEvent& event) override
	{
		GameManager::ProcessKeyUpInput(event.keyCode);
	}

	void OnLoop() override
	{
		try
		{
			BOOL lightFlag = false;
			GameManager::ProcessTime(PerformanceTime::GetTime());

			auto* activeScene = SceneManager::GetActiveScene();
			const auto allGoList = activeScene->GetGameObjectList();
			for (auto* gameObject : allGoList)
			{
				if (!lightFlag)
				{
					if (gameObject->HasComponent<Light>())
					{
						activeScene->globalLight = gameObject->GetComponent<Light>();
						lightFlag = true;
					}
				}

				const auto& actorMap = gameObject->GetActorMap();
				if (actorMap.empty())
				{
					continue;
				}
				for (const auto& actorPair : actorMap)
				{
					actorPair.second->OnUpdate();
				}
			}
			for (const auto* gameObject : allGoList)
			{
				const auto& actorMap = gameObject->GetActorMap();
				if (actorMap.empty())
				{
					continue;
				}
				for (const auto& actorPair : actorMap)
				{
					actorPair.second->OnLateUpdate();
				}
			}

			UINT runtimeHeapSize = 0;
			auto matGoMap = SceneManager::GetActiveScene()->GetMatGoMap();
			for (auto& [material, gameObject] : matGoMap)
			{
				runtimeHeapSize += material->GetTexturePropertyNum();
			}
			if (runtimeHeapSize != 0)
			{
				GraphicsManager::GetGraphicsManager()->ReSetRuntimeResourceHeap(runtimeHeapSize);
			}

			m_renderPipeline->Render(GraphicsManager::GetCommandContext());

			GameManager::ResetMouseKeyUp();
			GameManager::ClearKeyDownUp();
			GameManager::ClearMouseKeyDownUp();
			GameManager::ClearMouseWheel();
		}
		catch (const std::exception& e)
		{
			StdErrorOutput(e);
		}
	}

private:
	BOOL m_isMinimize = false;
	std::shared_ptr<RenderPipeline> m_renderPipeline;
};

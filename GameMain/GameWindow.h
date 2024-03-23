#pragma once

#include "Header/XusoryEngine.h"
#include "GameMainDefine.h"

using namespace XusoryEngine;

class BuiltInRenderPipeline : public RenderPipeline
{
public:
	BuiltInRenderPipeline() = default;

	void Render(CommandContext* commandContext) override
	{
		commandContext->BeginCommand();
		commandContext->ClearRenderTarget({ 0.9f, 0.9f, 0.9f, 1.f });
		commandContext->ClearDepth(1.0f);
		commandContext->ClearStencil(0);

		auto viewMatrix = Camera::mainCamera->GetViewMatrix();
		auto projMatrix = Camera::mainCamera->GetProjectionMatrix();
		auto vpMatrix = viewMatrix * projMatrix;

		auto matGoMap = GameManager::GetMatGoMap();

		for (auto& [material, goList] : matGoMap)
		{
			if (!GraphicsManager::GetGraphicsManager()->IsShaderBuilt(const_cast<Shader*>(material->GetShader())))
			{
				continue;
			}
			if (!GraphicsManager::GetGraphicsManager()->IsMaterialBuilt(material))
			{
				continue;
			}

			for (UINT i = material->GetConstantPropertyNum(); i < material->GetTexturePropertyNum(); i++)
			{
				auto* texture = const_cast<Texture*>(material->GetTextureByIndex(i));
				if (!GraphicsManager::GetGraphicsManager()->IsTextureBuilt(texture))
				{
					GraphicsManager::BuildAloneTexture(texture, true);
				}
			}
			commandContext->SetMaterial(material);

			for (auto* renderingGo : goList)
			{
				if (!renderingGo->GetActive())
				{
					continue;
				}

				auto modelMatrix = renderingGo->GetTransform()->GetModelMatrix();
				auto modelToProj = modelMatrix * vpMatrix;
				material->SetMatrix4ByName("gWorldViewProj", modelToProj.Transpose());

				Mesh* mesh = renderingGo->GetComponent<MeshRenderer>()->mesh;
				if (mesh == nullptr)
				{
					continue;
				}
				if (!GraphicsManager::GetGraphicsManager()->IsMeshBuilt(mesh))
				{
					GraphicsManager::BuildAloneMesh(mesh, true);
				}

				commandContext->SetMesh(mesh);
				commandContext->DrawMesh();
			}
		}

		commandContext->EndCommand();
	}
};

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
			GameManager::ProcessTime(PerformanceTime::GetTime());

			const auto allGoList = SceneManager::GetActiveScene()->GetSceneGameObjectList();
			for (const auto* gameObject : allGoList)
			{
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
			auto matGoMap = SceneManager::GetActiveScene()->GetSceneMatGoMap();
			for (auto& [material, gameObject] : matGoMap)
			{
				runtimeHeapSize += material->GetTexturePropertyNum();
			}

			GraphicsManager::GetGraphicsManager()->ReSetRuntimeResourceHeap(runtimeHeapSize);
			GameManager::SetMatGoMap(matGoMap);

			m_renderPipeline->Render(GraphicsManager::GetCommandContext());

			GameManager::ResetMouseKeyUp();
			GameManager::ClearKeyDownUp();
			GameManager::ClearMouseKeyDownUp();
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

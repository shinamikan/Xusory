#pragma once

#include "Header/XusoryEngine.h"
#include "GameMainDefine.h"

using namespace XusoryEngine;

class TestWindow : public Window
{
public:
	void OnMousePress(const MouseClickEvent& event) override
	{
		if (event.mouseKeyCode == EX_BUTTON_1)
		{
			Debug::Log(LOG_INFO, event.mouseKeyCode);
		}
	}

	void OnKeyPress(const KeyEvent& event) override
	{
		if (event.keyCode == KEY_1)
		{
			Console::Clear();
		}
		else if (event.keyCode == KEY_2)
		{
			Vector3 v00 = Vector3(1, 2, 3);
			Vector4 v01 = Vector4(1, 2, 3, 4);

			Matrix4x4 m02 = Matrix4x4(
				2.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 2.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			Matrix4x4 m03 = Matrix4x4(
				8.0f, 16.0f, 1.0f, 3.0f,
				5.0f, 11.0f, 12.0f, 2.0f,
				6.0f, 10.0f, 151.0f, 7.0f,
				9.0f, 13.0f, 14.0f, 4.0f);

			Debug::LogInfo("m03:\n", m03);
			Debug::LogInfo("Determinant:", m03.Determinant());
			Debug::LogInfo("Inverse:\n", m03.Inverse());
			Debug::LogInfo("Transpose:\n", m03.Transpose());
			Debug::LogInfo("PreMultiVector4:", Matrix4x4::PreTransPoint3(v00, m02));
			Debug::LogInfo("PreMultiVector4:", Matrix4x4::PreTransVector3(v00, m02));
			Debug::LogInfo("PreMultiVector4:", Matrix4x4::PostTransVector3(m02, v00));
			Debug::LogInfo("PreMultiVector4:", Matrix4x4::PostTransVector3(m02, v00));
			Debug::LogInfo("PreMultiVector4:", Matrix4x4::PreMultiVector4(v01, m03));
			Debug::LogInfo("PostMultiVector4:", Matrix4x4::PostMultiVector4(m03, v01));
			Debug::LogInfo("MultiMatrix:\n", Matrix4x4::MultiMatrix(m02, m02));
		}
		else if (event.keyCode == KEY_3)
		{
			Vector2 v1 = Vector2(1, 2);
			Vector2 v2 = Vector2(4, 3);
			Vector3 v3 = Vector3(1, 0, 0);
			Vector3 v4 = Vector3(0, 1, 0);

			Debug::LogInfo("v1:", v1);
			Debug::LogInfo("v2:", v2);
			Debug::LogInfo("v1 + v2:", v1 + v2);
			Debug::LogInfo("v1 - v2:", v1 - v2);
			Debug::LogInfo("v1 * v2:", v1 * v2);
			Debug::LogInfo("v1 / v2:", v1 / v2);

			Debug::LogInfo("Length:", v1.Length());
			Debug::LogInfo("LengthSq:", v1.LengthSq());
			Debug::LogInfo("Dot:", v1.Dot(v2));

			Debug::LogInfo("Normalize:", v1.Normalize());
			Debug::LogInfo("Sqrt:", v1.Sqrt());
			Debug::LogInfo("Max:", v1.Max(v2));
			Debug::LogInfo("Min:", v1.Min(v2));
			Debug::LogInfo("Lerp:", Vector2::Lerp(v1, v2, 0.5f));
			Debug::LogInfo("Cross:", Vector3::Cross(v3, v4));
		}
		else if (event.keyCode == KEY_4)
		{
			WindowFactory::MessageWindow(GetWinId(), TEXT("≤‚ ‘¥∞ø⁄"), TEXT("≤‚ ‘ƒ⁄»›Hello World"));
		}
		else if (event.keyCode == KEY_5)
		{
			Debug::Log(LOG_INFO, "Monitoring the directory");
			Directory::MonitorDirChanges(TEXT("Resource/Test1"));
			Debug::Log(LOG_INFO, "Monitor over");
		}
	}

	void OnDestroy() override
	{
		PostQuitMessage(0);
	}
};

class GameWindow : public Window
{
public:
	void BindShaderList(const std::vector<Shader*>& shaderList)
	{
		m_shaderList = shaderList;
	}

	void BindRenderPipeline(RenderPipeline* renderPipeline)
	{
		m_renderPipeline = renderPipeline;
	}

	void InitGraphicsManager(GraphicsLibrary graphicsLibrary)
	{
		switch (graphicsLibrary)
		{
		case GraphicsLibrary::Direct3D_12:
			m_graphicsManager = std::make_unique<GiDx12GraphicsManager>();
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
			for (const auto& shader : m_shaderList)
			{
				m_graphicsManager->BuildShader(shader);
			}
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
			if (m_graphicsManager)
			{
				m_graphicsManager->Resize(event.sizeX, event.sizeY);
			}
		}
		catch (const std::exception& e)
		{
			StdErrorOutput(e);
			WindowFactory::DestroyAllWindowInstance();
		}
	}

	void OnKeyPress(const KeyEvent& event) override
	{
		if (event.keyCode == KEY_1)
		{
			Debug::LogInfo("Test Press");
		}
	}

	void OnLoop() override
	{
		//m_renderPipeline->Render();
		dynamic_cast<GiDx12GraphicsManager*>(m_graphicsManager.get())->Render();
	}

private:
	std::unique_ptr<GraphicsManager> m_graphicsManager = nullptr;
	//std::unique_ptr<CommandContext> m_commandContext = nullptr;

	std::vector<Shader*> m_shaderList;
	RenderPipeline* m_renderPipeline = nullptr;

	DOUBLE m_lastTime = 0;
};

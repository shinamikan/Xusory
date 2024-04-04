#include "../GraphicsManager.h"

namespace XusoryEngine
{
	std::unique_ptr<RhiManager> GraphicsManager::sm_rhiManager = nullptr;
	std::unique_ptr<CommandContext> GraphicsManager::sm_commandContext = nullptr;

	std::vector<Material*> GraphicsManager::sm_materialListTemp = std::vector<Material*>();
	std::vector<Mesh*> GraphicsManager::sm_meshListTemp = std::vector<Mesh*>();
	std::vector<Shader*> GraphicsManager::sm_shaderListTemp = std::vector<Shader*>();
	std::vector<Texture*> GraphicsManager::sm_textureListTemp = std::vector<Texture*>();

	void GraphicsManager::BuildGraphicsManager(GraphicsLibrary graphicsLibrary)
	{
		switch (graphicsLibrary)
		{
		case GraphicsLibrary::Direct3D_12:
			sm_rhiManager = std::make_unique<GiDx12RhiManager>();
			sm_commandContext = std::make_unique<GiDx12CommandContext>();
			break;

		default:
			ThrowWithErrName(RuntimeError, "Unknown graphics library");
		}
	}

	void GraphicsManager::InitGraphicsManager(void* renderWindow)
	{
		sm_rhiManager->InitGraphicsObject(renderWindow);
		sm_commandContext->InitCommandContext(sm_rhiManager.get());
	}

	RhiManager* GraphicsManager::GetGraphicsManager()
	{
		return sm_rhiManager.get();
	}

	CommandContext* GraphicsManager::GetCommandContext()
	{
		return sm_commandContext.get();
	}

	void GraphicsManager::AddMaterial(Material* material)
	{
		sm_materialListTemp.push_back(material);
	}

	void GraphicsManager::AddMesh(Mesh* mesh)
	{
		sm_meshListTemp.push_back(mesh);
	}

	void GraphicsManager::AddShader(Shader* shader)
	{
		sm_shaderListTemp.push_back(shader);
	}

	void GraphicsManager::AddTexture(Texture* texture)
	{
		sm_textureListTemp.push_back(texture);
	}

	void GraphicsManager::BuildAllGraphicsObject()
	{
		sm_rhiManager->ReSetCommandList();

		for (auto* mesh : sm_meshListTemp)
		{
			sm_rhiManager->BuildMesh(mesh);
		}
		for (auto* texture : sm_textureListTemp)
		{
			sm_rhiManager->BuildTexture(texture);
		}
		for (auto* shader : sm_shaderListTemp)
		{
			sm_rhiManager->BuildShader(shader);
		}
		for (auto* material : sm_materialListTemp)
		{
			sm_rhiManager->BuildMaterial(material);
		}

		sm_rhiManager->ExecuteCommandAndWait();

		sm_materialListTemp.clear();
		sm_meshListTemp.clear();
		sm_shaderListTemp.clear();
		sm_textureListTemp.clear();
	}

	void GraphicsManager::BuildAloneMaterial(Material* material)
	{
		sm_rhiManager->BuildMaterial(material);
	}

	void GraphicsManager::BuildAloneMesh(Mesh* mesh, BOOL isCommandBegan)
	{
		if (!isCommandBegan) sm_rhiManager->ReSetCommandList();
		sm_rhiManager->BuildMesh(mesh);
		if (!isCommandBegan) sm_rhiManager->ExecuteCommandAndWait();
	}

	void GraphicsManager::BuildAloneShader(Shader* shader, BOOL isCommandBegan)
	{
		sm_rhiManager->BuildShader(shader);
	}

	void GraphicsManager::BuildAloneTexture(Texture* texture, BOOL isCommandBegan)
	{
		if (!isCommandBegan) sm_rhiManager->ReSetCommandList();
		sm_rhiManager->BuildTexture(texture);
		if (!isCommandBegan) sm_rhiManager->ExecuteCommandAndWait();
	}
}

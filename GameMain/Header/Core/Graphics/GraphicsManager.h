#pragma once

#include <vector>
#include "CommandContext.h"
#include "RhiManager.h"

namespace XusoryEngine
{
	class Material;
	class Mesh;
	class Shader;
	class Texture;
	class GraphicsManager
	{
	public:
		static void BuildGraphicsManager(GraphicsLibrary graphicsLibrary);
		static void InitGraphicsManager(void* renderWindow);

		static RhiManager* GetGraphicsManager();
		static CommandContext* GetCommandContext();

		static void AddMaterial(Material* material);
		static void AddMesh(Mesh* mesh);
		static void AddShader(Shader* shader);
		static void AddTexture(Texture* texture);
		static void BuildAllGraphicsObject();

		static void BuildAloneMaterial(Material* material);
		static void BuildAloneMesh(Mesh* mesh, BOOL isCommandBegan);
		static void BuildAloneShader(Shader* shader, BOOL isCommandBegan);
		static void BuildAloneTexture(Texture* texture, BOOL isCommandBegan);

	private:
		static std::unique_ptr<RhiManager> sm_rhiManager;
		static std::unique_ptr<CommandContext> sm_commandContext;

		static std::vector<Material*> sm_materialListTemp;
		static std::vector<Mesh*> sm_meshListTemp;
		static std::vector<Shader*> sm_shaderListTemp;
		static std::vector<Texture*> sm_textureListTemp;
	};
}


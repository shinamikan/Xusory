#pragma once

#include "../XusoryEngine.h"

using namespace XusoryEngine;

class BuiltInRenderPipeline : public RenderPipeline
{
public:
	BuiltInRenderPipeline() = default;

	void Render(CommandContext* commandContext) override
	{
		commandContext->BeginCommand();
		commandContext->ClearRenderTarget({ 0.0f, 0.0f, 0.0f, 1.0f });
		commandContext->ClearDepth(1.0f);
		commandContext->ClearStencil(0);

		auto viewMatrix = Camera::mainCamera->GetViewMatrix();
		auto projMatrix = Camera::mainCamera->GetProjectionMatrix();
		auto vpMatrix = viewMatrix * projMatrix;

		auto activeScene = SceneManager::GetActiveScene();
		auto matGoMap = activeScene->GetMatGoMap();

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

			Light* light = activeScene->globalLight;
			if (material->HasProperty("ambient")) material->SetFloat3ByName("ambient", Light::ambient.GetVector());
			if (material->HasProperty("lightType")) material->SetIntByName("lightType", static_cast<INT>(light->lightType));
			if (material->HasProperty("lightPosition")) material->SetFloat3ByName("lightPosition", light->GetLightWorldPosition().GetVector());
			if (material->HasProperty("lightDirection")) material->SetFloat3ByName("lightDirection", light->GetLightWorldDirection().GetVector());
			if (material->HasProperty("lightColor")) material->SetFloat3ByName("lightColor", light->color.GetVector());
			if (material->HasProperty("lightIntensity")) material->SetFloatByName("lightIntensity", light->intensity);
			if (material->HasProperty("lightRange")) material->SetFloatByName("lightRange", light->range);
			if (material->HasProperty("viewPosition")) material->SetFloat3ByName("viewPosition", Camera::mainCamera->belongsGameObject->GetTransform()->GetPosition(Space::WORLD).GetVector());

			commandContext->SetMaterial(material);

			for (auto* renderingGo : goList)
			{
				if (!renderingGo->GetActive())
				{
					continue;
				}

				auto modelMatrix = renderingGo->GetTransform()->GetModelMatrix();
				auto modelToProj = modelMatrix * vpMatrix;
				material->SetMatrix4ByName("modelToProject", modelToProj.Transpose());
				if (material->HasProperty("modelToWorld")) material->SetMatrix4ByName("modelToWorld", modelMatrix);
				if (material->HasProperty("worldToModel")) material->SetMatrix4ByName("worldToModel", modelMatrix.Inverse());

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

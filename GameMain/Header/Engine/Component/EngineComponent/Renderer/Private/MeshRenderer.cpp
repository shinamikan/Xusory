#include "../MeshRenderer.h"
#include "../../../../Scene/Scene.h"
#include "../../../../Scene/SceneManager.h"

namespace XusoryEngine
{
	INIT_XS_CLASS(MeshRenderer);

	Material* MeshRenderer::GetMaterial() const
	{
		return m_material;
	}

	void MeshRenderer::SetMaterial(const Material* material)
	{
		if (m_material != material)
		{
			m_material = const_cast<Material*>(material);

			Scene* activeScene = SceneManager::GetActiveScene();
			activeScene->m_isMatGoMapDirty = true;
		}
	}
}

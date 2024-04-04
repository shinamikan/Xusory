#pragma once

#include <vector>
#include "../../Core/Core.h"

#include "MeshLoader.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

namespace XusoryEngine
{
	DLL_CLASS(ResourceLoader)
	{
	public:
		template <typename T>
		static std::shared_ptr<T> Load(const std::wstring_view& path, BOOL isGameInit = false);

		template <typename T>
		static std::vector<std::shared_ptr<T>> LoadSeveral(const std::wstring_view& path, BOOL isGameInit = false);
	};

	template<>
	inline std::shared_ptr<Mesh> ResourceLoader::Load(const std::wstring_view& path, BOOL isGameInit)
	{
		File::TryToFindFile(path);
		const auto filePathList = StringEx::SplitView<std::wstring>(path, TEXT("."));

		const auto meshLoader = std::unique_ptr<IMeshLoader>(MeshLoaderFactory::GetFactory(*(filePathList.end() - 1)));
		const auto mesh = meshLoader->LoadMesh(path);

		const std::wstring meshAttrFile = std::wstring(path) + TEXT(".attr");
		File::TryToFindFile(meshAttrFile);

		auto meshAttr = JsonDocument(meshAttrFile);
		auto& rootNode = meshAttr.GetRootNode();
		mesh->m_indexFormat = static_cast<IndexFormat>(rootNode["IndexFormat"].asInt());
		mesh->m_primitiveTopology = static_cast<PrimitiveTopology>(rootNode["PrimitiveTopology"].asInt());

		if (isGameInit)
		{
			GraphicsManager::AddMesh(mesh.get());
		}
		else
		{
			GraphicsManager::BuildAloneMesh(mesh.get(), false);
		}

		return mesh;
	}

	template<>
	inline std::shared_ptr<Shader> ResourceLoader::Load(const std::wstring_view& path, BOOL isGameInit)
	{
		File::TryToFindFile(path);

		const auto shader = std::make_shared<Shader>();
		auto pathListTemp = StringEx::SplitView<std::wstring>(path, TEXT("/"));
		shader->m_name = StringEx::WStringToString(StringEx::Split<std::wstring>(*(pathListTemp.end() - 1), TEXT(".")).at(0));

		const std::wstring shaderAttrFile = std::wstring(path) + TEXT(".attr");
		File::TryToFindFile(shaderAttrFile);

		auto shaderAttr = JsonDocument(shaderAttrFile);
		auto& rootNode = shaderAttr.GetRootNode();
		shader->SetVertexShaderEntryPoint(rootNode["VertexShader"].asString());
		shader->SetPixelShaderEntryPoint(rootNode["PixelShader"].asString());
		shader->SetDomainShaderEntryPoint(rootNode["DomainShader"].asString());
		shader->SetHullShaderEntryPoint(rootNode["HullShader"].asString());
		shader->SetGeometryShaderEntryPoint(rootNode["GeometryShader"].asString());

		const auto filePathList = StringEx::SplitView<std::wstring>(path, TEXT("."));
		const auto shaderLoader = std::unique_ptr<IShaderLoader>(ShaderLoaderFactory::GetFactory(*(filePathList.end() - 1)));
		shaderLoader->LoadShader(shader.get(), path);

		shader->m_fillMode = static_cast<GraphicsFillMode>(rootNode["GraphicsFillMode"].asInt());
		shader->m_cullMode = static_cast<GraphicsCullMode>(rootNode["GraphicsCullMode"].asInt());
		shader->m_triangleWindingOrder = static_cast<TriangleWindingOrder>(rootNode["TriangleWindingOrder"].asInt());

		if (isGameInit)
		{
			GraphicsManager::AddShader(shader.get());
		}
		else
		{
			GraphicsManager::BuildAloneShader(shader.get(), false);
		}

		return shader;
	}

	template<>
	inline std::shared_ptr<Texture> ResourceLoader::Load(const std::wstring_view& path, BOOL isGameInit)
	{
		File::TryToFindFile(path);
		const auto filePathList = StringEx::SplitView<std::wstring>(path, TEXT("."));

		const auto textureLoader = std::unique_ptr<ITextureLoader>(TextureLoaderFactory::GetFactory(*(filePathList.end() - 1)));
		const auto texture = textureLoader->LoadTexture(path);
		texture->m_name = StringEx::WStringToString(path);

		const std::wstring textureAttrFile = std::wstring(path) + TEXT(".attr");
		File::TryToFindFile(textureAttrFile);

		auto textureAttr = JsonDocument(textureAttrFile);
		auto& rootNode = textureAttr.GetRootNode();
		texture->m_dimension = static_cast<TextureDimension>(rootNode["TextureDimension"].asInt());
		texture->m_addressModeU = static_cast<AddressMode>(rootNode["AddressModeU"].asInt());
		texture->m_addressModeV = static_cast<AddressMode>(rootNode["AddressModeV"].asInt());
		texture->m_addressModeW = static_cast<AddressMode>(rootNode["AddressModeW"].asInt());
		texture->m_filterMode = static_cast<FilterMode>(rootNode["FilterMode"].asInt());

		if (isGameInit)
		{
			GraphicsManager::AddTexture(texture.get());
		}
		else
		{
			GraphicsManager::BuildAloneTexture(texture.get(), false);
		}

		return texture;
	}

	template<>
	inline std::vector<std::shared_ptr<Mesh>> ResourceLoader::LoadSeveral(const std::wstring_view& path, BOOL isGameInit)
	{
		File::TryToFindFile(path);
		const auto filePathList = StringEx::SplitView<std::wstring>(path, TEXT("."));

		const auto meshLoader = std::unique_ptr<IMeshLoader>(MeshLoaderFactory::GetFactory(*(filePathList.end() - 1)));
		const auto meshList = meshLoader->LoadSeveralMesh(path);

		const std::wstring meshAttrFile = std::wstring(path) + TEXT(".attr");
		File::TryToFindFile(meshAttrFile);

		auto meshAttr = JsonDocument(meshAttrFile);
		auto& rootNode = meshAttr.GetRootNode();

		const auto indexFormat = static_cast<IndexFormat>(rootNode["IndexFormat"].asInt());
		const auto primitiveTopology = static_cast<PrimitiveTopology>(rootNode["PrimitiveTopology"].asInt());

		for (const auto& mesh : meshList)
		{
			mesh->m_indexFormat = indexFormat;
			mesh->m_primitiveTopology = primitiveTopology;

			if (isGameInit)
			{
				GraphicsManager::AddMesh(mesh.get());
			}
			else
			{
				GraphicsManager::BuildAloneMesh(mesh.get(), false);
			}
		}

		return meshList;
	}
}

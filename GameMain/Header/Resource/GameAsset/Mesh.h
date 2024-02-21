#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	enum class IndexFormat
	{
		INDEX_UINT16,
        INDEX_UINT32
	};

	class Mesh
	{
    public:
        Mesh() = default;
        Mesh(UINT verticesNum, UINT indicesNum);

        const std::vector<Vertex>& GetVertices() const;
        const std::vector<UINT>& GetIndices() const;
        void SetVertices(std::vector<Vertex>& vertices);
        void SetIndices(std::vector<UINT>& indices);

        void SetPosition(const std::vector<Float3>& positionList);
        void SetNormal(const std::vector<Float3>& normalList);
        void SetTangent(const std::vector<Float3>& tangentList);
        void SetColor(const std::vector<Float4>& colorList);
        void SetUv0(const std::vector<Float2>& uvList);
        void SetUv1(const std::vector<Float2>& uvList);
        void SetUv2(const std::vector<Float2>& uvList);
        void SetUv3(const std::vector<Float2>& uvList);
        void SetUv4(const std::vector<Float2>& uvList);

        std::string name;
        IndexFormat indexFormat = IndexFormat::INDEX_UINT32;

    private:
        std::vector<Vertex> vertices{};
        std::vector<UINT> indices{};
	};
}

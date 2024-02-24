#pragma once

#include <vector>
#include "Geometry/Vertex.h"

namespace XusoryEngine
{
	enum class IndexFormat
	{
		UINT16 = 57,
        UINT32 = 42
	};

	enum class PrimitiveTopology
	{
        UNDEFINED = 0,
        POINT_LIST,
        LINE_LIST,
        TRIANGLE_LIST,
        TRIANGLE_STRIP,
        LINE_LIST_ADJ = 10,
        LINE_STRIP_ADJ = 11,
        TRIANGLE_LIST_ADJ = 12,
        TRIANGLE_STRIP_ADJ = 13,
	};

	class Mesh
	{
    public:
        Mesh() = default;
        Mesh(UINT verticesNum, UINT indicesNum);

        const std::wstring& GetMeshFilePath() const;

        const std::vector<Vertex>& GetVertices() const;
        const std::vector<UINT>& GetIndices() const;
        UINT GetVerticesNum() const;
        UINT GetIndicesNum() const;

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

        IndexFormat indexFormat = IndexFormat::UINT32;
        PrimitiveTopology primitiveTopology = PrimitiveTopology::TRIANGLE_LIST;

    private:
        std::wstring m_meshFilePath;

        std::vector<Vertex> m_vertices{};
        std::vector<UINT> m_indices{};
	};
}

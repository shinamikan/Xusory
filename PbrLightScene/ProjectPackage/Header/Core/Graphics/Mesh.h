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
        LINE_STRIP,
        TRIANGLE_LIST,
        TRIANGLE_STRIP,
        LINE_LIST_ADJ = 10,
        LINE_STRIP_ADJ = 11,
        TRIANGLE_LIST_ADJ = 12,
        TRIANGLE_STRIP_ADJ = 13,
	};

	DLL_CLASS(Mesh)
	{
        friend class ResourceLoader;

    public:
        Mesh() = default;
        explicit Mesh(const std::string_view& name);

        const std::string& GetName() const;

        IndexFormat GetIndexFormat() const;
        PrimitiveTopology GetPrimitiveTopology() const;

        const std::vector<Vertex>& GetVertices() const;
        const std::vector<UINT>& GetIndices() const;
        UINT GetVerticesNum() const;
        UINT GetIndicesNum() const;

        void AddVertex(const Vertex& vertices);
        void AddTriangleIndex(UINT ver0, UINT ver1, UINT ver2);
        void SetVertices(const std::vector<Vertex>& vertices);
        void SetIndices(const std::vector<UINT>& indices);
        void SetVerticesNum(UINT verticesNum);
        void SetIndicesNum(UINT indicesNum);

        void SetPosition(const std::vector<Float3>& positionList);
        void SetNormal(const std::vector<Float3>& normalList);
        void SetTangent(const std::vector<Float3>& tangentList);
        void SetColor(const std::vector<Float4>& colorList);
        void SetUv0(const std::vector<Float2>& uvList);
        void SetUv1(const std::vector<Float2>& uvList);
        void SetUv2(const std::vector<Float2>& uvList);
        void SetUv3(const std::vector<Float2>& uvList);
        void SetUv4(const std::vector<Float2>& uvList);

    private:
        std::string m_name;

        IndexFormat m_indexFormat = IndexFormat::UINT32;
        PrimitiveTopology m_primitiveTopology = PrimitiveTopology::TRIANGLE_LIST;

        std::vector<Vertex> m_vertices;
        std::vector<UINT> m_indices;
	};
}

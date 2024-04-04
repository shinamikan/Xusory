#include "../Mesh.h"

namespace XusoryEngine
{
	Mesh::Mesh(const std::string_view& name) : m_name(name) { }

	const std::string& Mesh::GetName() const
	{
		return m_name;
	}

	IndexFormat Mesh::GetIndexFormat() const
	{
		return m_indexFormat;
	}

	PrimitiveTopology Mesh::GetPrimitiveTopology() const
	{
		return m_primitiveTopology;
	}

	const std::vector<Vertex>& Mesh::GetVertices() const
	{
		return m_vertices;
	}

	const std::vector<UINT>& Mesh::GetIndices() const
	{
		return m_indices;
	}

	void Mesh::SetVertices(const std::vector<Vertex>& vertices)
	{
		m_vertices = vertices;
	}

	void Mesh::SetIndices(const std::vector<UINT>& indices)
	{
		m_indices = indices;
	}

	void Mesh::SetVerticesNum(UINT verticesNum)
	{
		m_vertices.resize(verticesNum);
	}

	void Mesh::SetIndicesNum(UINT indicesNum)
	{
		m_vertices.resize(indicesNum);
	}

	UINT Mesh::GetVerticesNum() const
	{
		return static_cast<UINT>(m_vertices.size());
	}

	UINT Mesh::GetIndicesNum() const
	{
		return static_cast<UINT>(m_indices.size());
	}

	void Mesh::AddVertex(const Vertex& vertices)
	{
		m_vertices.push_back(vertices);
	}

	void Mesh::AddTriangleIndex(UINT ver0, UINT ver1, UINT ver2)
	{
		m_indices.push_back(ver0);
		m_indices.push_back(ver1);
		m_indices.push_back(ver2);
	}

	void Mesh::SetPosition(const std::vector<Float3>& positionList)
	{
		if (positionList.size() > m_vertices.size())
		{
			for (SIZE_T i = m_vertices.size(); i < positionList.size(); i++)
			{
				m_vertices.emplace_back(positionList.at(i), VertexCommonProperty::POSITION);
			}
		}
		for (UINT i = 0; i < positionList.size(); i++)
		{
			m_vertices.at(i).position = positionList.at(i);
		}
	}

	void Mesh::SetNormal(const std::vector<Float3>& normalList)
	{
		if (normalList.size() > m_vertices.size())
		{
			for (SIZE_T i = m_vertices.size(); i < normalList.size(); i++)
			{
				m_vertices.emplace_back(normalList.at(i), VertexCommonProperty::NORMAL);
			}
		}
		for (UINT i = 0; i < normalList.size(); i++)
		{
			m_vertices.at(i).normal = normalList.at(i);
		}
	}

	void Mesh::SetTangent(const std::vector<Float3>& tangentList)
	{
		if (tangentList.size() > m_vertices.size())
		{
			for (SIZE_T i = m_vertices.size(); i < tangentList.size(); i++)
			{
				m_vertices.emplace_back(tangentList.at(i), VertexCommonProperty::TANGENT);
			}
		}
		for (UINT i = 0; i < tangentList.size(); i++)
		{
			m_vertices.at(i).tangent = tangentList.at(i);
		}
	}

	void Mesh::SetColor(const std::vector<Float4>& colorList)
	{
		if (colorList.size() > m_vertices.size())
		{
			for (SIZE_T i = m_vertices.size(); i < colorList.size(); i++)
			{
				m_vertices.emplace_back(colorList.at(i));
			}
		}
		for (UINT i = 0; i < colorList.size(); i++)
		{
			m_vertices.at(i).color = colorList.at(i);
		}
	}

	void Mesh::SetUv0(const std::vector<Float2>& uvList)
	{
		if (uvList.size() > m_vertices.size())
		{
			for (SIZE_T i = m_vertices.size(); i < uvList.size(); i++)
			{
				m_vertices.emplace_back(uvList.at(i), VertexUvProperty::UV0);
			}
		}
		for (UINT i = 0; i < uvList.size(); i++)
		{
			m_vertices.at(i).uv0 = uvList.at(i);
		}
	}

	void Mesh::SetUv1(const std::vector<Float2>& uvList)
	{
		if (uvList.size() > m_vertices.size())
		{
			for (SIZE_T i = m_vertices.size(); i < uvList.size(); i++)
			{
				m_vertices.emplace_back(uvList.at(i), VertexUvProperty::UV1);
			}
		}
		for (UINT i = 0; i < uvList.size(); i++)
		{
			m_vertices.at(i).uv1 = uvList.at(i);
		}
	}

	void Mesh::SetUv2(const std::vector<Float2>& uvList)
	{
		if (uvList.size() > m_vertices.size())
		{
			for (SIZE_T i = m_vertices.size(); i < uvList.size(); i++)
			{
				m_vertices.emplace_back(uvList.at(i), VertexUvProperty::UV2);
			}
		}
		for (UINT i = 0; i < uvList.size(); i++)
		{
			m_vertices.at(i).uv2 = uvList.at(i);
		}
	}

	void Mesh::SetUv3(const std::vector<Float2>& uvList)
	{
		if (uvList.size() > m_vertices.size())
		{
			for (SIZE_T i = m_vertices.size(); i < uvList.size(); i++)
			{
				m_vertices.emplace_back(uvList.at(i), VertexUvProperty::UV3);
			}
		}
		for (UINT i = 0; i < uvList.size(); i++)
		{
			m_vertices.at(i).uv3 = uvList.at(i);
		}
	}

	void Mesh::SetUv4(const std::vector<Float2>& uvList)
	{
		if (uvList.size() > m_vertices.size())
		{
			for (SIZE_T i = m_vertices.size(); i < uvList.size(); i++)
			{
				m_vertices.emplace_back(uvList.at(i), VertexUvProperty::UV4);
			}
		}
		for (UINT i = 0; i < uvList.size(); i++)
		{
			m_vertices.at(i).uv4 = uvList.at(i);
		}
	}
}

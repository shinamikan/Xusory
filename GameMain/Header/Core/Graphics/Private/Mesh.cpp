#include "../Mesh.h"

namespace XusoryEngine
{
	Mesh::Mesh(UINT verticesNum, UINT indicesNum)
	{
		m_vertices.resize(verticesNum);
		m_indices.resize(indicesNum);
	}

	const std::wstring& Mesh::GetMeshFilePath() const
	{
		return m_meshFilePath;
	}

	const std::vector<Vertex>& Mesh::GetVertices() const
	{
		return m_vertices;
	}

	const std::vector<UINT>& Mesh::GetIndices() const
	{
		return m_indices;
	}

	void Mesh::SetVertices(std::vector<Vertex>& vertices)
	{
		m_vertices.assign(vertices.begin(), vertices.end());
	}

	void Mesh::SetIndices(std::vector<UINT>& indices)
	{
		m_indices.assign(indices.begin(), indices.end());
	}

	UINT Mesh::GetVerticesNum() const
	{
		return static_cast<UINT>(m_vertices.size());
	}

	UINT Mesh::GetIndicesNum() const
	{
		return static_cast<UINT>(m_indices.size());
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

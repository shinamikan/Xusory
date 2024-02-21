#include "../Mesh.h"

namespace XusoryEngine
{
	Mesh::Mesh(UINT verticesNum, UINT indicesNum)
	{
		vertices.resize(verticesNum);
		indices.resize(indicesNum);
	}

	const std::vector<Vertex>& Mesh::GetVertices() const
	{
		return vertices;
	}

	const std::vector<UINT>& Mesh::GetIndices() const
	{
		return indices;
	}

	void Mesh::SetVertices(std::vector<Vertex>& p_vertices)
	{
		vertices.assign(p_vertices.begin(), p_vertices.end());
	}

	void Mesh::SetIndices(std::vector<UINT>& p_indices)
	{
		indices.assign(p_indices.begin(), p_indices.end());
	}

	void Mesh::SetPosition(const std::vector<Float3>& positionList)
	{
		for (UINT i = 0; i < vertices.size(); i++)
		{
			vertices.at(i).position = positionList.at(i);
		}
		if (positionList.size() > vertices.size())
		{
			for (SIZE_T i = vertices.size(); i < positionList.size(); i++)
			{
				vertices.push_back(Vertex(positionList.at(i), VertexCommonProperty::POSITION));
			}
		}
	}

	void Mesh::SetNormal(const std::vector<Float3>& normalList)
	{
		for (UINT i = 0; i < vertices.size(); i++)
		{
			vertices.at(i).normal = normalList.at(i);
		}
		if (normalList.size() > vertices.size())
		{
			for (SIZE_T i = vertices.size(); i < normalList.size(); i++)
			{
				vertices.push_back(Vertex(normalList.at(i), VertexCommonProperty::NORMAL));
			}
		}
	}

	void Mesh::SetTangent(const std::vector<Float3>& tangentList)
	{
		for (UINT i = 0; i < vertices.size(); i++)
		{
			vertices.at(i).tangent = tangentList.at(i);
		}
		if (tangentList.size() > vertices.size())
		{
			for (SIZE_T i = vertices.size(); i < tangentList.size(); i++)
			{
				vertices.push_back(Vertex(tangentList.at(i), VertexCommonProperty::TANGENT));
			}
		}
	}

	void Mesh::SetColor(const std::vector<Float4>& colorList)
	{
		for (UINT i = 0; i < vertices.size(); i++)
		{
			vertices.at(i).color = colorList.at(i);
		}
		if (colorList.size() > vertices.size())
		{
			for (SIZE_T i = vertices.size(); i < colorList.size(); i++)
			{
				vertices.push_back(Vertex(colorList.at(i)));
			}
		}
	}

	void Mesh::SetUv0(const std::vector<Float2>& uvList)
	{
		for (UINT i = 0; i < vertices.size(); i++)
		{
			vertices.at(i).uv0 = uvList.at(i);
		}
		if (uvList.size() > vertices.size())
		{
			for (SIZE_T i = vertices.size(); i < uvList.size(); i++)
			{
				vertices.push_back(Vertex(uvList.at(i), VertexUvProperty::UV0));
			}
		}
	}

	void Mesh::SetUv1(const std::vector<Float2>& uvList)
	{
		for (UINT i = 0; i < vertices.size(); i++)
		{
			vertices.at(i).uv1 = uvList.at(i);
		}
		if (uvList.size() > vertices.size())
		{
			for (SIZE_T i = vertices.size(); i < uvList.size(); i++)
			{
				vertices.push_back(Vertex(uvList.at(i), VertexUvProperty::UV1));
			}
		}
	}

	void Mesh::SetUv2(const std::vector<Float2>& uvList)
	{
		for (UINT i = 0; i < vertices.size(); i++)
		{
			vertices.at(i).uv2 = uvList.at(i);
		}
		if (uvList.size() > vertices.size())
		{
			for (SIZE_T i = vertices.size(); i < uvList.size(); i++)
			{
				vertices.push_back(Vertex(uvList.at(i), VertexUvProperty::UV2));
			}
		}
	}

	void Mesh::SetUv3(const std::vector<Float2>& uvList)
	{
		for (UINT i = 0; i < vertices.size(); i++)
		{
			vertices.at(i).uv3 = uvList.at(i);
		}
		if (uvList.size() > vertices.size())
		{
			for (SIZE_T i = vertices.size(); i < uvList.size(); i++)
			{
				vertices.push_back(Vertex(uvList.at(i), VertexUvProperty::UV3));
			}
		}
	}

	void Mesh::SetUv4(const std::vector<Float2>& uvList)
	{
		for (UINT i = 0; i < vertices.size(); i++)
		{
			vertices.at(i).uv4 = uvList.at(i);
		}
		if (uvList.size() > vertices.size())
		{
			for (SIZE_T i = vertices.size(); i < uvList.size(); i++)
			{
				vertices.push_back(Vertex(uvList.at(i), VertexUvProperty::UV4));
			}
		}
	}
}

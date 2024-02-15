#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	class Mesh
	{
    public:
        Mesh() = default;

        std::vector<Vertex>& GetVerticesList() const;
        std::vector<UINT>& GetIndicesList() const;

        void SetPosition(const std::vector<Float3>& positionList) const;
        void SetNormal(const std::vector<Float3>& normalList) const;
        void SetTangent(const std::vector<Float3>& tangentList) const;
        void SetColor(const std::vector<Float4>& colorList) const;
        void SetUv0(const std::vector<Float2>& uvList) const;
        void SetUv1(const std::vector<Float2>& uvList) const;
        void SetUv2(const std::vector<Float2>& uvList) const;
        void SetUv3(const std::vector<Float2>& uvList) const;
        void SetUv4(const std::vector<Float2>& uvList) const;

        std::string name;

    private:
        std::vector<Vertex>* vertices;
        std::vector<UINT>* indices;
	};
}

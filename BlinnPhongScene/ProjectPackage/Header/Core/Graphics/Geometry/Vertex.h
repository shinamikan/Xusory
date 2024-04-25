#pragma once

#include "../../Math/Vector2.h"
#include "../../Math/Vector3.h"
#include "../../Math/Vector4.h"

namespace XusoryEngine
{
    enum class VertexCommonProperty
    {
        POSITION = 0,
        NORMAL,
        TANGENT,
    };

	enum class VertexUvProperty
	{
        UV0 = 0,
        UV1,
        UV2,
        UV3,
        UV4,
	};

	struct Vertex
	{
        Vertex() = default;
        Vertex(const Float2& value, VertexUvProperty property)
        {
	        switch (property)
	        {
	        case VertexUvProperty::UV0:
                uv0 = value;
                break;
            case VertexUvProperty::UV1:
                uv1 = value;
                break;
            case VertexUvProperty::UV2:
                uv2 = value;
                break;
            case VertexUvProperty::UV3:
                uv3 = value;
                break;
            case VertexUvProperty::UV4:
                uv4 = value;
                break;
	        }
        }
        Vertex(const Float3& value, VertexCommonProperty property)
        {
            switch (property)
            {
            case VertexCommonProperty::POSITION:
                position = value;
                break;
            case VertexCommonProperty::NORMAL:
                normal = value;
                break;
            case VertexCommonProperty::TANGENT:
                tangent = value;
                break;
            }
        }
        explicit Vertex(const Float4& value)
        {
            color = value;
        }

        Vertex(const Float3& position, const Float3& normal, const Float3& tangent, const Float2& uv) :
            position(position), normal(normal), tangent(tangent), uv0(uv) { }
        Vertex(const Float3& position, const Float3& normal, const Float3& tangent, const Float2& uv0,
            const Float2& uv1, const Float2& uv2, const Float2& uv3, const Float2& uv4) :
            position(position), normal(normal), tangent(tangent),
			uv0(uv0), uv1(uv1), uv2(uv2), uv3(uv3), uv4(uv4) { }

        Float3 position = Float3();
        Float3 normal = Float3();
        Float3 tangent = Float3();
        Float4 color = Float4();

        Float2 uv0 = Float2();
        Float2 uv1 = Float2();
        Float2 uv2 = Float2();
        Float2 uv3 = Float2();
        Float2 uv4 = Float2();
	};
}

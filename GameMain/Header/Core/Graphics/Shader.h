#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "../../RHI/RHI.h"
#include "Common/GraphicsDefine.h"

namespace XusoryEngine
{
	enum class GraphicsFillMode
	{
		WIRE_FRAME = 2,
		SOLID = 3
	};

	enum class GraphicsCullMode
	{
		NONE = 1,
		FRONT = 2,
		BACK = 3
	};

	enum class TriangleWindingOrder
	{
		ANTI_CLOCK_WISE = 0,
		CLOCK_WISE
	};

	enum class ShaderPropertyType
	{
		INT = 0,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		MATRIX2,
		MATRIX3,
		MATRIX4,
		TEXTURE
	};

	struct ShaderByte
	{
		std::vector<BYTE> byteCode;
		SIZE_T byteSize;
	};

	struct ShaderCBufferProperty
	{
		std::string name;

		UINT size;
		UINT variableNum;

		UINT slot;
		UINT space;
	};

	struct ShaderProperty
	{
		std::string name;
		UINT index;

		ShaderPropertyType propertyType;
		TextureDimension dimension;

		UINT offset;
		UINT slot;
		UINT space;
	};

	class Shader
	{
		friend class GiDx12RhiManager;
		friend class DxShaderLoader;
		friend class ResourceLoader;

	public:
		Shader() = default;
		DELETE_COPY_OPERATOR(Shader);
		DELETE_MOVE_OPERATOR(Shader);
		~Shader();

		const std::string& GetName() const;

		const std::array<std::string, 5>& GetShaderEntryPoint() const;
		const std::string& GetVertexShaderEntryPoint() const;
		const std::string& GetPixelShaderEntryPoint() const;
		const std::string& GetDomainShaderEntryPoint() const;
		const std::string& GetHullShaderEntryPoint() const;
		const std::string& GetGeometryShaderEntryPoint() const;

		GraphicsFillMode GetGraphicsFillMode() const;
		GraphicsCullMode GetGraphicsCullMode() const;
		TriangleWindingOrder GetTriangleWindingOrder() const;

		UINT GetCBufferCount() const;
		const ShaderCBufferProperty& GetCBufferProperty(UINT index) const;

		UINT GetPropertyCount() const;
		const std::string& GetPropertyNameByIndex(UINT index) const;
		const ShaderProperty& GetPropertyByIndex(UINT index) const;
		ShaderPropertyType GetPropertyTypeByIndex(UINT index) const;
		UINT GetPropertyOffsetByIndex(UINT index) const;
		UINT GetPropertySlotByIndex(UINT index) const;
		UINT GetPropertySpaceByIndex(UINT index) const;

		UINT GetPropertyIndexByName(const std::string_view& name) const;
		const ShaderProperty& GetPropertyByName(const std::string_view& name) const;
		ShaderPropertyType GetPropertyTypeByName(const std::string_view& name) const;
		UINT GetPropertyOffsetByName(const std::string_view& name) const;
		UINT GetPropertySlotByName(const std::string_view& name) const;
		UINT GetPropertySpaceByName(const std::string_view& name) const;

	private:
		void ThrowIfOutOfCBufferRange(UINT index) const;
		void ThrowIfOutOfPropertyRange(UINT index) const;

		void SetVertexShaderEntryPoint(const std::string_view& entryPoint);
		void SetPixelShaderEntryPoint(const std::string_view& entryPoint);
		void SetDomainShaderEntryPoint(const std::string_view& entryPoint);
		void SetHullShaderEntryPoint(const std::string_view& entryPoint);
		void SetGeometryShaderEntryPoint(const std::string_view& entryPoint);

		std::string m_name;
		std::array<std::string, 5> m_shaderEntryPointList;

		GraphicsFillMode m_fillMode = GraphicsFillMode::SOLID;
		GraphicsCullMode m_cullMode = GraphicsCullMode::BACK;
		TriangleWindingOrder m_triangleWindingOrder = TriangleWindingOrder::CLOCK_WISE;

		std::vector<ShaderByte> m_shaderByteList{5};

		std::vector<ShaderCBufferProperty> m_shaderCBufferPropertyList;
		std::vector<ShaderProperty> m_shaderPropertyList;
		std::unordered_map<std::string, ShaderProperty&> m_shaderPropertyMap;
	};
}

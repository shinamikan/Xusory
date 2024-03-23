#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	class IMeshLoader
	{
	public:
		IMeshLoader() = default;
		DELETE_COPY_OPERATOR(IMeshLoader);
		DELETE_MOVE_OPERATOR(IMeshLoader);
		virtual ~IMeshLoader() = default;

		virtual std::shared_ptr<Mesh> LoadMesh(const std::wstring_view& path) = 0;
		virtual std::vector<std::shared_ptr<Mesh>> LoadSeveralMesh(const std::wstring_view& path) = 0;
	};

	class ObjMeshLoader : public IMeshLoader
	{
	public:
		std::shared_ptr<Mesh> LoadMesh(const std::wstring_view& path) override;
		std::vector<std::shared_ptr<Mesh>> LoadSeveralMesh(const std::wstring_view& path) override;

		CREATE_FACTORY(IMeshLoader, ObjMeshLoader);
	};

	class IObjParser
	{
	public:
		IObjParser() = default;
		DELETE_COPY_OPERATOR(IObjParser);
		DELETE_MOVE_OPERATOR(IObjParser);
		virtual ~IObjParser() = default;

		virtual std::shared_ptr<Mesh> ParseObjMesh(const std::vector<std::string_view>& meshDataList,
			std::vector<Float3>& positionList, std::vector<Float3>& normalList, std::vector<Float2>& uvList,
			UINT& dataIndex, UINT positionNum, UINT normalNum, UINT uvNum) = 0;
	};

	class BlenderObjLoader : public IObjParser
	{
	public:
		std::shared_ptr<Mesh> ParseObjMesh(const std::vector<std::string_view>& meshDataList,
			std::vector<Float3>& positionList, std::vector<Float3>& normalList, std::vector<Float2>& uvList,
			UINT& dataIndex, UINT positionNum, UINT normalNum, UINT uvNum) override;
		CREATE_FACTORY(IObjParser, BlenderObjLoader);
	};

	class C4dObjLoader : public IObjParser
	{
	public:
		std::shared_ptr<Mesh> ParseObjMesh(const std::vector<std::string_view>& meshDataList,
			std::vector<Float3>& positionList, std::vector<Float3>& normalList, std::vector<Float2>& uvList,
			UINT& dataIndex, UINT positionNum, UINT normalNum, UINT uvNum) override;
		CREATE_FACTORY(IObjParser, C4dObjLoader);
	};

	class MaxObjLoader : public IObjParser
	{
	public:
		std::shared_ptr<Mesh> ParseObjMesh(const std::vector<std::string_view>& meshDataList,
			std::vector<Float3>& positionList, std::vector<Float3>& normalList, std::vector<Float2>& uvList,
			UINT& dataIndex, UINT positionNum, UINT normalNum, UINT uvNum) override;
		CREATE_FACTORY(IObjParser, MaxObjLoader);
	};

	typedef FactoryBase<IMeshLoader> MeshLoaderFactory;
	typedef FactoryBase<IObjParser> ObjParserFactory;
}

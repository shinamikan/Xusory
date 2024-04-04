#pragma once

#include "../../Core/Core.h"

namespace XusoryEngine
{
	DLL_CLASS(IMeshLoader)
	{
	public:
		IMeshLoader() = default;
		DELETE_COPY_OPERATOR(IMeshLoader);
		DELETE_MOVE_OPERATOR(IMeshLoader);
		virtual ~IMeshLoader() = default;

		virtual std::shared_ptr<Mesh> LoadMesh(const std::wstring_view& path) = 0;
		virtual std::vector<std::shared_ptr<Mesh>> LoadSeveralMesh(const std::wstring_view& path) = 0;
	};

	DLL_CLASS(ObjMeshLoader) : public IMeshLoader
	{
	public:
		std::shared_ptr<Mesh> LoadMesh(const std::wstring_view& path) override;
		std::vector<std::shared_ptr<Mesh>> LoadSeveralMesh(const std::wstring_view& path) override;

		CREATE_FACTORY(IMeshLoader, ObjMeshLoader);
	};

	DLL_CLASS(IObjParser)
	{
	public:
		IObjParser() = default;
		DELETE_COPY_OPERATOR(IObjParser);
		DELETE_MOVE_OPERATOR(IObjParser);
		virtual ~IObjParser() = default;

		virtual std::shared_ptr<Mesh> ParseObjMesh(const std::vector<std::string_view>& meshDataList, UINT& dataIndex,
			std::vector<Float3>& positionList, std::vector<Float3>& normalList, std::vector<Float2>& uvList) = 0;
	};

	DLL_CLASS(BlenderObjLoader) : public IObjParser
	{
	public:
		std::shared_ptr<Mesh> ParseObjMesh(const std::vector<std::string_view>& meshDataList, UINT& dataIndex,
			std::vector<Float3>& positionList, std::vector<Float3>& normalList, std::vector<Float2>& uvList) override;
		CREATE_FACTORY(IObjParser, BlenderObjLoader);
	};

	DLL_CLASS(C4dObjLoader) : public IObjParser
	{
	public:
		std::shared_ptr<Mesh> ParseObjMesh(const std::vector<std::string_view>& meshDataList, UINT& dataIndex,
			std::vector<Float3>& positionList, std::vector<Float3>& normalList, std::vector<Float2>& uvList) override;
		CREATE_FACTORY(IObjParser, C4dObjLoader);
	};

	DLL_CLASS(MaxObjLoader) : public IObjParser
	{
	public:
		std::shared_ptr<Mesh> ParseObjMesh(const std::vector<std::string_view>& meshDataList, UINT& dataIndex,
			std::vector<Float3>& positionList, std::vector<Float3>& normalList, std::vector<Float2>& uvList) override;
		CREATE_FACTORY(IObjParser, MaxObjLoader);
	};

	typedef FactoryBase<IMeshLoader> MeshLoaderFactory;
	typedef FactoryBase<IObjParser> ObjParserFactory;

	REGISTER_FACTORY(MeshLoaderFactory, ObjMeshLoader, TEXT("obj"));
	REGISTER_FACTORY(ObjParserFactory, BlenderObjLoader, "Blender");
	REGISTER_FACTORY(ObjParserFactory, C4dObjLoader, "Cinema4D");
	REGISTER_FACTORY(ObjParserFactory, MaxObjLoader, "3dsMax");
}

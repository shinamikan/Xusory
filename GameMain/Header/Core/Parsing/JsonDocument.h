#pragma once

#include "../../3rdParty/jsoncpp/json.h"

namespace XusoryEngine
{
	using JsonNode = Json::Value;

	enum class JsonWriteMode
	{
		EXISTING = 0,
		CREATING
	};

	class JsonDocument
	{
	public:
		JsonDocument() = default;
		JsonDocument(const std::wstring_view& jsonFilePath);

		void LoadJsonFromStr(const std::string_view& jsonStr);
		void LoadJsonFromFile(const std::wstring_view& jsonFilePath);

		JsonNode& GetRootNode();
		void SetRootNode(const JsonNode& node);

		void ClearRootNode();
		void SaveJson(const std::wstring_view& jsonFilePath, JsonWriteMode writeMode = JsonWriteMode::CREATING) const;

	private:
		Json::Reader m_reader;
		JsonNode m_rootNode;
	};
}

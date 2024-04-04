#include "../JsonDocument.h"
#include "../../../Platform/Platform.h"

namespace XusoryEngine
{
	JsonDocument::JsonDocument(const std::wstring_view& jsonFilePath)
	{
		LoadJsonFromFile(jsonFilePath);
	}

	void JsonDocument::LoadJsonFromStr(const std::string_view& jsonStr)
	{
		if (!m_reader.parse(jsonStr.data(), m_rootNode))
		{
			ThrowWithErrName(RuntimeError, FailedInfo("parse json file"));
		}
	}

	void JsonDocument::LoadJsonFromFile(const std::wstring_view& jsonFilePath)
	{
		const auto jsonFile = File(jsonFilePath, FileOpenMode::READ);

		if (const auto jsonStr = jsonFile.ReadText(); !m_reader.parse(jsonStr, m_rootNode))
		{
			ThrowWithErrName(RuntimeError, FailedInfo("parse json file"));
		}
	}

	JsonNode& JsonDocument::GetRootNode()
	{
		return m_rootNode;
	}

	JsonNode* JsonDocument::GetRootNodePtr()
	{
		return &m_rootNode;
	}

	void JsonDocument::SetRootNode(const JsonNode& node)
	{
		m_rootNode = node;
	}

	void JsonDocument::ClearRootNode()
	{
		m_rootNode = Json::Value();
	}

	void JsonDocument::SaveJson(const std::wstring_view& jsonFilePath, JsonWriteMode writeMode) const
	{
		const auto openMode = writeMode == JsonWriteMode::EXISTING ? FileOpenMode::WRITE : FileOpenMode::WRITE_ADD;
		const auto jsonFile = File(jsonFilePath, openMode);

		Json::StyledWriter writer;
		const std::string jsonStr = writer.write(m_rootNode);

		jsonFile.Write(jsonStr.data(), jsonStr.size());
	}
}

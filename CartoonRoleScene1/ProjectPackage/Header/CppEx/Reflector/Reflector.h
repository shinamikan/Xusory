#pragma once

#include <iostream>
#include <unordered_map>

#include "../ClassEx/ClassEx.h"
#include "../Error/Throw.h"

STD_ERROR_CLASS(FieldError, LogicError)
END_CLASS;

enum class MemberType
{
	VARIABLE = 0,
	FUNCTION,
};

struct FieldInfo
{
	FieldInfo(MemberType memberType, const std::string_view& access, const std::string_view& type, const std::string_view& name)
		: memberType(memberType),  access(access), type(type), name(name) { }

	MemberType memberType;

	std::string access;
	std::string type;
	std::string name;
};

class ReflectorField
{
public:
	ReflectorField(MemberType memberType, const std::string_view& access, const std::string_view& type, const std::string_view& fieldName, void* valPtr,
		std::unordered_map<std::string, ReflectorField*>& fieldMap, std::unordered_map<std::string, FieldInfo>& fieldInfoMap)
		: m_fieldPtr(valPtr)
	{
		fieldMap.emplace(fieldName, this);
		fieldInfoMap.emplace(fieldName, FieldInfo(memberType, access, type, fieldName));
	}

	void* GetFieldPtr() const
	{
		return m_fieldPtr;
	}

private:
	void* m_fieldPtr;
};

#define REFLECT_CLASS															\
public:																			\
	static const FieldInfo& GetFieldInfo(const std::string_view& fieldName)		\
	{																			\
		if (sm_fieldInfoMap.find(fieldName.data()) == sm_fieldInfoMap.end())	\
		{																		\
			ThrowWithErrName(FieldError, "Class does not have this member");	\
		}																		\
		return sm_fieldInfoMap.at(fieldName.data());							\
	}																			\
	template <typename T>														\
	T& GetField(const std::string_view& fieldName)								\
	{																			\
		if (m_fieldMap.find(fieldName.data()) == m_fieldMap.end())				\
		{																		\
			ThrowWithErrName(FieldError, "Class does not have this member");	\
		}																		\
		const ReflectorField* field = m_fieldMap.at(fieldName.data());			\
		return *static_cast<T*>(field->GetFieldPtr());							\
	}																			\
	auto GetFieldCount() const													\
	{																			\
		return m_fieldMap.size();												\
	}																			\
	const std::unordered_map<std::string, ReflectorField*>& GetReflectorMap()	\
	{																			\
		return m_fieldMap;														\
	}																			\
private:																		\
	static std::unordered_map<std::string, FieldInfo> sm_fieldInfoMap;			\
	std::unordered_map<std::string, ReflectorField*> m_fieldMap				

#define INIT_STATIC_REFLECTOR(className) \
	std::unordered_map<std::string, FieldInfo> className::sm_fieldInfoMap = std::unordered_map<std::string, FieldInfo>()

#define REFLECT_VARIABLE(access, variableType, variableName)																							\
private:																																				\
	ReflectorField m_field##variableName{ MemberType::VARIABLE, #access, #variableType, #variableName, &variableName, m_fieldMap, sm_fieldInfoMap };	\
access:																																					\
	variableType variableName

#define REFLECT_VARIABLE_WITH_VALUE(access, variableType, variableName, value)																			\
private:																																				\
	ReflectorField m_field##variableName{ MemberType::VARIABLE, #access, #variableType, #variableName, &variableName, m_fieldMap, sm_fieldInfoMap };	\
access:																																					\
	variableType variableName = value

#define REFLECT_FUNCTION(className, access, returnType, funcName, ...)																									\
public:																																									\
	typedef returnType (className::*funcName##Type)(__VA_ARGS__);																										\
private:																																								\
	funcName##Type m_fieldFunc##funcName = &className::funcName;																										\
	ReflectorField m_field##funcName{ MemberType::FUNCTION, #access, #returnType, #funcName, static_cast<void*>(&m_fieldFunc##funcName), m_fieldMap, sm_fieldInfoMap };	\
access:																																									\
	returnType funcName(__VA_ARGS__)

#define REFLECT_CONST_FUNCTION(className, access, returnType, funcName, ...)																							\
public:																																									\
	typedef returnType (className::*funcName##Type)(__VA_ARGS__) const;																									\
private:																																								\
	funcName##Type m_fieldFunc##funcName = &className::funcName;																										\
	ReflectorField m_field##funcName{ MemberType::FUNCTION, #access, #returnType, #funcName, static_cast<void*>(&m_fieldFunc##funcName), m_fieldMap, sm_fieldInfoMap };	\
access:																																									\
	returnType funcName(__VA_ARGS__) const

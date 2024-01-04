#pragma once

#pragma warning(disable : 4834)

#include <iostream>
#include <unordered_map>

#include "../Error/Throw.h"

STD_ERROR_CLASS(FieldError, LogicError)
END_CLASS;

class ReflectorField
{
public:
	ReflectorField(const std::string& fieldName, void* valPtr, std::unordered_map<std::string, ReflectorField*>& fieldMap)
		: m_fieldPtr(valPtr)
	{
		fieldMap[fieldName] = this;
	}

	void* GetFieldPtr() const
	{
		return m_fieldPtr;
	}

private:
	void* m_fieldPtr;
};

#define REGISTER_CLASS															\
public:																			\
	template <typename T>														\
	T& GetField(const std::string& fieldName)									\
	{																			\
		if (m_reflectorMap.find(fieldName) == m_reflectorMap.end())				\
		{																		\
			ThrowWithErrName(FieldError, "Class does not have this member");	\
		}																		\
		ReflectorField* field = m_reflectorMap.at(fieldName);					\
		return *static_cast<T*>(field->GetFieldPtr());							\
	}																			\
	auto GetFieldCount() const													\
	{																			\
		return m_reflectorMap.size();											\
	}																			\
	const std::unordered_map<std::string, ReflectorField*>& GetReflectorMap()	\
	{																			\
		return m_reflectorMap;													\
	}																			\
private:																		\
	std::unordered_map<std::string, ReflectorField*> m_reflectorMap

#define ADD_FIELD(access, fieldType, fieldName, value)	\
access:													\
	fieldType fieldName = value;						\
private:												\
	ReflectorField m_field##fieldName{ #fieldName, &fieldName, m_reflectorMap }

#define ADD_FUNC_FIELD(access, returnType, funcName, ...)					\
access:																		\
	returnType funcName(__VA_ARGS__);										\
private:																	\
	typedef returnType (TestReflectClass::*funcName##Type)(__VA_ARGS__);	\
	funcName##Type m_fieldFunc##funcName = &TestReflectClass::funcName;		\
	ReflectorField m_field##funcName{ #funcName, static_cast<void*>(&m_fieldFunc##funcName), m_reflectorMap }

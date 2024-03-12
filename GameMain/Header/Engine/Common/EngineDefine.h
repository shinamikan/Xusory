#pragma once

#include "../../Core/Core.h"

#define XS_CLASS REFLECT_CLASS;
#define INIT_XS_CLASS(className) INIT_STATIC_REFLECTOR(className)

#define EXPOSED_VARIABLE REFLECT_FIELD
#define EXPOSED_VARIABLE_VALUE REFLECT_FIELD_WITH_VALUE
#define EXPOSED_FUNCTION REFLECT_FUNC_FIELD
#define EXPOSED_CONST_FUNCTION REFLECT_CONST_FUNC_FIELD

#define HIDDEN_VARIABLE(access, returnType, variableName)	\
access:														\
	returnType variableName						
#define HIDDEN_VARIABLE_VALUE(access, returnType, variableName, value)	\
access:																	\
	returnType variableName = value

#define HIDDEN_FUNCTION(access, returnType, funcName, ...)	\
	access:													\
		returnType funcName(__VA_ARGS__)
#define HIDDEN_CONST_FUNCTION(access, returnType, funcName, ...)	\
	access:															\
		returnType funcName(__VA_ARGS__) const


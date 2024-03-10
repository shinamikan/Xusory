#pragma once

#include "../../Core/Core.h"

#define XS_CLASS REFLECT_CLASS;
#define INIT_XS_CLASS(className) INIT_STATIC_REFLECTOR(className)

#define EXPOSED_VARIABLE REFLECT_FIELD
#define EXPOSED_VARIABLE_VALUE REFLECT_FIELD_WITH_VALUE

#define HIDDEN_VARIABLE(access, fieldType, fieldName)	\
access:													\
	fieldType fieldName;								
#define HIDDEN_VARIABLE_VALUE(access, fieldType, fieldName, value)	\
access:																\
	fieldType fieldName = value;								

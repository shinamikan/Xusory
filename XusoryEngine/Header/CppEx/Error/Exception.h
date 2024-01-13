#pragma once

#include <iostream>
#include "../ClassEx/ClassEx.h"

// Extended Standard Library Error Class
#define STD_ERROR_CLASS(className, errorClass)						\
	CLASS(className) : public errorClass							\
	{																\
	static_assert(std::is_base_of_v<std::exception, errorClass>);	\
	public:															\
		using errorClass::errorClass;

// Std Error Redefine

using Exception = std::exception;

using LogicError		= std::logic_error;
using DomainError		= std::domain_error;
using InvalidArgument	= std::invalid_argument;
using LengthError		= std::length_error;
using OutOfRange		= std::out_of_range;

using RuntimeError		= std::runtime_error;
using SystemError		= std::system_error;
using RangeError		= std::range_error;
using OverflowError		= std::overflow_error;
using UnderflowError	= std::underflow_error;

// Extern Logic Error

STD_ERROR_CLASS(IndexError, OutOfRange)
END_CLASS;

STD_ERROR_CLASS(KeyError, OutOfRange)
END_CLASS;

// Extern Runtime Error

STD_ERROR_CLASS(AssertionError, RuntimeError)
END_CLASS;

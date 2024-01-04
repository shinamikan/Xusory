#pragma once

#include "../../XsCommon/DllDefine.h"

#define CLASS(className) class className
#define DLL_CLASS(className) class DLL_FUNC className
#define END_CLASS }

// Expand the interface class, you can use INTERFACE_CLASS defines an interface

#ifdef INTERFACE
#undef INTERFACE
#endif
#define INTERFACE(className) class __declspec(novtable) className
#define DLL_INTERFACE(className) class DLL_FUNC __declspec(novtable) className

// Expanding static classes, static classes cannot be instantiated or copied

class StaticBase
{
public:
	StaticBase() = delete;

	StaticBase(const StaticBase& rhs)	= delete;
	StaticBase(const StaticBase&& rhs)	= delete;
	StaticBase& operator=(const StaticBase& rhs)	= delete;
	StaticBase& operator=(const StaticBase&& rhs)	= delete;

	static void Init() { }
	static void Del() { }
};

#define STATIC_CLASS(className) CLASS(className) : public StaticBase
#define DLL_STATIC_CLASS(className) DLL_CLASS(className) : public StaticBase

#define INIT_STATIC_CLASS(className) className::Init()

// You can use PROPERTY macro to add the get set property to a class
#if defined(_MSC_VER)
#define PROPERTY(getFunc, setFunc, type, propName)							\
    public:																	\
        __declspec(property(get = getFunc, put = setFunc)) type propName;	\
        type getFunc() const;												\
        void setFunc(type value)
#define PROPERTY_GET(getFunc, type, propName)								\
	public:																	\
		__declspec(property(get = getFunc)) type propName;					\
		type getFunc()
#define PROPERTY_SET(setFunc, type, propName)								\
    public:																	\
        __declspec(property(put = setFunc)) type propName;					\
        void setFunc(type value)
#endif

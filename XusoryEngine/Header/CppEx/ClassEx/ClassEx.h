#pragma once

#include "../../XsCommon/DllDefine.h"

#define CLASS(className) class className
#define DLL_CLASS(className) class DLL_FUNC className
#define END_CLASS }

#define COPY_OPERATOR(className)					\
	className(const className& other);				\
	className& operator=(const className& other)

#define DEFAULT_COPY_OPERATOR(className)			\
	className(const className& other)	= default;	\
	className& operator=(const className& other) = default

#define DELETE_COPY_OPERATOR(className)				\
	className(const className& other)	= delete;	\
	className& operator=(const className& other) = delete

#define MOVE_OPERATOR(className)	\
	className(className&& other);	\
	className& operator=(className&& other)

#define DEFAULT_MOVE_OPERATOR(className)		\
	className(className&& other)	= default;	\
	className& operator=(className&& other) = default

#define DELETE_MOVE_OPERATOR(className)			\
	className(className&& other)	= delete;	\
	className& operator=(className&& other) = delete

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
	DELETE_COPY_OPERATOR(StaticBase);
	DELETE_MOVE_OPERATOR(StaticBase);
	~StaticBase() = default;

	static void Init() { }
	static void Del() { }
};

#define STATIC_CLASS(className) CLASS(className) : public StaticBase
#define DLL_STATIC_CLASS(className) DLL_CLASS(className) : public StaticBase

#define INIT_STATIC_CLASS(className, ...) className::Init(__VA_ARGS__)
#define DEL_STATIC_CLASS(className, ...) className::Del(__VA_ARGS__)

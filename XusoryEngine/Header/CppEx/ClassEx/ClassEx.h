#pragma once

#include "../DllDefine/DllDefine.h"
#include "../Name/Name.h"

#define CLASS(className) class className
#define DLL_CLASS(className) class DLL_FUNC className
#define END_CLASS }
#define DLL_STRUCT(structName) struct DLL_FUNC structName
#define END_STRUCT }

#define INTERNAL_CLASS(className)										\
	class SUFFIX_NAME(className, _Internal);							\
	static SUFFIX_NAME(className, _Internal) sm_internal##className;	\
	class SUFFIX_NAME(className, _Internal)

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
#define PROPERTY_GET_SET(type, propName)											\
    __declspec(property(get = Get##propName, put = Set##propName)) type propName;	\
    type Get##propName() const;												        \
    void Set##propName(type value)

#define REF_PROPERTY_GET_SET(type, propName)										\
    __declspec(property(get = Get##propName, put = Set##propName)) type propName;	\
    const type& Get##propName() const;												\
    void Set##propName(const type& value)

#define PROPERTY_GET_ONLY(type, propName)						\
	__declspec(property(get = Get##propName)) type propName;	\
	type Get##propName() const

#define REF_PROPERTY_GET_ONLY(type, propName)					\
	__declspec(property(get = Get##propName)) type propName;	\
    const type& Get##propName() const

#define PROPERTY_SET_ONLY(type, propName)				        \
    __declspec(property(set = Set##propName)) type propName;	\
    void Set##propName(type value)

#define REF_PROPERTY_SET_ONLY(type, propName)			        \
    __declspec(property(set = Set##propName)) type propName;	\
    void Set##propName(const type& value)
#endif

// Expand the interface class, you can use INTERFACE_CLASS defines an interface

#ifdef INTERFACE
#undef INTERFACE
#endif
#define INTERFACE(className) class __declspec(novtable) className
#define DLL_INTERFACE(className) class DLL_FUNC __declspec(novtable) className

// Expanding static classes, static classes cannot be instantiated or copied

DLL_CLASS(StaticBase)
{
public:
	StaticBase() = delete;
	DELETE_COPY_OPERATOR(StaticBase);
	DELETE_MOVE_OPERATOR(StaticBase);
	~StaticBase() = default;
};

#define STATIC_CLASS(className) CLASS(className) : public StaticBase
#define DLL_STATIC_CLASS(className) DLL_CLASS(className) : public StaticBase

#define INIT_STATIC_CLASS(className, ...) className::Init(__VA_ARGS__)
#define DEL_STATIC_CLASS(className, ...) className::Del(__VA_ARGS__)

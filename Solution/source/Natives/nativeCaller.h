/*
	THIS FILE IS A PART OF GTA V SCRIPT HOOK SDK
				http://dev-c.com			
			(C) Alexander Blade 2015
*/

#pragma once

#include "..\main.h"

// Zorg93
template <typename T>
static inline void nativePush(T value)
{
	UINT64 val64 = 0;
	static_assert(sizeof(T) <= sizeof(UINT64), "error, value size > 64 bit");
	*reinterpret_cast<T *>(&val64) = value; // &val + sizeof(dw) - sizeof(val)
	nativePush64(val64);
}

////Helper for pushing a std::string
//static inline void nativePush(const std::string& value)
//{
//	nativePush(value.c_str());
//}

template <typename R, typename... TArgs>
static inline R invoke(UINT64 hash, TArgs... args)
{
	static_assert(sizeof...(TArgs) <= 25, "Cannot push more than 25 Args to a native");
	static_assert(sizeof(R) <= 24, "Natives cannot return data types larger than 24 bytes");
	nativeInit(hash);
	(nativePush(args), ...);
	return *reinterpret_cast<R *>(nativeCall());
}

template <typename R>
inline R invoke(UINT64 hash)
{
	static_assert(sizeof(R) <= 24, "Natives cannot return data types larger than 24 bytes");
	nativeInit(hash);
	return *reinterpret_cast<R *>(nativeCall());
}


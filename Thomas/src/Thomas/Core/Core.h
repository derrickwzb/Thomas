/******************************************************************************/
/*!
\file		Core.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file contains the core macros for the game engine.

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include <memory>

#ifdef TH_PLATFORM_WINDOWS
	#ifdef TH_BUILD_DLL
		#define THOMAS_API 
	#else
		#define THOMAS_API 
	#endif
#else
	#error Thomas only supports Windows!
#endif

#ifdef TH_DEBUG
	#if defined(TH_PLATFORM_WINDOWS)
		#define TH_DEBUGBREAK() __debugbreak()
	#else 
		#error "Platform doesnt support debugbreak yet"
	#endif
	#define TH_ENABLE_ASSERTS
#else
	#define TH_DEBUGBREAK()
#endif

#ifdef TH_ENABLE_ASSERTS
#define TH_ASSERT(x, ...) { if(!(x)) { TH_ERROR("Assertion Failed: {0}", __VA_ARGS__); TH_DEBUGBREAK(); } }
#define TH_CORE_ASSERT(x, ...) { if(!(x)) { TH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); TH_DEBUGBREAK(); } }
#else
#define TH_ASSERT(x, ...)
#define TH_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)

#define TH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Thomas
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
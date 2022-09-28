#pragma once

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
#define TH_ENABLE_ASSERTS
#endif

#ifdef TH_ENABLE_ASSERTS
#define TH_ASSERT(x, ...) { if(!(x)) { TH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define TH_CORE_ASSERT(x, ...) { if(!(x)) { TH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define TH_ASSERT(x, ...)
#define TH_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)

#define TH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
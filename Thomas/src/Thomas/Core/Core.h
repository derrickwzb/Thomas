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

#define BIT(x) (1<<x)

#define TH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#pragma once

#ifdef TH_PLATFORM_WINDOWS
	#ifdef TH_BUILD_DLL
		#define THOMAS_API __declspec(dllexport)
	#else
		#define THOMAS_API __declspec(dllimport)
	#endif
#else
	#error Thomas only supports Windows!
#endif
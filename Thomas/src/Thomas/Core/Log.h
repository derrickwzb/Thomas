#pragma once

#include <memory>

#include "Core.h"

#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>

namespace Thomas
{
	class THOMAS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define TH_CORE_TRACE(...)    ::Thomas::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TH_CORE_INFO(...)     ::Thomas::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TH_CORE_WARN(...)     ::Thomas::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TH_CORE_ERROR(...)    ::Thomas::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TH_CORE_FATAL(...)    ::Thomas::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define TH_TRACE(...)	      ::Thomas::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TH_INFO(...)	      ::Thomas::Log::GetClientLogger()->info(__VA_ARGS__)
#define TH_WARN(...)	      ::Thomas::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TH_ERROR(...)	      ::Thomas::Log::GetClientLogger()->error(__VA_ARGS__)
#define TH_FATAL(...)	      ::Thomas::Log::GetClientLogger()->fatal(__VA_ARGS__)


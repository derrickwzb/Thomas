/******************************************************************************/
/*!
\file		Log.h
\author 	Derrick Woo
\par    	email: d.woo@digipen.edu
\date   	25/9/2022
\brief		This file represents the class abstraction of the Log system

Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include <memory>

#include "Core.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

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


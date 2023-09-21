#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Fragment 
{
	class FRAGMENT_API Log
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
#define FRG_CORE_CRITICAL(...)	::Fragment::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define FRG_CORE_ERROR(...)		::Fragment::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FRG_CORE_WARNING(...)	::Fragment::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FRG_CORE_INFO(...)		::Fragment::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FRG_CORE_TRACE(...)		::Fragment::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define FRG_CRITICAL(...)	::Fragment::Log::GetClientLogger()->critical(__VA_ARGS__)
#define FRG_ERROR(...)		::Fragment::Log::GetClientLogger()->error(__VA_ARGS__)
#define FRG_WARNING(...)	::Fragment::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FRG_INFO(...)		::Fragment::Log::GetClientLogger()->info(__VA_ARGS__)
#define FRG_TRACE(...)		::Fragment::Log::GetClientLogger()->trace(__VA_ARGS__)


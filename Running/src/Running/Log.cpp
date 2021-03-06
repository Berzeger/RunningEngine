#include "pch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Running
{
	std::shared_ptr<spdlog::logger> Running::Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Running::Log::s_ClientLogger;

	void Running::Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Running");
		s_CoreLogger->set_level(spdlog::level::level_enum::trace);
		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::level_enum::trace);
	}
}

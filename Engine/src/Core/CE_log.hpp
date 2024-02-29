#pragma once


#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

namespace CyberEngine
{
	/* Singleton Log class */
	class Log
	{
		/* Log functions */
		#define CE_LOG_TRACE(...)		spdlog::trace(__VA_ARGS__)
		#define CE_LOG_INFO(...)		spdlog::info(__VA_ARGS__)
		#define CE_LOG_WARN(...)		spdlog::warn(__VA_ARGS__)
		#define CE_LOG_ERROR(...)		spdlog::error(__VA_ARGS__)
		#define CE_FMT_PTR(...)			fmt::ptr(__VA_ARGS__)

		#define CE_STOPWATCH			spdlog::stopwatch

	private:
		static Log* log_;
		Log() {
			// TODO: Set logging pattern

			// TODO: Set logging level

			// TODO: Set logging sinks

			// TODO: Set file logging
		}

	public:
		// Public Functions 
		Log(Log& other) = delete;
		void operator=(const Log&) = delete;

		static Log* GetInstance() {
				if (log_ == nullptr)
				log_ = new Log();
				return log_;
		}
	};
}

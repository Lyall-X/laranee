/**
 * ***************************************************************************
 * *
 * Copyright (c) 2022 papegames.com, Inc. All Rights Reserved
 * *
 * ***************************************************************************
 *
 * @file logging.h
 * @author lyall (liuyue@papegames.net)
 * @date 2025-07-29
 * @brief
 *
 */
#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "singleton.h"

#define LOGGING_FORMAT "%Y-%m-%d %H:%M:%S.%e %t %^%l%$ %s:%# %v"
#define LOGGING_FILE_SIZE (10 * 1024 * 1024)  // 10 MB

#define GTRACE(fmt, ...) spdlog::log({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::trace, fmt, ##__VA_ARGS__)
#define GDEBUG(fmt, ...) spdlog::log({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::debug, fmt, ##__VA_ARGS__)
#define GINFO(fmt, ...) spdlog::log({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::info, fmt, ##__VA_ARGS__)
#define GWARN(fmt, ...) spdlog::log({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::warn, fmt, ##__VA_ARGS__)
#define GERROR(fmt, ...) spdlog::log({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::err, fmt, ##__VA_ARGS__)
#define GCRITICAL(fmt, ...) spdlog::log({__FILE__, __LINE__, __FUNCTION__}, spdlog::level::critical, fmt, ##__VA_ARGS__)

class Logging : public Singleton<Logging>
{
 public:
    void Init(const std::string_view& app_name)
    {
        // Create a console logger
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        // Create a file logger
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("logs/{}.log", app_name), true);

        // Create the logger with both sinks
        spdlog::logger logger("app_logger", {console_sink, file_sink});
        spdlog::set_default_logger(std::make_shared<spdlog::logger>(logger));
        spdlog::set_pattern(LOGGING_FORMAT);
        spdlog::set_level(spdlog::level::trace);
        spdlog::flush_every(std::chrono::seconds(1));
    }
};
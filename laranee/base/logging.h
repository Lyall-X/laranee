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
#include <chrono>
#include <ctime>
// #include <format>
#include <iostream>

// std::string CurrentTime()
// {
//     auto now  = std::chrono::system_clock::now();
//     auto time = std::chrono::system_clock::to_time_t(now);
//     return std::ctime(&time);
// }

// #define GERRROR(fmt, ...) \
//     std::cerr << std::format("[ERROR] [{}] " fmt "\n", CurrentTime(), ##__VA_ARGS__)
// #define GWARNING(fmt, ...) \
//     std::cerr << std::format("[WARNING] [{}] " fmt "\n", CurrentTime(), ##__VA_ARGS__)
// #define GINFO(fmt, ...) \
//     std::cout << std::format("[INFO] [{}] " fmt "\n", CurrentTime(), ##__VA_ARGS__)
// #define GDEBUG(fmt, ...) \
//     std::cout << std::format("[DEBUG] [{}] " fmt "\n", CurrentTime(), ##__VA_ARGS__)
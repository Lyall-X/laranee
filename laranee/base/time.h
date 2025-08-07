/**
 * ***************************************************************************
 * *
 * Copyright (c) 2022 papegames.com, Inc. All Rights Reserved
 * *
 * ***************************************************************************
 *
 * @file time.h
 * @author lyall (liuyue@papegames.net)
 * @date 2025-08-06
 * @brief
 *
 */
#pragma once
#include <chrono>
#include <cstdint>

class Time
{
 public:
    static uint64_t Now()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }

    static uint64_t NowSeconds()
    {
        return std::chrono::duration_cast<std::chrono::seconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }
};
/**
 * ***************************************************************************
 * *
 * Copyright (c) 2022 papegames.com, Inc. All Rights Reserved
 * *
 * ***************************************************************************
 *
 * @file noncopyable.h
 * @author lyall (liuyue@papegames.net)
 * @date 2025-07-29
 * @brief
 *
 */
#pragma once

class NonCopyable
{
 protected:
    NonCopyable()  = default;
    ~NonCopyable() = default;

 private:
    NonCopyable(const NonCopyable&)            = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&)                 = delete;
    NonCopyable& operator=(NonCopyable&&)      = delete;
};

/**
 * ***************************************************************************
 * *
 * Laranee - A fast C++ server game engine
 * *
 * ***************************************************************************
 *
 * @file singleton.h
 * @author lyall (lyall.liu@gmail.com)
 * @date 2025-07-22
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

template <typename T>
class Singleton : public NonCopyable
{
 public:
    static T& Instance()
    {
        static T instance_;
        return instance_;
    }

 protected:
    Singleton()  = default;
    ~Singleton() = default;
};
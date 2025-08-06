/**
 * ***************************************************************************
 * *
 * Copyright (c) 2022 papegames.com, Inc. All Rights Reserved
 * *
 * ***************************************************************************
 *
 * @file thread.h
 * @author lyall (liuyue@papegames.net)
 * @date 2025-08-06
 * @brief
 *
 */

#pragma once
#include <pthread.h>

#include <atomic>

#include "define.h"
#include "noncopyable.h"

class Thread : public NonCopyable
{
 public:
    Thread(const std::string_view& name = "") : name_(name) {}
    ~Thread()
    {
        if (thread_ && IsRunning())
        {
            thread_->request_stop();
        }
    }

    bool IsRunning() const { return running_.load(); }

    bool IsCurrentThread() const
    {
        return std::this_thread::get_id() == thread_id_;
    }

    bool Run(std::function<bool()>&& func)
    {
        if (IsRunning() && IsCurrentThread())
            return false;  // Already running

        running_.store(true);
        thread_ = new std::jthread([this, func](std::stop_token token) {
            SetSelfName();
            std::thread::id this_id = std::this_thread::get_id();
            GDEBUG("Thread {} started, id: {}", name_.c_str(), std::hash<std::thread::id>{}(this_id));
            while (!token.stop_requested())
            {
                if (!func())
                    break;
            }
            running_.store(false);
            GDEBUG("Thread {} stopping, id: {}", name_.c_str(), std::hash<std::thread::id>{}(this_id));
        });

        thread_id_ = std::this_thread::get_id();
        return true;
    }

    void Stop()
    {
        if (IsRunning())
        {
            thread_->request_stop();
            Join();
        }
        else
        {
            GDEBUG("Thread {} is not running, no need to stop", name_.c_str());
        }
    }

    void Join()
    {
        if (!IsCurrentThread() && thread_ && thread_->joinable())
        {
            thread_->join();
            delete thread_;
            thread_ = nullptr;
        }
    }

 private:
    void SetSelfName() { pthread_setname_np(pthread_self(), name_.c_str()); }

 private:
    std::jthread* thread_ = nullptr;
    std::atomic<bool> running_{false};
    std::thread::id thread_id_;
    std::string name_;
};
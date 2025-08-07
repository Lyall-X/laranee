/**
 * ***************************************************************************
 * *
 * Copyright (c) 2022 papegames.com, Inc. All Rights Reserved
 * *
 * ***************************************************************************
 *
 * @file server.h
 * @author lyall (liuyue@papegames.net)
 * @date 2025-08-06
 * @brief
 *
 */

#pragma once
#include "base/define.h"
#include "base/ecs.h"
#include "base/thread.h"

#define IO_THREAD_NUM 0
class ReactorEntity;
class ConnEntity;

struct MainThreadComponent : public Component
{
    Thread main_thread{"main_thread"};
};

struct ReactorComponent : public Component
{
    ReactorEntity* accept_reactor_ = nullptr;
    std::vector<ReactorEntity*> io_reactors_;
};

struct ConnComponent : public Component
{
    std::vector<ConnEntity*> connections_;
};

class ServerEntity : public Entity<MainThreadComponent, ReactorComponent>
{
 public:
    ServerEntity();
};
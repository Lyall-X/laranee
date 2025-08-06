/**
 * ***************************************************************************
 * *
 * Copyright (c) 2022 papegames.com, Inc. All Rights Reserved
 * *
 * ***************************************************************************
 *
 * @file net_sys.h
 * @author lyall (liuyue@papegames.net)
 * @date 2025-08-06
 * @brief
 *
 */
#pragma once
#include <atomic>

#include "base/define.h"
#include "base/ecs.h"
#include "base/singleton.h"
#include "conn.h"
#include "reactor.h"
#include "server.h"

class NetSystem : public System<ServerEntity, ReactorEntity, ConnEntity>,
                  public Singleton<NetSystem>
{
 public:
    void Init();
    void Run(std::function<bool()>&& main_loop);
    void Stop();

 private:
    ServerEntity* server_entity_ = nullptr;
    std::atomic<bool> running_{true};
};
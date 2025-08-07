/**
 * ***************************************************************************
 * *
 * Copyright (c) 2022 papegames.com, Inc. All Rights Reserved
 * *
 * ***************************************************************************
 *
 * @file io.h
 * @author lyall (liuyue@papegames.net)
 * @date 2025-08-06
 * @brief
 *
 */
#pragma once
#include <netinet/in.h>

#include "base/define.h"
#include "base/ecs.h"
#include "base/thread.h"
#include "udp.h"

struct EpollComponent : public Component
{
    SOCKET_FD epoll_fd = -1;
};

struct IOThreadComponent : public Component
{
    Thread io_thread{"io_thread"};
};

struct UDPAcceptComponent : public Component
{
    std::string ip;
    int port = 0;

    SOCKET_FD sockfd = -1;
    struct sockaddr_in addr;

    ikcpcb* pkcp = nullptr;
    char buffer[1500];
};

struct ReactorActionComponent : public Component
{
    std::function<uint32_t(const char* buf, uint32_t len)> output_action = [](const char* buf, uint32_t len) -> uint32_t {
        GDEBUG("Output action called with buf: {}, len: {}", std::string_view(buf, len), len);
        return 0;
    };
};

class ReactorEntity : public Entity<EpollComponent, IOThreadComponent, UDPAcceptComponent, ReactorActionComponent>
{
 public:
    ReactorEntity();
    void Listen(const std::string& ip, int port);
    bool OnLoop();
};
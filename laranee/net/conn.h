/**
 * ***************************************************************************
 * *
 * Copyright (c) 2022 papegames.com, Inc. All Rights Reserved
 * *
 * ***************************************************************************
 *
 * @file conn.h
 * @author lyall (liuyue@papegames.net)
 * @date 2025-08-05
 * @brief
 *
 */
#pragma once
#include "base/define.h"
#include "base/ecs.h"
#include "udp.h"

struct SocketComponent : public Component
{
    SOCKET_FD sockfd = -1;

    char ibuf[RECV_BUF];
    char obuf[SEND_BUF];
};

struct UDPComponent : public Component
{
    KCPObj kcp_obj;
};

class ConnEntity : public Entity<SocketComponent, UDPComponent>
{
};
/**
 * ***************************************************************************
 * *
 * Laranee - A fast C++ server game engine
 * *
 * ***************************************************************************
 *
 * @file define.h
 * @author lyall (lyall.liu@gmail.com)
 * @date 2025-07-22
 * @brief base library and define header
 *
 */
#pragma once
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "logging.h"

#define SOCKET_FD int
#define RECV_BUF 2 * 1024 * 1024  // 2M
#define SEND_BUF 2 * 1024 * 1024  // 2M
#pragma once

#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include "asio1.28.0/include/asio.hpp"
//#include "include/asio/ts/buffer.hpp"
//#include "include/asio/ts/internet.hpp"


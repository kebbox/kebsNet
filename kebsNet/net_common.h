#pragma once
//all the includes file here just for easy managing
#include <thread>
#include <mutex>
#include <deque>
#include <optional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>

#include <unordered_map>


#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include "asio1.28.0/include/asio.hpp"
//#include "include/asio/ts/buffer.hpp"
//#include "include/asio/ts/internet.hpp"


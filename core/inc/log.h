#pragma once

#ifdef HOST_BUILD
#include <iostream>

#define LOG_ERROR(tag, msg) std::cout << "[ERROR] " << tag << ": " << msg << std::endl;
#define LOG_INFO(tag, msg)  std::cout << "[INFO] " << tag << ": " << msg << std::endl;
#define LOG_DEBUG(tag, msg) std::cout << "[DEBUG] " << tag << ": " << msg << std::endl;
#define LOG_VERBOSE(tag, msg) std::cout << "[VERBOSE] " << tag << ": " << msg << std::endl;

#endif
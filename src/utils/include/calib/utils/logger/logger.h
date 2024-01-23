#pragma once

#define LOGGER_SPDLOG
#ifdef LOGGER_SPDLOG
#include <spdlog/spdlog.h>

#define LOGI(...)  SPDLOG_INFO(__VA_ARGS__);
#define LOGW(...)  SPDLOG_WARN(__VA_ARGS__);
#define LOGE(...)  SPDLOG_ERROR(__VA_ARGS__);
#define LOGD(...)  SPDLOG_DEBUG(__VA_ARGS__);

#else
#define LOGI(...) void(0);
#define LOGW(...) void(0);
#define LOGE(...) void(0);
#define LOGD(...) void(0);
#endif

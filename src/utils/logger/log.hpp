#pragma once

#ifdef LOGGER_WITH_FMT
#include <fmt/core.h> 
#define PRINTF_P(...) fmt::printf("prefix " __VA_ARGS__)

#endif // LOGGER_WITH_FMT

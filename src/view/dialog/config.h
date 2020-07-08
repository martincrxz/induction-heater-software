#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

#include <logger/logger.h>

struct AppConfig {
    uint8_t window_size;
    uint8_t log_level_enabled;
};
#endif // CONFIG_H

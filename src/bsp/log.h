#ifndef BSP_LOG_H
#define BSP_LOG_H

#include "Particle.h"

#define BSP_LOG_PRIORITY LOG_LEVEL_DEBUG

#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_ERR 3
#define LOG_LEVEL_FATAL 4
#define LOG_LEVEL_OFF 5

int Log_Write(int priority, const char *format, ...);

int Log_Init();

#endif //BSP_LOG_H
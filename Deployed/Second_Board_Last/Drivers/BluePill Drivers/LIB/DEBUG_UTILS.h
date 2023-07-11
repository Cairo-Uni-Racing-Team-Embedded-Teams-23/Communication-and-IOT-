#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#define DEBUG_MODE 1
#if DEBUG_MODE == 1
#define DEBUG_PRINTF(message, ...) printf(message, ##__VA_ARGS__)
#define DEBUG_ASSERT(cond,)
#else
#define DEBUG_PRINTF(message, ...)
#endif

#endif

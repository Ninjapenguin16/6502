#ifndef SLEEP_H
#define SLEEP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void sleepMS(uint64_t milliseconds);

void sleepNS(uint64_t nanoseconds);

#ifdef __cplusplus
}
#endif

#endif
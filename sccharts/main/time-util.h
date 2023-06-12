#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include <stdio.h>
#include <stdint.h> // For fixed-width integral types
#include <time.h>   // For clocks

// Time type and conversion macros
typedef int64_t clock_time;

#ifndef MSEC
#define MSEC(t) (t * 1000000LL)
#endif
#ifndef SEC
#define SEC(t) (t * 1000000000LL)
#endif

/** Initialize clocks. */
void time_init(void);

/** Returns the curent time. */
clock_time time_current();

/** Returns the time since initialization. */
clock_time time_elapsed();

/** Blocking call until time passed. */
int time_nanosleep(clock_time sleep_duration);

#endif
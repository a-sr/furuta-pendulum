#include "time-util.h"
/*
 * Time tracking utilities.
 * This code based on the Lingua France time implementation
 * in reactor-c, see:
 * https://github.com/lf-lang/reactor-c/blob/main/core/platform/lf_unix_clock_support.c
 */

#define _LF_CLOCK CLOCK_MONOTONIC

struct timespec convert_ns_to_timespec(clock_time t) {
    struct timespec tp;
    tp.tv_sec = t / 1000000000;
    tp.tv_nsec = (t % 1000000000);
    return tp;
}

clock_time convert_timespec_to_ns(struct timespec tp) {
    return tp.tv_sec * 1000000000 + tp.tv_nsec;
}

clock_time _lf_time_epoch_offset;
clock_time _start_time;

void time_init(void) {
    // Code based on LF's calculate_epoch_offset

    if (_LF_CLOCK == CLOCK_REALTIME) {
        // Set the epoch offset to zero (see tag.h)
        _lf_time_epoch_offset = 0LL;
    } else {
        // Initialize _lf_time_epoch_offset to the difference between what is
        // reported by whatever clock LF is using (e.g. CLOCK_MONOTONIC) and
        // what is reported by CLOCK_REALTIME.
        struct timespec physical_clock_snapshot, real_time_start;

        clock_gettime(_LF_CLOCK, &physical_clock_snapshot);
        long long physical_clock_snapshot_ns = convert_timespec_to_ns(physical_clock_snapshot);

        clock_gettime(CLOCK_REALTIME, &real_time_start);
        long long real_time_start_ns = convert_timespec_to_ns(real_time_start);

        _lf_time_epoch_offset = real_time_start_ns - physical_clock_snapshot_ns;
    }

    // Store start time
    _start_time = time_current();
}

clock_time time_current() {
    // Code based on LF's lf_clock_gettime

    struct timespec tp;
    // Adjust the clock by the epoch offset, so epoch time is always reported.
    int return_value = clock_gettime(_LF_CLOCK, (struct timespec*)&tp);
    if (return_value < 0) {
        return -1;
    }

    clock_time tp_in_ns = convert_timespec_to_ns(tp);

    // We need to apply the epoch offset if it is not zero
    if (_lf_time_epoch_offset != 0) {
        tp_in_ns += _lf_time_epoch_offset;
    }

    return tp_in_ns;
}

clock_time time_elapsed() {
    return time_current() - _start_time;
}

int time_nanosleep(clock_time sleep_duration) {
    // From LF's lf_sleep
    const struct timespec tp = convert_ns_to_timespec(sleep_duration);
    struct timespec remaining;
    return clock_nanosleep(_LF_CLOCK, 0, (const struct timespec*)&tp, (struct timespec*)&remaining);
}
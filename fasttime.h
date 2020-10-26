#ifndef INCLUDED_FASTTIME_DOT_H
#define INCLUDED_FASTTIME_DOT_H

// We need _POSIX_C_SOURCE to pick up 'struct timespec' and clock_gettime.
#define _POSIX_C_SOURCE 200809L

#ifdef __MACH__
#include <mach/mach_time.h>  // mach_absolute_time

typedef uint64_t fasttime_t;

// Return the current time.
static inline fasttime_t gettime(void) { return mach_absolute_time(); }

// Return the time different between the start and the stop, as a float
// in units of seconds.  This function does not need to be fast.
// Implementation notes: See
// https://developer.apple.com/library/mac/qa/qa1398/_index.html
static inline double tdiff(const fasttime_t start, const fasttime_t stop) {
  static mach_timebase_info_data_t timebase;
  int r __attribute__((unused));
  r = mach_timebase_info(&timebase);
  fasttime_t elapsed = stop - start;
  double ns = (double)elapsed * timebase.numer / timebase.denom;
  return ns * 1e-9;
}

static inline unsigned int random_seed_from_clock(void) {
  fasttime_t now = gettime();
  return (now & 0xFFFFFFFF) + (now >> 32);
}

#else  // LINUX

#include <time.h>
#include <stdint.h>

typedef struct timespec fasttime_t;

// Return the current time.
static inline fasttime_t gettime(void) {
  struct timespec s;
  int r __attribute__((unused));
  r = clock_gettime(CLOCK_MONOTONIC, &s);
  return s;
}

// Return the time different between the start and the stop, as a float
// in units of seconds.  This function does not need to be fast.
static inline double tdiff_sec(const fasttime_t start, const fasttime_t stop) {
  return (stop.tv_sec - start.tv_sec) + 1e-9 * (stop.tv_nsec - start.tv_nsec);
}

static inline uint64_t tdiff_msec(const fasttime_t start,
                                  const fasttime_t stop) {
  return 1000 * (stop.tv_sec - start.tv_sec) +
         (stop.tv_nsec - start.tv_nsec) / 1000000;
}

static inline uint64_t tdiff_usec(const fasttime_t start,
                                  const fasttime_t stop) {
  return 1000000 * (stop.tv_sec - start.tv_sec) +
         (stop.tv_nsec - start.tv_nsec) / 1000000;
}

static inline uint64_t tdiff_nsec(const fasttime_t start,
                                  const fasttime_t stop) {
  return 1000000000 * (stop.tv_sec - start.tv_sec) +
         (stop.tv_nsec - start.tv_nsec);
}

static inline unsigned int random_seed_from_clock(void) {
  fasttime_t now = gettime();
  return now.tv_sec + now.tv_nsec;
}

// Poison these symbols to help find portability problems.
int clock_gettime(clockid_t, struct timespec*) __attribute__((deprecated));
time_t time(time_t*) __attribute__((deprecated));

#endif  // LINUX

#endif  // INCLUDED_FASTTIME_DOT_H

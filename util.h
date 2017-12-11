#ifndef PARALLEL_PROG_UTIL_H
#define PARALLEL_PROG_UTIL_H

#include <math.h>
#include <time.h>

#define array(TYPE, SIZE) malloc(sizeof(TYPE) * (SIZE))

#define log(str, ...) \
    do{ \
        printf(str, ##__VA_ARGS__); \
        fflush(stdout); \
    }while(0)

#define DECLARE_TIMED_VARIABLES() struct timespec start, end;
#define START_TIMED() clock_gettime(CLOCK_MONOTONIC, &start);
#define END_TIMED() clock_gettime(CLOCK_MONOTONIC, &end);
#define TIME_ELAPSED() ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9)
#define MILLIS_ELAPSED() (uint64_t)round(TIME_ELAPSED() * 1000)

void swp(int* x, int* y);
int millis(double time);
int percent(double val);

#endif //PARALLEL_PROG_UTIL_H

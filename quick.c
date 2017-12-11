#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <math.h>
#include "util.h"
#include "quick.h"
#include "graph.h"

int main(){
    int maxThreads = omp_get_max_threads();

    int arrSize = 10000000;
    int* arr = array(int, arrSize);
    fillRandom(arr, arrSize);

    int* stage = array(int, arrSize);;
    double* times = array(double, maxThreads);

    DECLARE_TIMED_VARIABLES();

    log("Running sequential sort\n");
    times[0] = runTest(arr, stage, arrSize, 1);

    for(int threads = 2; threads <= maxThreads; threads++){
        log("Running parallel sort on %d threads\n", threads);
        times[threads - 1] = runTest(arr, stage, arrSize, threads);
    }

    double seqTime = times[0];
    log("\nSequential:\n");
    log("\tTime elapsed: %d ms\n", millis(seqTime));

    int maxSpeedCount, maxEfficiencyCount;
    double maxSpeed = -INFINITY, maxEfficiency = -INFINITY;

    double* speeds = array(double, maxThreads);
    double* efficiencies = array(double, maxThreads);

    speeds[0] = 1;
    efficiencies[0] = 1;

    for(int threads = 2; threads <= maxThreads; threads++){
        double parTime = times[threads - 1];
        double speed = seqTime / parTime;
        double efficiency = speed / threads;
        log("Parallel x%d:\n", threads);
        log("\tTime elapsed: %d ms\n", millis(parTime));
        log("\tSpeedup : %d%%\n", percent(speed));
        log("\tEfficiency: %d%%\n", percent(efficiency));
        if(speed > maxSpeed){
            maxSpeed = speed;
            maxSpeedCount = threads;
        }
        if(efficiency > maxEfficiency){
            maxEfficiency = efficiency;
            maxEfficiencyCount = threads;
        }
        speeds[threads - 1] = speed;
        efficiencies[threads - 1] = efficiency;
    }
    log("Max Speedup: %d%% with %d threads\n", percent(maxSpeed), maxSpeedCount);
    log("Max Efficiency: %d%% with %d threads\n", percent(maxEfficiency), maxEfficiencyCount);

    log("\nSpeedup graph:\n");
    graph(0, ceil(maxSpeed), 1, maxThreads, speeds, maxThreads, 80, 40);
    log("\nEfficiency graph:\n");
    graph(0, 1.25, 1, maxThreads, efficiencies, maxThreads, 80, 40);

    free(arr);
    free(stage);
    free(times);
    free(speeds);
    free(efficiencies);
}

double runTest(int arr[], int stage[], int len, int threads){
    DECLARE_TIMED_VARIABLES();
    memcpy(stage, arr, sizeof(int) * len);
    if(threads != 1)
        omp_set_num_threads(threads);
    START_TIMED();
    if(threads == 1)
        quick(stage, len);
    else
        quickParallel(stage, len);
    END_TIMED();
    if(!isSorted(stage, len))
        log("Sort failed\n");
    return TIME_ELAPSED();
}

void fillRandom(int arr[], int len){
    for(int i = 0; i < len; i++)
        arr[i] = i;
    for(int i = 0; i < len; i++){
        int j = rand() % len;
        swp(&arr[i], &arr[j]);
    }
}

int isSorted(const int arr[], int len){
    for(int i = 1; i < len; i++){
        if(arr[i - 1] > arr[i])
            return 0;
    }
    return 1;
}

int getPivot(const int arr[], int a, int b, int c){
    if(arr[a] >= arr[b]){
        if(arr[a] <= arr[c])
            return a;
        else if(arr[b] >= arr[c])
            return b;
        else
            return c;
    }else{
        if(arr[a] >= arr[c])
            return a;
        else if(arr[b] >= arr[c])
            return c;
        else
            return b;
    }
}

void quickRange(int arr[], int l, int u){
    if(l >= u)
        return;
    int pivot = getPivot(arr, l, u, (l + u) / 2);
    swp(&arr[u], &arr[pivot]);
    pivot = arr[u];
    int div = l;
    for(int i = l; i < u; i++){
        if(arr[i] < pivot)
            swp(&arr[i], &arr[div++]);

    }
    swp(&arr[u], &arr[div]);
    quickRange(arr, l, div - 1);
    quickRange(arr, div + 1, u);
}

void quick(int arr[], int len){
    quickRange(arr, 0, len - 1);
}

void quickRangeParallel(int arr[], const int l, const int u){
    if(l >= u)
        return;
    int pivot = getPivot(arr, l, u, (l + u) / 2);
    swp(&arr[u], &arr[pivot]);
    pivot = arr[u];
    int div = l;
    for(int i = l; i < u; i++){
        if(arr[i] < pivot)
            swp(&arr[i], &arr[div++]);

    }
    swp(&arr[u], &arr[div]);

    const int m = div;
    if(m - l - 1 >= CUTOFF){
        #pragma omp task
        quickRangeParallel(arr, l, m - 1);
    }else{
        quickRange(arr, l, m - 1);
    }
    if(u - m - 1 >= CUTOFF){
        #pragma omp task
        quickRangeParallel(arr, m + 1, u);
    }else{
        quickRange(arr, m + 1, u);
    }
}

void quickParallel(int arr[], int len){
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            quickRangeParallel(arr, 0, len - 1);
        }
        #pragma omp taskwait
    }
}
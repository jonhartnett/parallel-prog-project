#ifndef PARALLEL_PROG_QUICK_H
#define PARALLEL_PROG_QUICK_H

#define CUTOFF 1024

double runTest(int arr[], int stage[], int len, int threads);
void fillRandom(int arr[], int len);
void quick(int arr[], int len);
void quickParallel(int arr[], int len);
int isSorted(const int arr[], int len);

#endif //PARALLEL_PROG_QUICK_H

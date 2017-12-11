#include "util.h"

void swp(int* x, int* y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int millis(double time){
    return (int)(time * 1000);
}

int percent(double val){
    return (int)(val * 100);
}
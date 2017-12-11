#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "util.h"

#define toString(str, len, format, ...) \
    do{ \
        len = snprintf(NULL, 0, format, ##__VA_ARGS__); \
        str = malloc(sizeof(char) * (len + 1)); \
        snprintf(str, len + 1, format, ##__VA_ARGS__); \
    }while(0)

double interpolate(double coords[], int len, int x, double mu){
    if(x >= len - 1)
        return coords[len - 1];
    return coords[x] * (1 - mu) + coords[x + 1] * mu;
}

void graph(double minY, double maxY, double minX, double maxX, double coords[], int len, int width, int height){
    char* const chars[] = {"⎯", "⎽", "⎼", "⎻", "⎺"};
    const int lineLen = sizeof(chars) / sizeof(char*);

    double step = (maxY - minY) / height;

    int* ys = array(int, width);
    char** cs = array(char*, width);

    for(int i = 0; i < width; i++){
        double x = i * (len - 1) / (double)(width - 1);
        int xi = (int)x;
        double xf = x - xi;
        double sample = interpolate(coords, len, xi, xf);
        double y = (sample - minY) / step;
        int yi = (int)y;
        double yf = y - yi;
        ys[i] = yi;
        cs[i] = chars[(int)(yf * lineLen)];
    }

    char* yStart, * yEnd;
    int yStartLen, yEndLen;
    char* xStart, * xEnd;
    int xStartLen, xEndLen;
    toString(yStart, yStartLen, "%d%%", percent(minY));
    toString(yEnd, yEndLen, "%d%%", percent(maxY));
    toString(xStart, xStartLen, "%d%%", percent(minX));
    toString(xEnd, xEndLen, "%d%%", percent(maxX));

    int padWidth = yStartLen > yEndLen ? yStartLen : yEndLen;

    for(int i = height - 1; i >= 0; i--){
        if(i == 0)
            log("%*s", padWidth, yStart);
        else if(i == height - 1)
            log("%*s", padWidth, yEnd);
        else
            log("%*s", padWidth, "");
        log("|");
        for(int x = 0; x < width; x++){
            if(ys[x] == i){
                log("%s", cs[x]);
            }else{
                log(" ");
            }
        }
        log("\n");
    }
    log("%*s", padWidth, "");
    for(int x = 0; x < width; x++){
        log("⎺");
    }
    log("\n");
    log("%*s%d%*d\n", padWidth, "", (int)minX, width - 1, (int)maxX);

    free(ys);
    free(cs);
    free(yStart);
    free(yEnd);
    free(xStart);
    free(xEnd);
}
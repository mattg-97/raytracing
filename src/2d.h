#ifndef two_d_h
#define two_d_h

#define WIDTH 1200
#define HEIGHT 900
#define COLOUR_WHITE 0xffffffff
#define COLOUR_BLACK 0x00000000
#define RAY_COLOUR 0xffd43b
#define RAYS_NUMBER 512
#include "math.h"
#include "SDL.h"

typedef struct {
    double x;
    double y;
    double radius;
} Circle;

typedef struct {
    double x_start, y_start;
    double angle;
    double x_end, y_end;
} Ray_2D;

int run_2d(void);

#endif
#ifndef three_d_h
#define three_d_h

#define WIDTH 1200
#define HEIGHT 900
#define COLOUR_WHITE 0xffffffff
#define COLOUR_BLACK 0x00000000
#define RAY_COLOUR 0xffd43b
#define RAYS_NUMBER 512
#include "math.h"
#include "raylib.h"
#include "stdbool.h"

typedef struct {
    double x, y, z;
    double radius;
} Sphere;

typedef struct {
    double x_start, y_start, z_start;
    double angle;
    double x_end, y_end, z_end;
} Ray_3D;

int run_3d(void);

#endif
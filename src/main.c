#include "2d.h"
#include "3d.h"
#include "SDL.h"

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL Init failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    int cmd = 0;
    printf("Would you like to run the 2D (2) or 3D (3) demo: ");
    scanf("%d", &cmd);
    if (cmd != 2 && cmd != 3) {
        printf("You need to select either 2D (2) or 3D (3).\n");
        exit(EXIT_FAILURE);
    }
    if (cmd == 2) {
        return run_2d(window);
    }
    if (cmd == 3) {
        return run_3d(window);
    }
}
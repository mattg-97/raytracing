#include "2d.h"


void ray_cast(Circle circle, Ray_2D rays[]) {
    for (int i = 0; i < RAYS_NUMBER; i++) {
        double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
        Ray_2D ray = (Ray_2D){
            .x_start = circle.x,
            .angle = angle,
            .y_start = circle.y,
        };
        rays[i] = ray;
    }
}

void fill_circle(SDL_Surface* surface, Circle circle, Uint32 colour) {
    double radius_squared = pow(circle.radius, 2);
    for (double x = circle.x - circle.radius; x <= circle.x+circle.radius; x++) {
        for (double y = circle.y - circle.radius; y <= circle.y+ circle.radius; y++) {
            double distance_squared = pow(x-circle.x, 2) + pow(y-circle.y, 2);
            if (distance_squared < radius_squared) {
                SDL_Rect pixel = (SDL_Rect){x, y, 1, 1};
                if (SDL_FillRect(surface, &pixel, colour) != 0) {
                    fprintf(stderr, "Failed to write pixel: %s\n", SDL_GetError());
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

void fill_rays(SDL_Surface* surface, Ray_2D rays[RAYS_NUMBER], Uint32 colour, Circle object) {
    double radius_squared = pow(object.radius, 2);
    for (int i = 0; i < RAYS_NUMBER; i++) {
        Ray_2D ray = rays[i];
        int end_of_screen = 0;
        int object_hit = 0;
        double step = 1;
        double x_draw = ray.x_start;
        double y_draw = ray.y_start;
        while (!end_of_screen && !object_hit) {
            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);
            SDL_Rect pixel = (SDL_Rect){x_draw, y_draw, 2, 2};
            SDL_FillRect(surface, &pixel, colour);
            if (x_draw < 0 || x_draw > WIDTH) {
                end_of_screen = 1;
            }
            if (y_draw < 0 || y_draw > HEIGHT) {
                end_of_screen = 1;
            }
            double distance_squared = pow(x_draw-object.x, 2) + pow(y_draw-object.y, 2);
            if (distance_squared < radius_squared) {
                break;
            }
        }
    }
}

int run_2d() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL Init failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    Circle circle = (Circle){.x = 500, .y = 500, .radius = 50};
    Circle shadow_circle = (Circle){.x = 550, .y = 300, .radius = 120};
    
    Ray_2D rays[RAYS_NUMBER];
    ray_cast(circle, rays);
    int obstacle_speed = 1;

    SDL_bool quit = SDL_FALSE;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = SDL_TRUE;
            }
            if (e.type == SDL_MOUSEMOTION && e.motion.state != 0) {
                circle.x = e.motion.x;
                circle.y = e.motion.y;
                ray_cast(circle, rays);
            }
        }
        SDL_FillRect(surface, NULL, COLOUR_BLACK);
        fill_rays(surface, rays, RAY_COLOUR, shadow_circle);
        fill_circle(surface, circle, COLOUR_WHITE);
        fill_circle(surface, shadow_circle, COLOUR_WHITE);
        shadow_circle.y += obstacle_speed;
        if (shadow_circle.y < (0 + shadow_circle.radius)) {
            obstacle_speed = -obstacle_speed;
        } 
        if (shadow_circle.y > (HEIGHT - shadow_circle.radius)) {
            obstacle_speed = -obstacle_speed;
        }
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }
    SDL_DestroyWindow(window);
    return 0;
}
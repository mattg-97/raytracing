#include "3d.h"

int run_3d() {
    InitWindow(WIDTH, HEIGHT, "Raytracing - 3D");
    SetExitKey(KEY_ESCAPE);
    SetTargetFPS(60);
    Camera3D camera = (Camera3D){ 
        .position = (Vector3){.x = 800.f, .y = 800.0f, .z = 800.0f},
        .target = (Vector3){.x = 500.f, .y = 500.0f, .z = 500.0f},
        .up = (Vector3){.x = 0.0f, .y = 1.0f, .z = 0.0f},
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE,
     };
    Vector2 ballPosition = (Vector2){ .x = 500.0f, .y = 500.0f};
    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
        Vector3 vec3 = (Vector3){.x = ballPosition.x, .y = ballPosition.y,  .z = 500};

        DrawSphere(vec3, 50.0f, GRAY);

        EndMode3D();
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
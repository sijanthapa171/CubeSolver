#include "App.h"
#include <math.h>

App::App() : 
    screenWidth(800), screenHeight(450),
    cameraAngle({0.78f, 0.5f}), cameraRadius(15.0f) {
    
    camera = { 0 };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void App::Init() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "3D Rubik's Cube");
    SetTargetFPS(60);
}

void App::RunLoop() {
    while (!WindowShouldClose()) {
        cameraRadius -= GetMouseWheelMove() * 1.5f;
        if (cameraRadius < 5.0f) cameraRadius = 5.0f;
        if (cameraRadius > 100.0f) cameraRadius = 100.0f;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 delta = GetMouseDelta();
            cameraAngle.x -= delta.x * 0.01f;
            cameraAngle.y += delta.y * 0.01f;
        } else {
            cameraAngle.x -= 0.003f; 
        }

        if (cameraAngle.y > 1.5f) cameraAngle.y = 1.5f;
        if (cameraAngle.y < -1.5f) cameraAngle.y = -1.5f;

        camera.position.x = sinf(cameraAngle.x) * cosf(cameraAngle.y) * cameraRadius;
        camera.position.y = sinf(cameraAngle.y) * cameraRadius;
        camera.position.z = cosf(cameraAngle.x) * cosf(cameraAngle.y) * cameraRadius;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        rubik.Draw();

        EndMode3D();

        DrawText("3D Rubik's Cube", 10, 10, 20, DARKGRAY);
        DrawText("- Left Click + Drag to view 360 degrees", 10, 40, 20, DARKGRAY);
        DrawText("- Mouse Wheel to zoom in and out", 10, 60, 20, DARKGRAY);

        EndDrawing();
    }
}

void App::Cleanup() {
    CloseWindow();
}

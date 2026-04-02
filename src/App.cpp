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
        ClearBackground({ 18, 18, 24, 255 }); 
        BeginMode3D(camera);

        DrawGrid(40, 1.0f);

        rubik.Draw();

        EndMode3D();

        DrawText("3D Rubik's Cube", 10, 10, 20, { 220, 220, 220, 255 });
        DrawText("- Left Click + Drag to view 360 degrees", 10, 40, 16, { 160, 160, 160, 255 });
        DrawText("- Mouse Wheel to zoom in and out", 10, 60, 16, { 160, 160, 160, 255 });

        // --- Top-right stats panel ---
        {
            int sw = GetScreenWidth();
            int panelW = 230, panelH = 110, panelX = sw - panelW - 10, panelY = 10;
            int fps = GetFPS();
            bool autoRotating = !IsMouseButtonDown(MOUSE_BUTTON_LEFT);

            DrawRectangle(panelX, panelY, panelW, panelH, { 0, 0, 0, 160 });
            DrawRectangleLines(panelX, panelY, panelW, panelH, { 80, 80, 100, 200 });

            Color fpsColor = (fps >= 55) ? (Color){ 80, 220, 80, 255 }
                           : (fps >= 30) ? (Color){ 220, 180, 60, 255 }
                                         : (Color){ 220, 60, 60, 255 };
            DrawText(TextFormat("FPS: %d", fps),
                     panelX + 10, panelY + 10, 18, fpsColor);

            DrawText(TextFormat("Zoom:  %.1f", cameraRadius),
                     panelX + 10, panelY + 34, 15, { 180, 200, 255, 255 });
            DrawText(TextFormat("Yaw:   %.1f deg", cameraAngle.x * (180.0f / PI)),
                     panelX + 10, panelY + 56, 15, { 180, 200, 255, 255 });
            DrawText(TextFormat("Pitch: %.1f deg", cameraAngle.y * (180.0f / PI)),
                     panelX + 10, panelY + 78, 15, { 180, 200, 255, 255 });

            Color dotColor = autoRotating ? (Color){ 80, 220, 80, 255 }
                                          : (Color){ 220, 60, 60, 255 };
            DrawCircle(panelX + panelW - 18, panelY + 12, 6, dotColor);
            DrawText(autoRotating ? "Auto-Rotate" : "Manual", 
                     panelX + panelW - 100, panelY + 92, 13, { 160, 160, 160, 255 });
        }

        EndDrawing();
    }
}

void App::Cleanup() {
    CloseWindow();
}

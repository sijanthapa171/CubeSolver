#include "core/App.h"
#include "ui/StatsPanel.h"
#include <math.h>

App::App() :
    screenWidth(800), screenHeight(450),
    cameraAngle({ 0.78f, 0.5f }), cameraRadius(15.0f),
    isDraggingRight(false)
{
    camera = { 0 };
    camera.target     = { 0.0f, 0.0f, 0.0f };
    camera.up         = { 0.0f, 1.0f, 0.0f };
    camera.fovy       = 45.0f;
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
        if (cameraRadius <   5.0f) cameraRadius =   5.0f;
        if (cameraRadius > 100.0f) cameraRadius = 100.0f;

        float dt = GetFrameTime();
        rubik.Update(dt);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 delta = GetMouseDelta();
            cameraAngle.x -= delta.x * 0.01f;
            cameraAngle.y += delta.y * 0.01f;
        }

        if (cameraAngle.y >  1.5f) cameraAngle.y =  1.5f;
        if (cameraAngle.y < -1.5f) cameraAngle.y = -1.5f;

        if (!rubik.IsAnimating()) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                Ray ray = GetMouseRay(GetMousePosition(), camera);
                float hs = 1.5f * 1.05f; 
                BoundingBox box = { (Vector3){-hs, -hs, -hs}, (Vector3){hs, hs, hs} };
                RayCollision col = GetRayCollisionBox(ray, box);

                if (col.hit) {
                    isDraggingRight = true;
                    dragStartMouse = GetMousePosition();
                    hitNormal = col.normal;
                    hitCubieLogical = { round(col.point.x / 1.05f), round(col.point.y / 1.05f), round(col.point.z / 1.05f) };

                    if (hitCubieLogical.x > 1) hitCubieLogical.x = 1; else if (hitCubieLogical.x < -1) hitCubieLogical.x = -1;
                    if (hitCubieLogical.y > 1) hitCubieLogical.y = 1; else if (hitCubieLogical.y < -1) hitCubieLogical.y = -1;
                    if (hitCubieLogical.z > 1) hitCubieLogical.z = 1; else if (hitCubieLogical.z < -1) hitCubieLogical.z = -1;
                }
            } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && isDraggingRight) {
                Vector2 mPos = GetMousePosition();
                Vector2 delta = { mPos.x - dragStartMouse.x, mPos.y - dragStartMouse.y };
                if (Vector2Length(delta) > 15.0f) {
                    int axis = 0; 
                    int slice = 0;
                    int dir = 1;

                    if (fabs(hitNormal.x) > 0.5f) {
                        if (fabs(delta.y) > fabs(delta.x)) {
                            axis = 2; slice = hitCubieLogical.z; dir = (delta.y > 0) ? -1 : 1; dir *= hitNormal.x;
                        } else {
                            axis = 1; slice = hitCubieLogical.y; dir = (delta.x > 0) ? 1 : -1; dir *= hitNormal.x;
                        }
                    } else if (fabs(hitNormal.y) > 0.5f) {
                        if (fabs(delta.x) > fabs(delta.y)) {
                            axis = 2; slice = hitCubieLogical.z; dir = (delta.x > 0) ? -1 : 1; dir *= hitNormal.y;
                        } else {
                            axis = 0; slice = hitCubieLogical.x; dir = (delta.y > 0) ? -1 : 1; dir *= hitNormal.y;
                        }
                    } else if (fabs(hitNormal.z) > 0.5f) {
                        if (fabs(delta.x) > fabs(delta.y)) {
                            axis = 1; slice = hitCubieLogical.y; dir = (delta.x > 0) ? 1 : -1; dir *= hitNormal.z;
                        } else {
                            axis = 0; slice = hitCubieLogical.x; dir = (delta.y > 0) ? 1 : -1; dir *= hitNormal.z;
                        }
                    }

                    rubik.StartRotation(axis, slice, dir);
                    isDraggingRight = false;
                }
            }
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
            isDraggingRight = false;
        }

        camera.position.x = sinf(cameraAngle.x) * cosf(cameraAngle.y) * cameraRadius;
        camera.position.y = sinf(cameraAngle.y) * cameraRadius;
        camera.position.z = cosf(cameraAngle.x) * cosf(cameraAngle.y) * cameraRadius;

        BeginDrawing();
        ClearBackground({ 18, 18, 24, 255 });

        BeginMode3D(camera);
        DrawGrid(40, 1.0f);
        rubik.Draw();
        EndMode3D();

        DrawText("3D Rubik's Cube",                        10, 10, 20, { 220, 220, 220, 255 });
        DrawText("- Right Click + Drag to rotate a slice", 10, 40, 16, { 160, 160, 160, 255 });
        DrawText("- Left Click + Drag to view 360 degrees", 10, 60, 16, { 160, 160, 160, 255 });
        DrawText("- Mouse Wheel to zoom in and out",        10, 80, 16, { 160, 160, 160, 255 });

        DrawStatsPanel(cameraRadius, cameraAngle);

        EndDrawing();
    }
}

void App::Cleanup() {
    CloseWindow();
}

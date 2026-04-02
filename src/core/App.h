#pragma once
#include "raylib.h"
#include "cube/RubiksCube.h"

class App {
public:
    App();
    void Init();
    void RunLoop();
    void Cleanup();

private:
    int screenWidth;
    int screenHeight;

    Camera3D camera;
    Vector2  cameraAngle;
    float    cameraRadius;

    RubiksCube rubik;

    bool isDraggingRight;
    Vector2 dragStartMouse;
    Vector3 hitNormal;
    Vector3 hitCubieLogical;
};

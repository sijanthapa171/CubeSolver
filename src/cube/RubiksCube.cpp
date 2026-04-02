#include "cube/RubiksCube.h"
#include "cube/Cubie.h"
#include <math.h>

RubiksCube::RubiksCube() : 
    cubieSize(1.0f), spacing(1.05f), 
    isAnimating(false), animAxis(0), animSlice(0), animDir(1), animAngle(0.0f), targetAngle(0.0f) 
{
    Color rWhite  = { 255, 255, 255, 255 };
    Color rYellow = { 255, 213,   0, 255 };
    Color rGreen  = {   0, 158,  96, 255 };
    Color rBlue   = {   0,  81, 186, 255 };
    Color rRed    = { 196,  30,  58, 255 };
    Color rOrange = { 255,  88,   0, 255 };
    Color rBlack  = {  15,  15,  15, 255 };

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {
                CubieState c;
                c.pos = { (float)x * spacing, (float)y * spacing, (float)z * spacing };
                c.transform = MatrixTranslate(c.pos.x, c.pos.y, c.pos.z);
                
                c.up    = (y ==  1) ? rWhite  : rBlack;
                c.down  = (y == -1) ? rYellow : rBlack;
                c.front = (z ==  1) ? rGreen  : rBlack;
                c.back  = (z == -1) ? rBlue   : rBlack;
                c.right = (x ==  1) ? rRed    : rBlack;
                c.left  = (x == -1) ? rOrange : rBlack;

                cubies.push_back(c);
            }
        }
    }
}

bool RubiksCube::StartRotation(int axis, int slice, int direction) {
    if (isAnimating) return false;
    
    isAnimating = true;
    animAxis = axis;
    animSlice = slice;
    animDir = direction;
    animAngle = 0.0f;
    targetAngle = (PI / 2.0f) * direction;
    
    return true;
}

void RubiksCube::Update(float dt) {
    if (!isAnimating) return;

    float speed = PI * 2.0f * dt; 
    
    bool finished = false;
    float step = speed * ((targetAngle > 0) ? 1.0f : -1.0f);
    
    if (fabs(animAngle + step) >= fabs(targetAngle)) {
        step = targetAngle - animAngle;
        finished = true;
    }
    animAngle += step;

    Matrix rotMat = MatrixIdentity();
    if (animAxis == 0) rotMat = MatrixRotateX(step);
    else if (animAxis == 1) rotMat = MatrixRotateY(step);
    else if (animAxis == 2) rotMat = MatrixRotateZ(step);

    for (auto& c : cubies) {
        int lx = round(c.pos.x / spacing);
        int ly = round(c.pos.y / spacing);
        int lz = round(c.pos.z / spacing);

        bool inSlice = false;
        if (animAxis == 0 && lx == animSlice) inSlice = true;
        if (animAxis == 1 && ly == animSlice) inSlice = true;
        if (animAxis == 2 && lz == animSlice) inSlice = true;

        if (inSlice) {
            c.pos = Vector3Transform(c.pos, rotMat);
            c.transform = MatrixMultiply(c.transform, rotMat);
            
            if (finished) {
                c.pos.x = round(c.pos.x / spacing) * spacing;
                c.pos.y = round(c.pos.y / spacing) * spacing;
                c.pos.z = round(c.pos.z / spacing) * spacing;
                
            }
        }
    }

    if (finished) {
        isAnimating = false;
    }
}

void RubiksCube::Draw() {
    for (const auto& c : cubies) {
        DrawCubie(c.transform, cubieSize, c.up, c.down, c.front, c.back, c.right, c.left);
    }
}

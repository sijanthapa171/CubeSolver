#include "RubiksCube.h"
#include "rlgl.h"

RubiksCube::RubiksCube() : cubieSize(1.0f), spacing(1.05f) {}

void RubiksCube::DrawCubie(Vector3 position, float size, Color up, Color down, Color front, Color back, Color right, Color left) {
    float s = size / 2.0f;

    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    
    rlBegin(RL_QUADS);

    // Front Face (Z+)
    rlColor4ub(front.r, front.g, front.b, front.a);
    rlVertex3f(-s, -s,  s);
    rlVertex3f( s, -s,  s);
    rlVertex3f( s,  s,  s);
    rlVertex3f(-s,  s,  s);

    // Back Face (Z-)
    rlColor4ub(back.r, back.g, back.b, back.a);
    rlVertex3f(-s, -s, -s);
    rlVertex3f(-s,  s, -s);
    rlVertex3f( s,  s, -s);
    rlVertex3f( s, -s, -s);

    // Top Face (Y+)
    rlColor4ub(up.r, up.g, up.b, up.a);
    rlVertex3f(-s,  s, -s);
    rlVertex3f(-s,  s,  s);
    rlVertex3f( s,  s,  s);
    rlVertex3f( s,  s, -s);

    // Bottom Face (Y-)
    rlColor4ub(down.r, down.g, down.b, down.a);
    rlVertex3f(-s, -s, -s);
    rlVertex3f( s, -s, -s);
    rlVertex3f( s, -s,  s);
    rlVertex3f(-s, -s,  s);

    // Right Face (X+)
    rlColor4ub(right.r, right.g, right.b, right.a);
    rlVertex3f( s, -s, -s);
    rlVertex3f( s,  s, -s);
    rlVertex3f( s,  s,  s);
    rlVertex3f( s, -s,  s);

    // Left Face (X-)
    rlColor4ub(left.r, left.g, left.b, left.a);
    rlVertex3f(-s, -s, -s);
    rlVertex3f(-s, -s,  s);
    rlVertex3f(-s,  s,  s);
    rlVertex3f(-s,  s, -s);

    rlEnd();
    rlPopMatrix();
}

void RubiksCube::Draw() {
    Color rWhite  = { 255, 255, 255, 255 };
    Color rYellow = { 255, 213, 0, 255 };
    Color rGreen  = { 0, 158, 96, 255 };
    Color rBlue   = { 0, 81, 186, 255 };
    Color rRed    = { 196, 30, 58, 255 };
    Color rOrange = { 255, 88, 0, 255 };
    Color rBlack  = { 15, 15, 15, 255 };

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            for (int z = -1; z <= 1; z++) {
                Vector3 pos = { x * spacing, y * spacing, z * spacing };

                Color up    = (y ==  1) ? rWhite  : rBlack;
                Color down  = (y == -1) ? rYellow : rBlack;
                Color front = (z ==  1) ? rGreen  : rBlack;
                Color back  = (z == -1) ? rBlue   : rBlack;
                Color right = (x ==  1) ? rRed    : rBlack;
                Color left  = (x == -1) ? rOrange : rBlack;

                DrawCubie(pos, cubieSize, up, down, front, back, right, left);
            }
        }
    }
}

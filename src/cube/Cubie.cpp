#include "cube/Cubie.h"
#include "rlgl.h"

void DrawCubie(Matrix transform, float size,
               Color up, Color down,
               Color front, Color back,
               Color right, Color left)
{
    float s = size / 2.0f;

    rlPushMatrix();
    float m[16] = {
        transform.m0, transform.m1,  transform.m2,  transform.m3,
        transform.m4, transform.m5,  transform.m6,  transform.m7,
        transform.m8, transform.m9,  transform.m10, transform.m11,
        transform.m12, transform.m13, transform.m14, transform.m15
    };
    rlMultMatrixf(m);

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

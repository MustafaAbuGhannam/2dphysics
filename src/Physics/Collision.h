#ifndef COLLISION_H
#define COLLISION_H

#include "Body.h"

struct Collision
{
    static bool IsCollided(Body *a, Body *b);
    static bool IsCollidedCircleCircle(Body *a, Body *b);
};

#endif
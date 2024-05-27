#ifndef COLLISION_H
#define COLLISION_H

#include "Body.h"
#include "Contact.h"

struct Collision
{
    static bool IsCollided(Body *a, Body *b, Contact &contact);
    static bool IsCollidedCircleCircle(Body *a, Body *b, Contact &contact);
    static bool IsCollidedPolygonPolygon(Body *a, Body *b, Contact &contact);
    
};

#endif
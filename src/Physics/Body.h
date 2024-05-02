#ifndef BODY_H
#define BODY_H

#include "Vec2.h"

struct Body
{
    int radius;

    Vec2 postion;
    Vec2 velocity;
    Vec2 acceleraion;

    Vec2 sumForces;

    float mass;
    float invMass;

    Body(float x, float y, float mass);
    ~Body();

    void integrate(float dt);
    void addForce(const Vec2 &force);
    void clearForces();
};

#endif
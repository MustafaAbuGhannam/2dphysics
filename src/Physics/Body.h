#ifndef BODY_H
#define BODY_H

#include "Vec2.h"
#include "Shape.h"

struct Body
{
    int radius;

    Vec2 postion;
    Vec2 velocity;
    Vec2 acceleraion;

    Vec2 sumForces;

    float mass;
    float invMass;

    Body(const Shape& shape, float x, float y, float mass);
    ~Body();

    Shape* shape = NULL;

    void integrate(float dt);
    void addForce(const Vec2 &force);
    void clearForces();
};

#endif
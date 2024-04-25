#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec2.h"

struct Particle
{
    int radius;

    Vec2 postion;
    Vec2 velocity;
    Vec2 acceleraion;

    Vec2 sumForces;

    float mass;
    float invMass;

    Particle(float x, float y, float mass);
    ~Particle();

    void integrate(float dt);
    void addForce(const Vec2 &force);
    void clearForces();
};

#endif
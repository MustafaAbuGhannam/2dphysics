#ifndef BODY_H
#define BODY_H

#include "Vec2.h"
#include "Shape.h"
#include "../Graphics.h"

struct Body
{
    bool isCollided; // temp addition

    // Linear motion
    Vec2 postion;
    Vec2 velocity;
    Vec2 acceleration;

    Vec2 sumForces;

    float mass;
    float invMass;

    // Angular motion
    float rotation;
    float angularVelocity;
    float angularAcceleration;

    float I;
    float invI;

    float sumTorque;

    Shape *shape = nullptr;

    Body(const Shape &shape, float x, float y, float mass);
    ~Body();

    void IntegrateLinear(float dt);
    void AddForce(const Vec2 &force);
    void ClearForces();

    void IntegrateAngular(float dt);
    void AddTorque(float torque);
    void ClearTorque();

    void CollidedWithScreenBorders();
    void Update(float dt);
    bool IsStatic();
};

#endif
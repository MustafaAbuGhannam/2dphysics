#include "Force.h"
#include <iostream>

Vec2 Force::GenerateDragForce(const Particle &particle, float k)
{
    Vec2 dragForce = Vec2(0, 0);
    if (particle.velocity.MagnitudeSquared() > 0)
    {
        Vec2 dragDirection = particle.velocity.UnitVector() * -1.0;
        float dragMagnitude = k * particle.velocity.MagnitudeSquared();

        dragForce = dragDirection * dragMagnitude;
    }

    return dragForce;
}

Vec2 Force::GenerateFrictionForce(const Particle &Particle, float k)
{

    Vec2 frictionForce = Vec2(0.0, 0.0);

    Vec2 frictionDirection = Particle.velocity.UnitVector() * -1.0;
    float frictionMagnitude = k;

    frictionForce = frictionDirection * frictionMagnitude;

    return frictionForce;
}

Vec2 Force::GenerateGravitationalForce(const Particle &a, const Particle &b, float G, float minDistance, float maxDistance)
{
    Vec2 d = (b.postion - a.postion);
    float distanceSquared = d.MagnitudeSquared();

    distanceSquared = std::clamp(distanceSquared, minDistance, maxDistance);

    Vec2 gravitationalDirection = d.UnitVector();
    float attractionMagnitude = G * (a.mass * b.mass) / distanceSquared;

    Vec2 attractionForce = gravitationalDirection * attractionMagnitude;

    return attractionForce;
}

Vec2 Force::GenerateSpringForce(const Particle &particle, const Vec2 &anchor, float restLength, float k)
{

    Vec2 d = particle.postion - anchor;

    float displacement = d.Magnitude() - restLength;
    Vec2 springDirection = d.UnitVector();
    float springMagnitude = -k * displacement;

    Vec2 springForce = springDirection * springMagnitude;

    return springForce;
}

Vec2 Force::GenerateSpringForce(const Particle &a, const Particle &b, float restLength, float k)
{
    return Force::GenerateSpringForce(a, b.postion, restLength, k);
}

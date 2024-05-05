#include "Body.h"
#include <iostream>

Body::Body(const Shape& shape, float x, float y, float mass)
{
    this->shape = shape.Clone();
    this->postion = Vec2(x, y);
    this->mass = mass;
    if (this->mass != 0.0)
    {
        this->invMass = 1.0 / this->mass;
    }
    else
    {
        this->invMass = 0.0;
    }
    std::cout << "Body constructor called !" << std::endl;
}

Body::~Body()
{
    delete this->shape;
    std::cout << "Body destructor called !" << std::endl;
}

void Body::integrate(float dt)
{
    // Find acc
    this->acceleraion = this->sumForces * this->invMass;
    // integrate
    this->velocity += this->acceleraion * dt;
    this->postion += this->velocity * dt;
    // clear forces
    this->clearForces();
}

void Body::addForce(const Vec2 &force)
{
    this->sumForces += force;
}

void Body::clearForces()
{
    this->sumForces = Vec2(0.0, 0.0);
}

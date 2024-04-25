#include "Particle.h"
#include <iostream>

Particle::Particle(float x, float y, float mass)
{
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
    std::cout << "Partical constructor called !" << std::endl;
}

Particle::~Particle()
{
    std::cout << "Parical destructor called !" << std::endl;
}

void Particle::integrate(float dt)
{
    // Find acc
    this->acceleraion = this->sumForces * this->invMass;
    // integrate
    this->velocity += this->acceleraion * dt;
    this->postion += this->velocity * dt;
    // clear forces
    this->clearForces();
}

void Particle::addForce(const Vec2 &force)
{
    this->sumForces += force;
}

void Particle::clearForces()
{
    this->sumForces = Vec2(0.0, 0.0);
}
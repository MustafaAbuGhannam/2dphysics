#include "Body.h"
#include <iostream>

Body::Body(const Shape &shape, float x, float y, float mass)
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

void Body::CollidedWithScreenBorders()
{
    CircleShape *bodyCircle = (CircleShape *)this->shape;

    if (this->postion.y + bodyCircle->radius >= Graphics::Height())
    {
        this->postion.y = Graphics::Height() - bodyCircle->radius;
        this->velocity.y = this->velocity.y * -0.9;
    }
    else if (this->postion.y - bodyCircle->radius <= 0)
    {
        this->postion.y = bodyCircle->radius;
        this->velocity.y = this->velocity.y * -0.9;
    }
    if (this->postion.x + bodyCircle->radius >= Graphics::Width())
    {
        this->postion.x = Graphics::Width() - bodyCircle->radius;
        this->velocity.x = this->velocity.x * -0.9;
    }

    else if (this->postion.x - bodyCircle->radius <= 0)
    {
        this->postion.x = bodyCircle->radius;
        this->velocity.x = this->velocity.x * -0.9;
    }
}

void Body::Draw() const
{
    this->shape->Draw(this->postion);
}

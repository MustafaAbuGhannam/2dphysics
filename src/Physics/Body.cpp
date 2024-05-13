#include "Body.h"
#include <iostream>

Body::Body(const Shape &shape, float x, float y, float mass)
{
    this->shape = shape.Clone();
    this->postion = Vec2(x, y);
    this->mass = mass;
    this->velocity = Vec2(0, 0);
    this->acceleration = Vec2(0, 0);
    this->rotation = 0;
    this->angularAcceleration = 0.0;
    this->angularVelocity = 0.0;
    this->sumForces = Vec2(0, 0);
    this->sumTorque = 0.0;

    this->I = this->shape->getMomentOfInertia() * this->mass;

    if (this->mass != 0.0)
    {
        this->invMass = 1.0 / this->mass;
    }
    else
    {
        this->invMass = 0.0;
    }

    if (this->I != 0.0)
    {
        this->invI = 1.0 / this->I;
    }
    else
    {
        this->invI = 0.0;
    }

    std::cout << "Body constructor called !" << std::endl;
}

Body::~Body()
{
    delete this->shape;
    std::cout << "Body destructor called !" << std::endl;
}

void Body::IntegrateLinear(float dt)
{
    // Find acc
    this->acceleration = this->sumForces * this->invMass;
    // integrate
    this->velocity += this->acceleration * dt;
    this->postion += this->velocity * dt;
    // clear forces
    this->ClearForces();
}

void Body::IntegrateAngular(float dt)
{
    this->angularAcceleration = this->sumTorque * this->invI;

    this->angularVelocity += this->angularAcceleration * dt;

    this->rotation += this->angularVelocity * dt;

    this->ClearTorque();
}

void Body::AddForce(const Vec2 &force)
{
    this->sumForces += force;
}

void Body::ClearForces()
{
    this->sumForces = Vec2(0.0, 0.0);
}

void Body::CollidedWithScreenBorders()
{
    if (this->shape->GetType() == CIRCILE)
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
}

void Body::Draw() const
{
    this->shape->Draw(this->postion, this->rotation);
}

void Body::AddTorque(float torque)
{
    this->sumTorque += torque;
}

void Body::ClearTorque()
{
    this->sumTorque = 0.0;
}

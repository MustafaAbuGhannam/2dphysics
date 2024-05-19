#include "Contact.h"
#include <iostream>

void Contact::ResolvePenetration()
{
    this->ResolveWithProjection();
}

void Contact::ResolveWithProjection()
{
    if (this->a->IsStatic() && this->b->IsStatic())
    {
        return;
    }

    float da = this->depth / (this->a->invMass + this->b->invMass) * this->a->invMass;
    float db = this->depth / (this->a->invMass + this->b->invMass) * this->b->invMass;

    this->a->postion -= this->normal * da;
    this->b->postion += this->normal * db;
}

void Contact::ResolveWithImpulse()
{
    Vec2 vrel = a->velocity - b->velocity;
    float e = std::min(a->restitution, b->restitution);

    float impulseMagnitude = -(1 + e) * vrel.Dot(this->normal) / (this->a->invMass + this->b->invMass); 
    Vec2 impulseDirection = this->normal;

    Vec2 jn = impulseDirection * impulseMagnitude;

    this->a->ApplyImpulse(jn);
    this->b->ApplyImpulse(-jn);
}

void Contact::ResolveCollision()
{
    this->ResolvePenetration();
    this->ResolveWithImpulse();
}
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
    Vec2 ra = end - a->postion;
    Vec2 rb = start - b->postion;
    Vec2 va = a->velocity + Vec2(- a->angularVelocity * ra.y, a->angularVelocity * ra.x);
    Vec2 vb = b->velocity + Vec2(- b->angularVelocity * rb.y, b->angularVelocity * rb.x);
    const Vec2 vrel = va - vb;

    float e = std::min(a->restitution, b->restitution);

    float vrelDotNormal = vrel.Dot(this->normal);

    float impulseMagnitude = -(1 + e) * vrelDotNormal / ((this->a->invMass + this->b->invMass) + ra.Cross(normal) * ra.Cross(normal) * a->invI + rb.Cross(normal) * rb.Cross(normal) * b->invI); 
    Vec2 impulseDirection = this->normal;

    Vec2 jn = impulseDirection * impulseMagnitude;

    this->a->ApplyImpulse(jn, ra);
    this->b->ApplyImpulse(-jn, rb);
}

void Contact::ResolveCollision()
{
    this->ResolvePenetration();
    this->ResolveWithImpulse();
}